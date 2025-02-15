/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhattab <ykhattab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 01:32:16 by yousef            #+#    #+#             */
/*   Updated: 2025/02/15 01:53:31 by ykhattab         ###   ########.fr       */
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
    long timestamp = get_current_time(data);
    enqueue_message(&data->print_queue, timestamp, philosopher_id, status);
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
        usleep(100); // sleep in increments of 100 microseconds
    }
}

// void sim_start_delay(t_data *data, long start_time)
// {
//     while (get_current_time(data) < start_time)
//         usleep(100);
// }

void *print_thread(void *arg)
{
    t_data *data = (t_data *)arg;
    t_message message;

    while (!data->simulation_stopped)
    {
        if (dequeue_message(&data->print_queue, &message))
        {
            printf("%ld %d %s\n", message.timestamp, message.philosopher_id, message.status);
            free(message.status);  // Don't forget to free the memory allocated for status
        }
        usleep(1000);  // Adjust this to control how often to print
    }
    return NULL;
}
