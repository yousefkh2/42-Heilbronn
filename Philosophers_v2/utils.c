/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhattab <ykhattab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 01:32:16 by yousef            #+#    #+#             */
/*   Updated: 2025/02/21 00:55:58 by ykhattab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

long	get_current_time(t_data *data)
{
	struct timeval	current;
	long			now;
	long			result;

	gettimeofday(&current, NULL);
	now = current.tv_sec * 1000 + current.tv_usec / 1000;
	result = now - data->start_time;
	return (result);
}

/**
 * philo_sleep - Makes the philosopher sleep for a specified amount of time.
 * 

	* This function puts the philosopher to sleep 
	* for the given duration in milliseconds.
 	* During the sleep period,
	it periodically checks if the simulation has been stopped.
 	* If the simulation is stopped,
	the function will break out of the sleep loop early.
	* The sleep is performed in increments 
	of 100 microseconds to allow frequent checks.
 * 
	* @param data: Pointer to the shared data structure 
		containing simulation state.
 	* @param sleep_time_ms: The duration of sleep in milliseconds.
 */
void	philo_sleep(t_data *data, long sleep_time_ms)
{
	long	wake_up;
	int		stop;

	wake_up = get_current_time(data) + sleep_time_ms;
	while (get_current_time(data) < wake_up)
	{
		pthread_mutex_lock(&data->stop_mutex);
		stop = data->simulation_stopped;
		pthread_mutex_unlock(&data->stop_mutex);
		if (stop)
			break ;
		usleep(100);
	}
}

void	handle_single_philosopher(t_philosopher *ph)
{
	pthread_mutex_lock(&ph->data->forks[ph->id - 1]);
	print_status(ph->data, ph->id, "has taken a fork");
	pthread_mutex_unlock(&ph->data->forks[ph->id - 1]);
	philo_sleep(ph->data, ph->data->time_to_die);
	print_status(ph->data, ph->id, "died");
	pthread_mutex_lock(&ph->data->stop_mutex);
	ph->data->simulation_stopped = 1;
	pthread_mutex_unlock(&ph->data->stop_mutex);
}

/**
 * @brief Checks whether the simulation has been stopped.
 *
 * This function locks the stop mutex, reads the simulation_stopped flag,
 * and then unlocks the mutex.
 *
 * @param data Pointer to the shared simulation data.
 * @return int Returns non-zero if the simulation is stopped.
 */
int	simulation_stopped(t_data *data)
{
	int	stopped;

	pthread_mutex_lock(&data->stop_mutex);
	stopped = data->simulation_stopped;
	pthread_mutex_unlock(&data->stop_mutex);
	return (stopped);
}

int	ft_strncmp(const char *str1, const char *str2, size_t n)
{
	size_t	count;

	count = 0;
	while (*str1 && *str2 && count < n)
	{
		if (*str1 != *str2)
		{
			return ((unsigned char)*str1 - (unsigned char)*str2);
		}
		str1++;
		str2++;
		count++;
	}
	if (count < n)
	{
		return ((unsigned char)*str1 - (unsigned char)*str2);
	}
	return (0);
}