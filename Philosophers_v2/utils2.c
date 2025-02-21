/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhattab <ykhattab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 22:54:41 by ykhattab          #+#    #+#             */
/*   Updated: 2025/02/21 00:57:59 by ykhattab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	is_digit(char c)
{
	return (c >= '0' && c <= '9');
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
int	is_positive_number(const char *str)
{
	int	i;

	i = 0;
	if (str[i] == '+')
		i++;
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (!is_digit((unsigned char)str[i]))
			return (0);
		i++;
	}
	return (1);
}

/**
 * @brief Parses the command-line arguments to initialize simulation parameters.
 *
 * This function validates the number of arguments, checks if each argument is a
 * valid positive number, and initializes the t_data structure with the provided

 *
 * @param argc The count of command-line arguments.
 * @param argv The array of command-line arguments.
 * @param data Pointer to the simulation data structure to be initialized.
 * @return int Returns 0 on success, or 1 if there was an error.
 */
int	parse_arguments(int argc, char **argv, t_data *data)
{
	int	i;

	i = 1;
	if (argc < 5 || argc > 6)
	{
		printf("Usage: ./philosophers <number_of_philosophers> \
		<time_to_die>");
		printf("<time_to_eat> <time_to_sleep> \
		[number_of_times_each_philosopher_must_eat]\n");
		return (1);
	}
	while (i < argc)
	{
		if (!is_positive_number(argv[i]))
		{
			printf("Error: Argument %d ('%s') is not a valid \
			positive number.\n", i, argv[i]);
			return (1);
		}
		i++;
	}
	if (initialize_data(argc, argv, data))
		return (1);
	return (0);
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
int	allocate_philosophers(t_data *data)
{
	data->philosophers = malloc(data->number_of_philosophers
			* sizeof(t_philosopher));
	if (!data->philosophers)
	{
		printf("Memory allocation for philosophers failed!\n");
		return (1);
	}
	return (0);
}

int	ft_atoi(const char *str)
{
	int	sign;
	int	result;

	sign = 1;
	result = 0;
	while (*str == ' ' || *str == '\t' || *str == '\n'
		|| *str == '\v' || *str == '\f' || *str == '\r')
	{
		str++;
	}
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
		{
			sign = -1;
		}
		str++;
	}
	while (*str && is_digit(*str))
	{
		result = result * 10 + (*str - '0');
		str++;
	}
	return (sign * result);
}
