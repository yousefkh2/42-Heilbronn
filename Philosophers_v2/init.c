/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhattab <ykhattab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 01:32:35 by yousef            #+#    #+#             */
/*   Updated: 2025/02/21 01:05:13 by ykhattab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	initialize_data(int argc, char **argv, t_data *data)
{
	data->number_of_philosophers = ft_atoi(argv[1]);
	if (data->number_of_philosophers <= 0)
		return (1);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		data->number_of_times_each_philosopher_must_eat = ft_atoi(argv[5]);
	else
		data->number_of_times_each_philosopher_must_eat = -1;
	return (0);
}

/**
 * @brief Initializes the mutexes representing the forks.
 *
 * Allocates memory for the fork mutexes based on the number of philosophers and
 * initializes each mutex. If memory allocation or mutex initialization fails,
 * an error message is printed.
 *
 * @param data Pointer to the simulation data structure.
 * @return int Returns 0 on success, or 1 if there was an error.
 */
int	initialize_forks(t_data *data)
{
	int	i;

	i = 0;
	data->forks = malloc(data->number_of_philosophers
			* sizeof(pthread_mutex_t));
	if (!data->forks)
	{
		printf("Memory allocation for forks failed!\n");
		return (1);
	}
	while (i < data->number_of_philosophers)
	{
		if (pthread_mutex_init(&data->forks[i], NULL) != 0)
		{
			printf("Failed to initialize fork mutex %d.\n", i);
			return (1);
		}
		i++;
	}
	return (0);
}

/** 
 * Initializes the print queue by setting head and tail to 0 
 * and initializing its mutex.
 */
void	init_print_queue(t_print_queue *queue)
{
	queue->head = 0;
	queue->tail = 0;
	if (pthread_mutex_init(&queue->mutex, NULL) != 0)
	{
		printf("Failed to initialize queue mutex.\n");
		return ;
	}
}

/**
 * @brief Initializes a single philosopher's data and associated mutex.
 *
 * Sets up the philosopher's ID, initial meal count, fork pointers, and data
 * reference. It also initializes the mutex used to protect the philosopher's
 * meal-related data and sets the last meal time to the simulation start time.
 *
 * @param philosopher Pointer to the philosopher structure to initialize.
 * @param data Pointer to the simulation data structure.
 * @param id The index of the philosopher.
 * @return int Returns 0 on success, or 1 if mutex initialization fails.
 */
int	initialize_philosopher(t_philosopher *philosopher, t_data *data, int id)
{
	philosopher->id = id + 1;
	philosopher->meals_eaten = 0;
	philosopher->left_fork = &data->forks[id];
	philosopher->right_fork = &data->forks[(id + 1)
		% data->number_of_philosophers];
	philosopher->data = data;
	if (pthread_mutex_init(&philosopher->meal_mutex, NULL) != 0)
	{
		printf("Failed to initialize philosopher's meal mutex");
		return (1);
	}
	philosopher->last_meal_time = data->start_time;
	return (0);
}

/**
 * @brief Initializes all philosopher structures and creates their threads.
 *
 * This function allocates memory for the philosophers,
	sets the simulation's start
 * time, initializes each philosopher,
	and creates a thread for each philosopher's
 * routine. It returns an error if any of these steps fail.
 *
 * @param data Pointer to the simulation data structure.
 * @return int Returns 0 on success, or 1 if there was an error.
 */
int	init_and_create_thread_philosophers(t_data *data)
{
	int	i;

	if (allocate_philosophers(data) != 0)
		return (1);
	gettimeofday(&data->time_start, NULL);
	data->start_time = data->time_start.tv_sec * 1000 + data->time_start.tv_usec
		/ 1000;
	i = 0;
	while (i < data->number_of_philosophers)
	{
		if (initialize_philosopher(&data->philosophers[i], data, i))
			return (1);
		if (pthread_create(&data->philosophers[i].thread, NULL,
				philosopher_routine, (void *)&data->philosophers[i]) != 0)
		{
			printf("Failed to create philosopher thread");
			return (1);
		}
		i++;
	}
	return (0);
}
