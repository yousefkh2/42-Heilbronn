/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhattab <ykhattab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 01:32:35 by yousef            #+#    #+#             */
/*   Updated: 2025/02/16 06:02:35 by ykhattab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"


static int is_digit(char c) {
    return c >= '0' && c <= '9';
}

/**
 * @brief Validates if a given string represents a positive number.
 *
 * It checks if the string is a valid positive number. It allows an
 * optional '+' sign at the beginning and ensures that the rest of the string
 * consists solely of digits.
 *
 * @param str The input string.
 * @return int Returns 1 if the string is a valid positive number, 0 otherwise.
 */
static int is_positive_number(const char *str) {
    int i = 0;

    if (str[i] == '+')
        i++;
    if (!str[i])
        return 0;
    while (str[i]) {
        if (!is_digit((unsigned char)str[i]))
            return 0;
        i++;
    }
    return 1;
}


/**
 * @brief Parses the command-line arguments to initialize simulation parameters.
 *
 * This function validates the number of arguments, checks if each argument is a
 * valid positive number, and initializes the t_data structure with the provided
 * simulation parameters. It also prints usage information or error messages if needed.
 *
 * @param argc The count of command-line arguments.
 * @param argv The array of command-line arguments.
 * @param data Pointer to the simulation data structure to be initialized.
 * @return int Returns 0 on success, or 1 if there was an error.
 */
int parse_arguments(int argc, char **argv, t_data *data)
{
	int i = 1;
    if (argc < 5 || argc > 6)
    {
        printf("Usage: ./philosophers <number_of_philosophers> <time_to_die> ");
        printf("<time_to_eat> <time_to_sleep> [number_of_times_each_philosopher_must_eat]\n");
        return 1;
    }

	while (i < argc)
    {
        if (!is_positive_number(argv[i]))
        {
            printf("Error: Argument %d ('%s') is not a valid positive number.\n", i, argv[i]);
            return 1;
        }
		i++;
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

/**
 * @brief Allocates memory for the philosopher structures.
 *
 * This function allocates memory to store the philosopher information for each
 * philosopher in the simulation.
 *
 * @param data Pointer to the simulation data structure.
 * @return int Returns 0 on success, or 1 if memory allocation fails.
 */
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


/**
 * @brief Initializes all philosopher structures and creates their threads.
 *
 * This function allocates memory for the philosophers, sets the simulation's start
 * time, initializes each philosopher, and creates a thread for each philosopher's
 * routine. It returns an error if any of these steps fail.
 *
 * @param data Pointer to the simulation data structure.
 * @return int Returns 0 on success, or 1 if there was an error.
 */
int	init_and_create_thread_philosophers(t_data *data)
{
    int i;
    if (allocate_philosophers(data) != 0)
			return 1;
	gettimeofday(&data->time_start, NULL);
	data->start_time = data->time_start.tv_sec * 1000 + data->time_start.tv_usec / 1000;
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
