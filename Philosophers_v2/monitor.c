/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yousef <yousef@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 01:33:45 by yousef            #+#    #+#             */
/*   Updated: 2025/02/15 16:26:30 by yousef           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/**
 * @brief Checks if any philosopher has died.
 *
 * Iterates through philosophers, and if the time since the last meal
 * exceeds time_to_die, it prints the death status and stops the simulation.
 *
 * @param data Pointer to the simulation data structure.
 * @return int 1 if a philosopher died, 0 otherwise.
 */
static int check_for_deaths(t_data *data)
{
    int i;
    long current_time;

    i = 0;
    while (i < data->number_of_philosophers)
    {
        pthread_mutex_lock(&data->philosophers[i].meal_mutex);
        current_time = get_current_time(data);
        if ((current_time - data->philosophers[i].last_meal_time) > data->time_to_die)
        {
            print_status(data, data->philosophers[i].id, "died");
            pthread_mutex_lock(&data->stop_mutex);
            data->simulation_stopped = 1;
            pthread_mutex_unlock(&data->stop_mutex);
            pthread_mutex_unlock(&data->philosophers[i].meal_mutex);
            return 1;
        }
        pthread_mutex_unlock(&data->philosophers[i].meal_mutex);
        i++;
    }
    return 0;
}

/**
 * @brief Checks if all philosophers have eaten the required number of times.
 *
 * If each philosopher's meals_eaten is greater than or equal to the
 * required count, the simulation is stopped.
 *
 * @param data Pointer to the simulation data structure.
 * @return int 1 if all philosophers have eaten enough, 0 otherwise.
 */
static int check_if_all_ate(t_data *data)
{
    int i;

    if (data->number_of_times_each_philosopher_must_eat == -1)
        return 0;

    i = 0;
    while (i < data->number_of_philosophers)
    {
        pthread_mutex_lock(&data->philosophers[i].meal_mutex);
        if (data->philosophers[i].meals_eaten < data->number_of_times_each_philosopher_must_eat)
        {
            pthread_mutex_unlock(&data->philosophers[i].meal_mutex);
            return 0;
        }
        pthread_mutex_unlock(&data->philosophers[i].meal_mutex);
        i++;
    }
    pthread_mutex_lock(&data->stop_mutex);
    data->simulation_stopped = 1;
    pthread_mutex_unlock(&data->stop_mutex);
    return 1;
}

/**
 * @brief Determines whether the simulation should stop.
 *
 * Checks both philosopher deaths and meal counts to decide if the simulation
 * should be halted.
 *
 * @param data Pointer to the simulation data structure.
 * @return int 1 if the simulation should stop, 0 otherwise.
 */
static int should_stop_simulation(t_data *data)
{
    if (check_for_deaths(data))
        return 1;
    if (check_if_all_ate(data))
        return 1;
    return 0;
}
/**
 * @brief The monitor thread that continuously checks the philosophers' statuses.
 *
 * This function checks the status of philosophers in a loop: looking for deaths
 * or ensuring all philosophers have eaten the required number of meals. The thread
 * stops when one of these conditions is met.
 *
 * @param arg Pointer to the simulation data structure.
 * @return void* Always returns NULL.
 */
void *check_philosophers(void *arg)
{
    t_data *data = (t_data *)arg;

    while (1)
    {
        if (should_stop_simulation(data))
            break;
        pthread_mutex_lock(&data->stop_mutex);
        if (data->simulation_stopped)
        {
            pthread_mutex_unlock(&data->stop_mutex);
            break;
        }
        pthread_mutex_unlock(&data->stop_mutex);
        usleep(1000);
    }
    return NULL;
}
