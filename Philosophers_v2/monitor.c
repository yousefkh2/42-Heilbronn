/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yousef <yousef@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 01:33:45 by yousef            #+#    #+#             */
/*   Updated: 2025/01/24 11:54:54 by yousef           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

// Monitor thread to check for philosopher deaths and meal counts
void *check_philosophers(void *arg)
{
    t_data *data = (t_data *)arg;
    int i;
    long current_time;

    while (1)
    {
		i = 0;
        while (i < data->number_of_philosophers)
        {
            pthread_mutex_lock(&data->philosophers[i].meal_mutex);
            current_time = get_current_time(data);
			// printf("current time: %ld\n", current_time);
            if ((current_time - data->philosophers[i].last_meal_time) > data->time_to_die)
            {
                print_status(data, data->philosophers[i].id, "died");
                
                pthread_mutex_lock(&data->stop_mutex);
                data->simulation_stopped = 1;
                pthread_mutex_unlock(&data->stop_mutex);
                
                pthread_mutex_unlock(&data->philosophers[i].meal_mutex);
                return NULL;
            }
            pthread_mutex_unlock(&data->philosophers[i].meal_mutex);
			i++;
        }

        if (data->number_of_times_each_philosopher_must_eat != -1)
        {
            int all_eaten = 1;
            for (i = 0; i < data->number_of_philosophers; i++)
            {
                pthread_mutex_lock(&data->philosophers[i].meal_mutex);
                if (data->philosophers[i].meals_eaten < data->number_of_times_each_philosopher_must_eat)
                {
                    all_eaten = 0;
                    pthread_mutex_unlock(&data->philosophers[i].meal_mutex);
                    break;
                }
                pthread_mutex_unlock(&data->philosophers[i].meal_mutex);
            }
            if (all_eaten)
            {
                pthread_mutex_lock(&data->stop_mutex);
                data->simulation_stopped = 1;
                pthread_mutex_unlock(&data->stop_mutex);
                return NULL;
            }
        }

        // Check if simulation has been stopped by another thread
        pthread_mutex_lock(&data->stop_mutex);
        if (data->simulation_stopped)
        {
            pthread_mutex_unlock(&data->stop_mutex);
            break;
        }
        pthread_mutex_unlock(&data->stop_mutex);

        usleep(1000); // Check every 1ms to reduce CPU usage
    }
    return NULL;
}


