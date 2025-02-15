/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhattab <ykhattab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 01:33:13 by yousef            #+#    #+#             */
/*   Updated: 2025/02/14 20:25:54 by ykhattab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/**
 * @brief Determines the order of fork acquisition.
 *
 * To prevent deadlock, each philosopher picks up the forks in a specific order.
 * This function determines which fork (left or right) should be acquired first.
 * It accounts for the special case when the philosopher is the last in the table,
 * ensuring that the fork indices wrap correctly and avoiding deadlock.
 *
 * @param ph Pointer to the current philosopher.
 * @param first_fork Pointer to store the first fork to lock.
 * @param second_fork Pointer to store the second fork to lock.
 */
static void get_fork_order(t_philosopher *ph, pthread_mutex_t **first_fork, pthread_mutex_t **second_fork)
{
	int left_index = ph->id - 1;
	int right_index = (ph->id) % ph->data->number_of_philosophers;
	if (left_index < right_index)
	{
		*first_fork = &ph->data->forks[left_index];
		*second_fork = &ph->data->forks[right_index];
	}
	else
	{
		*first_fork = &ph->data->forks[right_index];
		*second_fork = &ph->data->forks[left_index];
	}
}

/**
 * @brief Checks whether the simulation has been stopped.
 *
 * This function locks the stop mutex, reads the simulation_stopped flag,
 * and then unlocks the mutex.
 *
 * @param data Pointer to the shared simulation data.
 * @return int Returns non-zero if the simulation is stopped.
 */
static int simulation_stopped(t_data *data)
{
    int stopped;
    pthread_mutex_lock(&data->stop_mutex);
    stopped = data->simulation_stopped;
    pthread_mutex_unlock(&data->stop_mutex);
    return stopped;
}

/**
 * @brief Waits for permission from the waiter before attempting to eat.
 *
 * To avoid deadlocks, all but one philosopher are allowed to try to eat 
 * at the same time. This function blocks until permission is granted.
 *
 * @param ph Pointer to the current philosopher.
 */
static void wait_for_waiter_permission(t_philosopher *ph)
{
	pthread_mutex_lock(&ph->data->waiter_mutex);
	while (ph->data->eating_philosophers == ph->data->number_of_philosophers - 1)
		pthread_cond_wait(&ph->data->waiter_cond, &ph->data->waiter_mutex);
	ph->data->eating_philosophers++;
	pthread_mutex_unlock(&ph->data->waiter_mutex);
}

/**
 * @brief Signals the waiter that the philosopher has finished eating.
 *
 * This function decrements the counter of eating philosophers and broadcasts
 * the condition variable so that waiting philosophers may continue.
 *
 * @param ph Pointer to the current philosopher.
 */
static void signal_waiter(t_philosopher *ph)
{
    pthread_mutex_lock(&ph->data->waiter_mutex);
    ph->data->eating_philosophers--;
    pthread_cond_broadcast(&ph->data->waiter_cond);
    pthread_mutex_unlock(&ph->data->waiter_mutex);
}

/**
 * @brief Simulates the philosopher eating.
 *
 * This function handles the philosopher's eating process: updates the last meal time,
 * increments the meals eaten count, and simulates the eating duration.
 *
 * @param ph Pointer to the current philosopher.
 */
static void eat(t_philosopher *ph)
{
    pthread_mutex_lock(&ph->meal_mutex);
    ph->last_meal_time = get_current_time(ph->data);
    print_status(ph->data, ph->id, "is eating");
    pthread_mutex_unlock(&ph->meal_mutex);
    philo_sleep(ph->data, ph->data->time_to_eat);
    pthread_mutex_lock(&ph->meal_mutex);
    ph->meals_eaten++;
    pthread_mutex_unlock(&ph->meal_mutex);
}

/**
 * @brief Picks up the forks and prints the status.
 *
 * This function locks the given forks and prints a message indicating that the
 * philosopher has taken them.
 *
 * @param ph Pointer to the current philosopher.
 * @param first_fork Pointer to the first fork.
 * @param second_fork Pointer to the second fork.
 */
static void pick_up_forks(t_philosopher *ph, pthread_mutex_t *first_fork, pthread_mutex_t *second_fork)
{
    pthread_mutex_lock(first_fork);
    print_status(ph->data, ph->id, "has taken a fork");
    pthread_mutex_lock(second_fork);
    print_status(ph->data, ph->id, "has taken a fork");
}

static void put_down_forks(pthread_mutex_t *first_fork, pthread_mutex_t *second_fork)
{
    pthread_mutex_unlock(second_fork);
    pthread_mutex_unlock(first_fork);
}

void *philosopher_routine(void *arg)
{
    t_philosopher *ph = (t_philosopher *)arg;
    pthread_mutex_t *first_fork;
	pthread_mutex_t *second_fork;

    // Small initial stagger if even
    if (ph->id % 2 == 0)
		philo_sleep(ph->data, 1);
	get_fork_order(ph, &first_fork, &second_fork);
    while (1)
    {
        if (simulation_stopped(ph->data))
			break;
        print_status(ph->data, ph->id, "is thinking");
		wait_for_waiter_permission(ph);
		pick_up_forks(ph, first_fork, second_fork);
		eat(ph);
		put_down_forks(first_fork, second_fork);
		signal_waiter(ph);
        print_status(ph->data, ph->id, "is sleeping");
        philo_sleep(ph->data, ph->data->time_to_sleep);
    }
    return NULL;
}


