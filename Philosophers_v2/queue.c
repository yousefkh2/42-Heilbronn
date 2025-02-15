/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhattab <ykhattab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 22:42:07 by ykhattab          #+#    #+#             */
/*   Updated: 2025/02/15 02:14:07 by ykhattab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <string.h>

void init_print_queue(t_print_queue *queue)
{
    queue->head = 0;
    queue->tail = 0;
    pthread_mutex_init(&queue->mutex, NULL);
}

// Add a message to the print queue
void enqueue_message(t_print_queue *queue, long timestamp, int philosopher_id, const char *status)
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
        queue->messages[queue->tail].status = strdup(status);
        queue->tail = (queue->tail + 1) % MAX_QUEUE_SIZE;
    }
    pthread_mutex_unlock(&queue->mutex);
}

// Get the next message from the queue
int dequeue_message(t_print_queue *queue, t_message *message)
{
    pthread_mutex_lock(&queue->mutex);
    if (queue->head == queue->tail)
    {
        pthread_mutex_unlock(&queue->mutex);
        return 0;  // No messages to print
    }
    *message = queue->messages[queue->head];
    queue->head = (queue->head + 1) % MAX_QUEUE_SIZE;
    pthread_mutex_unlock(&queue->mutex);
    return 1;  // Message was retrieved
}
