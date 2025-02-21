/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhattab <ykhattab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 22:12:20 by ykhattab          #+#    #+#             */
/*   Updated: 2025/02/21 00:56:27 by ykhattab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

# define MAX_QUEUE_SIZE 1000

typedef struct s_message
{
	long			timestamp;
	int				philosopher_id;
	char			*status;
}					t_message;

typedef struct s_print_queue
{
	t_message		messages[MAX_QUEUE_SIZE];
	int				head;
	int				tail;
	pthread_mutex_t	mutex;
}					t_print_queue;

// Structure to hold philosopher data
typedef struct s_philosopher
{
	int				id;
	long			last_meal_time;
	int				meals_eaten;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_t		thread;
	pthread_mutex_t	meal_mutex;
	struct s_data	*data;
}					t_philosopher;

// Structure to hold simulation data
typedef struct s_data
{
	int				number_of_philosophers;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	int				number_of_times_each_philosopher_must_eat;
	long			start_time;
	struct timeval	time_start;
	int				simulation_stopped;
	int				simulation_complete;
	pthread_mutex_t	stop_mutex;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print_mutex;
	t_philosopher	*philosophers;
	t_print_queue	print_queue;
	int				death_printed;
	int				eating_philosophers;
}					t_data;

void				init_print_queue(t_print_queue *queue);
int					parse_arguments(int argc, char **argv, t_data *data);
int					initialize_forks(t_data *data);
int					initialize_data(int argc, char **argv, t_data *data);
int					init_and_create_thread_philosophers(t_data *data);
int					initialize_philosopher(t_philosopher *philosopher,
						t_data *data, int id);
int					is_digit(char c);
int					is_positive_number(const char *str);
int					allocate_philosophers(t_data *data);
int					ft_strncmp(const char *str1, const char *str2, size_t n);
int					ft_atoi(const char *str);

// Philosopher routines
void				*philosopher_routine(void *arg);
void				*print_thread(void *arg);
// Monitor routines
void				*check_philosophers(void *arg);
int					simulation_stopped(t_data *data);
void				handle_single_philosopher(t_philosopher *ph);

// Utility functions
long				get_current_time(t_data *data);
void				print_status(t_data *data, int philosopher_id,
						char *status);
// void sim_start_delay(long start_time);
void				philo_sleep(t_data *data, long sleep_time_ms);
//queue functions
void				enqueue_message(t_print_queue *queue, long timestamp,
						int philosopher_id, char *status);
int					dequeue_message(t_print_queue *queue, t_message *message);

#endif
