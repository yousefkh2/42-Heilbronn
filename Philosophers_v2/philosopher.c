/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhattab <ykhattab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 01:33:13 by yousef            #+#    #+#             */
/*   Updated: 2025/01/24 01:07:04 by ykhattab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"


// Philosopher thread routine
// Philosopher thread routine
void *philosopher_routine(void *arg)
{
    t_philosopher *ph = (t_philosopher *)arg;
    pthread_mutex_t *first_fork;
	pthread_mutex_t *second_fork;
    long time_to_think;

    // Wait until all threads have been created and the start time has been reached
    // sim_start_delay(ph->data->start_time);

    // Initialize last_meal_time
    // pthread_mutex_lock(&ph->meal_mutex);
    // ph->last_meal_time = get_current_time();
    // pthread_mutex_unlock(&ph->meal_mutex);

    // Small initial stagger if even
    if (ph->id % 2 == 0)
        philo_sleep(ph->data, 1);

    // Determine fork order
    // if (ph->left_fork < ph->right_fork)
    // {
    //     first_fork = ph->left_fork;
    //     second_fork = ph->right_fork;
    // }
    // else
    // {
    //     first_fork = ph->right_fork;
    //     second_fork = ph->left_fork;
    // }
	int left_id = ph->id - 1;
    int right_id = (ph->id) % ph->data->number_of_philosophers;
	if (left_id < right_id) {
		first_fork = &ph->data->forks[left_id];
		second_fork = &ph->data->forks[right_id];
	} else {
		first_fork = &ph->data->forks[right_id];
		second_fork = &ph->data->forks[left_id];
	}

    while (1)
    {
        // Check stop condition often
        pthread_mutex_lock(&ph->data->stop_mutex);
        if (ph->data->simulation_stopped)
        {
            pthread_mutex_unlock(&ph->data->stop_mutex);
            break;
        }
        pthread_mutex_unlock(&ph->data->stop_mutex);

        // Thinking
        print_status(ph->data, ph->id, "is thinking");

        // Compute time_to_think as before
        pthread_mutex_lock(&ph->meal_mutex);
        long time_since_last_meal = get_current_time() - ph->last_meal_time;
        pthread_mutex_unlock(&ph->meal_mutex);

        // time_to_think = (ph->data->time_to_die - time_since_last_meal - ph->data->time_to_eat) / 2;
        // if (time_to_think < 0)
        //     time_to_think = 0;
        // if (time_to_think > 600)
        //     time_to_think = 200;
		// there shouldn't time to think here. wrong assumption.

        // Use philo_sleep instead of usleep
        philo_sleep(ph->data, time_to_think);
		// Wait for permission from the waiter
		pthread_mutex_lock(&ph->data->waiter_mutex);
		while (ph->data->eating_philosophers == ph->data->number_of_philosophers - 1)
		{
			// All but one philosopher are allowed to try eating
			// If this philosopher tried now, it could create a deadlock scenario.
			pthread_cond_wait(&ph->data->waiter_cond, &ph->data->waiter_mutex);
		}
		ph->data->eating_philosophers++;
		pthread_mutex_unlock(&ph->data->waiter_mutex);
        // Take forks
        pthread_mutex_lock(first_fork);
        print_status(ph->data, ph->id, "has taken a fork");
        pthread_mutex_lock(second_fork);
        print_status(ph->data, ph->id, "has taken a fork");

        // Eat
        pthread_mutex_lock(&ph->meal_mutex);
        ph->last_meal_time = get_current_time();
        print_status(ph->data, ph->id, "is eating");
        pthread_mutex_unlock(&ph->meal_mutex);

        philo_sleep(ph->data, ph->data->time_to_eat);
        
        pthread_mutex_lock(&ph->meal_mutex);
        ph->meals_eaten++;
        pthread_mutex_unlock(&ph->meal_mutex);

        // Put down forks
        pthread_mutex_unlock(second_fork);
        pthread_mutex_unlock(first_fork);

		// Signal the waiter that this philosopher has finished eating
		pthread_mutex_lock(&ph->data->waiter_mutex);
		ph->data->eating_philosophers--;
		pthread_cond_broadcast(&ph->data->waiter_cond);
		pthread_mutex_unlock(&ph->data->waiter_mutex);
		
        // Sleep
        print_status(ph->data, ph->id, "is sleeping");
        philo_sleep(ph->data, ph->data->time_to_sleep);
    }

    return NULL;
}


