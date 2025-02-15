/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhattab <ykhattab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 01:34:05 by yousef            #+#    #+#             */
/*   Updated: 2025/02/15 02:07:53 by ykhattab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

// Function to initialize mutexes and start philosopher threads
int start_simulation(t_data *data)
{
    pthread_t monitor_thread;
    int i;

    if (init_and_create_thread_philosophers(data))
        return 1;
    if (pthread_create(&monitor_thread, NULL, check_philosophers, (void *)data) != 0)
    {
        printf("Error creating monitor thread.\n");
        return 1;
    }
    pthread_join(monitor_thread, NULL);
    for (i = 0; i < data->number_of_philosophers; i++)
        pthread_join(data->philosophers[i].thread, NULL);
    return 0;
}

/*
mutexes that I lock
print
stop (do we need it? I assume yes, since you don't want multiple trying to stop at the same time)
forks
waiter
meal

*/

/**
 * @brief Initializes all necessary mutexes.
 *
 * This function initializes the print, stop, waiter mutexes and the condition variable.
 * It prints an error message and returns 1 if any initialization fails.
 *
 * @param data Pointer to the simulation data structure.
 * @return int Returns 0 on success, or 1 if any mutex initialization fails.
 */
static int initialize_mutexes(t_data *data)
{
    if (pthread_mutex_init(&data->print_mutex, NULL) != 0)
    {
        printf("Failed to initialize print mutex.\n");
        return 1;
    }
    if (pthread_mutex_init(&data->stop_mutex, NULL) != 0)
    {
        printf("Failed to initialize stop mutex.\n");
        return 1;
    }
    if (pthread_mutex_init(&data->waiter_mutex, NULL) != 0)
    {
        printf("Failed to initialize waiter mutex.\n");
        return 1;
    }
    if (pthread_cond_init(&data->waiter_cond, NULL) != 0)
    {
        printf("Failed to initialize waiter condition.\n");
        return 1;
    }
    return 0;
}

/**
 * @brief Initializes the simulation by parsing arguments and setting up resources.
 *
 * This function parses command-line arguments, initializes the forks, and sets up
 * the simulation environment.
 *
 * @param argc The count of command-line arguments.
 * @param argv The command-line arguments array.
 * @param data Pointer to the simulation data structure.
 * @return int Returns 0 on success, or 1 if any error occurs.
 */
static int initialize_simulation(int argc, char *argv[], t_data *data)
{
    if (parse_arguments(argc, argv, data))
        return 1;
    if (initialize_forks(data))
        return 1;
    data->eating_philosophers = 0;
    return 0;
}

/**
 * @brief Cleans up allocated resources after simulation.
 *
 * This function destroys all mutexes and frees any dynamically allocated memory.
 *
 * @param data Pointer to the simulation data structure.
 */
static void cleanup_simulation(t_data *data)
{
    int i;
    for (i = 0; i < data->number_of_philosophers; i++)
    {
        pthread_mutex_destroy(&data->forks[i]);
        pthread_mutex_destroy(&data->philosophers[i].meal_mutex);
    }
    pthread_mutex_destroy(&data->print_mutex);
    pthread_mutex_destroy(&data->stop_mutex);
    pthread_mutex_destroy(&data->waiter_mutex);
    pthread_cond_destroy(&data->waiter_cond);

    free(data->philosophers);
    free(data->forks);
}

int main(int argc, char *argv[])
{
    t_data data;
    pthread_t print_thread_id;
    data.simulation_stopped = 0;
	init_print_queue(&data.print_queue);
	if (initialize_mutexes(&data))
		return 1;
	if (initialize_simulation(argc, argv, &data))
		return 1;
	if (pthread_create(&print_thread_id, NULL, print_thread, (void *)&data) != 0)
    {
        printf("Error creating print thread.\n");
        return 1;
    }
    if (start_simulation(&data))
        return 1;
	cleanup_simulation(&data);
    return 0;
}
