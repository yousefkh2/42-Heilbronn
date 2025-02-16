/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhattab <ykhattab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 01:32:16 by yousef            #+#    #+#             */
/*   Updated: 2025/02/16 01:48:32 by ykhattab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

// Function to get the current timestamp in milliseconds
long get_current_time(t_data *data)
{
    struct timeval current;
    long now;
	long result;

    gettimeofday(&current, NULL);
    now = current.tv_sec * 1000 + current.tv_usec / 1000;
	result = now - data->start_time;
    return (result); 
}

/**
 * philo_sleep - Makes the philosopher sleep for a specified amount of time.
 * 
 * This function puts the philosopher to sleep for the given duration in milliseconds.
 * During the sleep period, it periodically checks if the simulation has been stopped.
 * If the simulation is stopped, the function will break out of the sleep loop early.
 * The sleep is performed in increments of 100 microseconds to allow frequent checks.
 * 
 * @param data: Pointer to the shared data structure containing simulation state.
 * @param sleep_time_ms: The duration of sleep in milliseconds.
 */
void philo_sleep(t_data *data, long sleep_time_ms)
{
    long wake_up = get_current_time(data) + sleep_time_ms;
    while (get_current_time(data) < wake_up)
    {
        pthread_mutex_lock(&data->stop_mutex);
        int stop = data->simulation_stopped;
        pthread_mutex_unlock(&data->stop_mutex);
        if (stop)
            break;
        usleep(1000); // sleep in increments of 100 microseconds
    }
}


// void sim_start_delay(t_data *data, long start_time)
// {
//     while (get_current_time(data) < start_time)
//         usleep(100);
// }



