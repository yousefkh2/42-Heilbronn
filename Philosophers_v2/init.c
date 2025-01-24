/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhattab <ykhattab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 01:32:35 by yousef            #+#    #+#             */
/*   Updated: 2025/01/24 00:32:50 by ykhattab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

// Function to parse command-line arguments
int parse_arguments(int argc, char **argv, t_data *data)
{
    if (argc < 5 || argc > 6)
    {
        printf("Usage: ./philosophers <number_of_philosophers> <time_to_die> ");
        printf("<time_to_eat> <time_to_sleep> [number_of_times_each_philosopher_must_eat]\n");
        return 1;
    }
    data->number_of_philosophers = atoi(argv[1]);
    if (data->number_of_philosophers <= 0)
        return 1;
    data->time_to_die = atol(argv[2]); // I think i might need to add atol to libft if it's not there
    data->time_to_eat = atol(argv[3]);
    data->time_to_sleep = atol(argv[4]);
    if (argc == 6)
        data->number_of_times_each_philosopher_must_eat = atoi(argv[5]);
    else
        data->number_of_times_each_philosopher_must_eat = -1;
    return 0;
}

// Function to initialize fork mutexes
int initialize_forks(t_data *data)
{
    int i;

	i = 0;

    data->forks = malloc(data->number_of_philosophers * sizeof(pthread_mutex_t));
    if (!data->forks)
    {
        printf("Memory allocation for forks failed!\n");
        return 1;
    }
    while (i < data->number_of_philosophers)
    {
        if (pthread_mutex_init(&data->forks[i], NULL) != 0)
        {
            printf("Failed to initialize fork mutex %d.\n", i);
            return 1;
        }
		i++;
    }
    return 0;
}
int allocate_philosophers(t_data *data)
{
    data->philosophers = malloc(data->number_of_philosophers * sizeof(t_philosopher));
    if (!data->philosophers)
    {
        printf("Memory allocation for philosophers failed!\n");
        return 1;
    }
    return 0;
}


int initialize_philosopher(t_philosopher *philosopher, t_data *data, int id)
{
    philosopher->id = id + 1;
    philosopher->meals_eaten = 0;
    philosopher->left_fork = &data->forks[id];
    philosopher->right_fork = &data->forks[(id + 1) % data->number_of_philosophers];
    philosopher->data = data;

    if (pthread_mutex_init(&philosopher->meal_mutex, NULL) != 0)
    {
        perror("Failed to initialize philosopher's meal mutex");
        return 1;
    }
    	philosopher->last_meal_time = data->start_time;
    return 0;
}


// Function to initialize philosopher data and create philosopher threads
int initialize_philosophers(t_data *data)
{
    int i;
    if (allocate_philosophers(data) != 0)
        return 1;
	gettimeofday(&data->time_start, NULL);
	data->start_time = data->time_start.tv_sec * 1000 
                 + data->time_start.tv_usec / 1000;
	i = 0;
    while (i < data->number_of_philosophers)
    {
		if (initialize_philosopher(&data->philosophers[i], data, i))
			return 1;
        
		if (pthread_create(&data->philosophers[i].thread, NULL, philosopher_routine, (void *)&data->philosophers[i]) != 0)
        {
            perror("Failed to create philosopher thread");
            return 1;
        }
		i++;
    }
    return 0;
}
