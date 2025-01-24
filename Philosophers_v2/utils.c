/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yousef <yousef@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 01:32:16 by yousef            #+#    #+#             */
/*   Updated: 2025/01/24 11:54:23 by yousef           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

// Function to get the current timestamp in milliseconds
long get_current_time(t_data *data)
{
    struct timeval current;
    long now;

    gettimeofday(&current, NULL);
    now = current.tv_sec * 1000 + current.tv_usec / 1000;
    return (now - data->start_time); 
}
//

// Function to print philosopher status with synchronized access
void print_status(t_data *data, int philosopher_id, char *status)
{
    long timestamp;

    pthread_mutex_lock(&data->print_mutex);
    // Check if simulation is stopped
    pthread_mutex_lock(&data->stop_mutex);
    if (data->simulation_stopped)
    {
        pthread_mutex_unlock(&data->stop_mutex);
        pthread_mutex_unlock(&data->print_mutex);
        return;
    }
    pthread_mutex_unlock(&data->stop_mutex);

    timestamp = get_current_time(data);
    printf("%ld %d %s\n", timestamp, philosopher_id, status);
    pthread_mutex_unlock(&data->print_mutex);
}

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
        usleep(100); // Sleep in small increments
    }
}

// void sim_start_delay(t_data *data, long start_time)
// {
//     while (get_current_time(data) < start_time)
//         usleep(100);
// }
