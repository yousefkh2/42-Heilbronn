/* philosophers.h */

#ifndef PHILOSOPHERS_H
#define PHILOSOPHERS_H

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>
#include <unistd.h>

// Structure to hold philosopher data
typedef struct s_philosopher
{
    int             id;
    long            last_meal_time;
    int             meals_eaten;
    pthread_mutex_t *left_fork;
    pthread_mutex_t *right_fork;
    pthread_t       thread;
	pthread_mutex_t meal_mutex;
    struct s_data   *data;
}               t_philosopher;

// Structure to hold simulation data
typedef struct s_data
{
    int             number_of_philosophers;
    long            time_to_die;
    long            time_to_eat;
    long            time_to_sleep;
    int             number_of_times_each_philosopher_must_eat;
    long            start_time;
    int             simulation_stopped;
    pthread_mutex_t stop_mutex;
    pthread_mutex_t *forks;
    pthread_mutex_t print_mutex;
    t_philosopher   *philosophers;

    // Waiter variables
    pthread_mutex_t waiter_mutex;
    pthread_cond_t  waiter_cond;
    int             eating_philosophers; // number of philosophers currently eating
} t_data;


// Function declarations

// Initialization functions
int     parse_arguments(int argc, char **argv, t_data *data);
int     initialize_forks(t_data *data);
int     initialize_philosophers(t_data *data);

// Philosopher routines
void    *philosopher_routine(void *arg);

// Monitor routines
void    *check_philosophers(void *arg);

// Utility functions
long    get_current_time(void);
void    print_status(t_data *data, int philosopher_id, char *status);
void sim_start_delay(long start_time);
void philo_sleep(t_data *data, long sleep_time_ms);
#endif
