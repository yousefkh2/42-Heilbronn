/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yousef <yousef@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 01:34:05 by yousef            #+#    #+#             */
/*   Updated: 2024/12/15 02:57:22 by yousef           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

// Function to initialize mutexes and start philosopher threads
int start_simulation(t_data *data)
{
    pthread_t monitor_thread;
    int i;

    
    if (initialize_philosophers(data))
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

int main(int argc, char *argv[])
{
    t_data data;
    int i;

    // Initialize simulation stopped flag
    data.simulation_stopped = 0;
    // Initialize mutexes
    if (pthread_mutex_init(&data.print_mutex, NULL) != 0)
    {
        printf("Failed to initialize print mutex.\n");
        return 1;
    }
	if (pthread_mutex_init(&data.stop_mutex, NULL) != 0)
	{
		printf("Failed to initialized stop mutex. \n");
		return 1;
	}
    // if (pthread_mutex_init(&data.meal_mutex, NULL) != 0)
    // {
    //     printf("Failed to initialize meal mutex.\n");
    //     return 1;
    // }
    // Parse command-line arguments
    if (parse_arguments(argc, argv, &data))
    {
        return 1;
    }
    // Initialize forks
    if (initialize_forks(&data))
    {
        return 1;
    }

	if (pthread_mutex_init(&data.waiter_mutex, NULL) != 0)
	{
		printf("Failed to initialize waiter mutex.\n");
		return 1;
	}
	if (pthread_cond_init(&data.waiter_cond, NULL) != 0)
	{
		printf("Failed to initialize waiter condition.\n");
		return 1;
	}

	data.eating_philosophers = 0;
    // Start simulation
    if (start_simulation(&data))
    {
        return 1;
    }
    // Cleanup
	for (i = 0; i < data.number_of_philosophers; i++)
	{
		pthread_mutex_destroy(&data.forks[i]);
		pthread_mutex_destroy(&data.philosophers[i].meal_mutex);
	}
	pthread_mutex_destroy(&data.print_mutex);
	pthread_mutex_destroy(&data.stop_mutex);
	free(data.philosophers);
	free(data.forks);

    return 0;
}
