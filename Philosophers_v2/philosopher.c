/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhattab <ykhattab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 01:33:13 by yousef            #+#    #+#             */
/*   Updated: 2025/02/21 00:42:18 by ykhattab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/**
 * @brief Determines the order of fork acquisition.
 *
 * To prevent deadlock, each philosopher picks up the forks in a specific order.
 * This function determines which fork (left or right) should be acquired first.
 *
 * @param ph Pointer to the current philosopher.
 * @param first_fork Pointer to store the first fork to lock.
 * @param second_fork Pointer to store the second fork to lock.
 */
static void	get_fork_order(t_philosopher *ph, pthread_mutex_t **first_fork,
		pthread_mutex_t **second_fork)
{
	int	left_index;
	int	right_index;

	left_index = ph->id - 1;
	right_index = (ph->id) % ph->data->number_of_philosophers;
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
 * @brief Simulates the philosopher eating.
 *
 * @param ph Pointer to the current philosopher.
 */
static void	eat(t_philosopher *ph)
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
static void	pick_up_forks(t_philosopher *ph, pthread_mutex_t *first_fork,
		pthread_mutex_t *second_fork)
{
	pthread_mutex_lock(first_fork);
	print_status(ph->data, ph->id, "has taken a fork");
	pthread_mutex_lock(second_fork);
	print_status(ph->data, ph->id, "has taken a fork");
}

static void	put_down_forks(pthread_mutex_t *first_fork,
							pthread_mutex_t *second_fork)
{
	pthread_mutex_unlock(second_fork);
	pthread_mutex_unlock(first_fork);
}

void	*philosopher_routine(void *arg)
{
	t_philosopher	*ph;
	pthread_mutex_t	*first_fork;
	pthread_mutex_t	*second_fork;

	ph = (t_philosopher *)arg;
	if (ph->data->number_of_philosophers == 1)
	{
		handle_single_philosopher(ph);
		return (NULL);
	}
	if (ph->id % 2 == 1)
		philo_sleep(ph->data, 1);
	get_fork_order(ph, &first_fork, &second_fork);
	while (1)
	{
		if (simulation_stopped(ph->data))
			break ;
		print_status(ph->data, ph->id, "is thinking");
		pick_up_forks(ph, first_fork, second_fork);
		eat(ph);
		put_down_forks(first_fork, second_fork);
		print_status(ph->data, ph->id, "is sleeping");
		philo_sleep(ph->data, ph->data->time_to_sleep);
	}
	return (NULL);
}
