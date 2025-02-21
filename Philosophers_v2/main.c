/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhattab <ykhattab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 01:34:05 by yousef            #+#    #+#             */
/*   Updated: 2025/02/20 22:35:10 by ykhattab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

// Function to initialize mutexes and start philosopher threads
int	start_simulation(t_data *data, pthread_t print_thread_id)
{
	pthread_t	monitor_thread;
	int			i;

	if (init_and_create_thread_philosophers(data))
		return (1);
	if (pthread_create(&monitor_thread, NULL, check_philosophers,
			(void *)data) != 0)
	{
		printf("Error creating monitor thread.\n");
		return (1);
	}
	pthread_join(monitor_thread, NULL);
	i = 0;
	while (i < data->number_of_philosophers)
	{
		pthread_join(data->philosophers[i].thread, NULL);
		i++;
	}
	pthread_join(print_thread_id, NULL);
	return (0);
}

/**
 * @brief Initializes all necessary mutexes.
 *
 * This function initializes the queue, print, stop,
	waiter mutexes and the condition variable.
 * It prints an error message and returns 1 if any initialization fails.
 *
 * @param data Pointer to the simulation data structure.
 * @return int Returns 0 on success, or 1 if any mutex initialization fails.
 */
static int	initialize_mutexes(t_data *data)
{
	init_print_queue(&data->print_queue);
	if (pthread_mutex_init(&data->stop_mutex, NULL) != 0)
	{
		printf("Failed to initialize stop mutex.\n");
		return (1);
	}
	return (0);
}

/**
 *
 * This function parses command-line arguments, initializes the forks,
	and sets up
 * the simulation environment.
 *
 * @param argc The count of command-line arguments.
 * @param argv The command-line arguments array.
 * @param data Pointer to the simulation data structure.
 * @return int Returns 0 on success, or 1 if any error occurs.
 */
static int	initialize_simulation(int argc, char *argv[], t_data *data)
{
	if (parse_arguments(argc, argv, data))
		return (1);
	if (initialize_forks(data))
		return (1);
	data->eating_philosophers = 0;
	data->death_printed = 0;
	return (0);
}

static void	cleanup_simulation(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->number_of_philosophers)
	{
		pthread_mutex_destroy(&data->forks[i]);
		pthread_mutex_destroy(&data->philosophers[i].meal_mutex);
		i++;
	}
	pthread_mutex_destroy(&data->stop_mutex);
	pthread_mutex_destroy(&data->print_queue.mutex);
	free(data->philosophers);
	free(data->forks);
}

int	main(int argc, char *argv[])
{
	t_data		*data;
	pthread_t	print_thread_id;

	data = malloc(sizeof(t_data));
	if (!data)
	{
		printf("Failed to allocate memory for t_data\n");
		return (1);
	}
	data->simulation_stopped = 0;
	data->simulation_complete = 0;
	if (initialize_mutexes(data))
		return (1);
	if (initialize_simulation(argc, argv, data))
		return (1);
	if (pthread_create(&print_thread_id, NULL, print_thread, (void *)data) != 0)
	{
		printf("Error creating print thread.\n");
		return (1);
	}
	if (start_simulation(data, print_thread_id))
		return (1);
	cleanup_simulation(data);
	free(data);
	return (0);
}
