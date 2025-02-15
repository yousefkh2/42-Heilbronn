/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yousef <yousef@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 22:42:07 by ykhattab          #+#    #+#             */
/*   Updated: 2025/02/15 17:56:58 by yousef           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/** 
 * Initializes the print queue by setting head and tail to 0 
 * and initializing its mutex.
 */
void init_print_queue(t_print_queue *queue)
{
    queue->head = 0;
    queue->tail = 0;
    if (pthread_mutex_init(&queue->mutex, NULL) != 0)
	{
        printf("Failed to initialize queue mutex.\n");
        return;
    }
}

/** 
 * Retrieves the current timestamp and enqueues the given philosopher status message.
 */
// Function to print philosopher status with synchronized access
void print_status(t_data *data, int philosopher_id, char *status)
{
    long timestamp = get_current_time(data);
    enqueue_message(&data->print_queue, timestamp, philosopher_id, status);
}

/**
 * Enqueues a message into the print queue with the provided timestamp, philosopher id, and status.
 * Handles the full-queue scenario if necessary.
 */
void enqueue_message(t_print_queue *queue, long timestamp, int philosopher_id, char *status)
{
    pthread_mutex_lock(&queue->mutex);
    if ((queue->tail + 1) % MAX_QUEUE_SIZE == queue->head)
    {
        // Queue is full, handle this scenario if needed (e.g., drop message or resize queue)
    }
    else
    {
        queue->messages[queue->tail].timestamp = timestamp;
        queue->messages[queue->tail].philosopher_id = philosopher_id;
        queue->messages[queue->tail].status = status;
        queue->tail = (queue->tail + 1) % MAX_QUEUE_SIZE;
    }
    pthread_mutex_unlock(&queue->mutex);
}

/**
 * Dequeues the next message from the print queue.
 * Returns 1 after retrieving a message, or 0 if the queue is empty.
 */
int dequeue_message(t_print_queue *queue, t_message *message)
{
    pthread_mutex_lock(&queue->mutex);
    if (queue->head == queue->tail)
    {
        pthread_mutex_unlock(&queue->mutex);
        return 0;
    }
    *message = queue->messages[queue->head];
    queue->head = (queue->head + 1) % MAX_QUEUE_SIZE;
    pthread_mutex_unlock(&queue->mutex);
    return 1;
}

/**
 * Thread function that continuously polls the print queue to print messages
 * until the simulation is stopped.
 */
void *print_thread(void *arg)
{
    t_data *data = (t_data *)arg;
    t_message message;
	int should_continue = 1;
	
    while (should_continue)
    {
		pthread_mutex_lock(&data->stop_mutex);
        should_continue = !data->simulation_stopped;
        pthread_mutex_unlock(&data->stop_mutex);

		if (!should_continue)
            break;
        if (dequeue_message(&data->print_queue, &message))
        {
            printf("%ld %d %s\n", message.timestamp, message.philosopher_id, message.status);
        }
		else
		{
			// usleep(101);
		}
    }
	// pthread_mutex_lock(&data->print_queue.mutex);
    // // Finish any last messages if needed
    // pthread_mutex_unlock(&data->print_queue.mutex);
    return NULL;
}