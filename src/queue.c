/* 
 * File: queue.c
 * Purpose: This file contains the Queue implementation.
 */

#include "queue.h"
#include "common.h"
#include <pthread.h>

pthread_mutex_t queue_update_mutex; // Mutex for synchronisation

/* Method to initialize the Queue */
QUEUE * initializeQueue()
{
    printf("Queue: Initializing Queue\n");
    QUEUE *q = malloc(sizeof (QUEUE));
    q->firstIndex = 0;
    q->lastIndex = MAX_QUEUE_LENGTH - 1;
    q->currentQueueLen = 0;

    if (pthread_mutex_init(&queue_update_mutex, NULL) != 0) 
    { 
        printf("Queue: Mutex init has failed\n"); // TODO - Handle this failure
    } 
    return q;
}

/* Method to destroy the Queue */
void destroyQueue(QUEUE *q)
{
    printf("Queue: Destroying Queue\n");
    free(q);
    pthread_mutex_destroy(&queue_update_mutex); 
}

/* Method to insert Packet Data into the Queue */
int insertIntoQueue(QUEUE *q, PACKET_DATA data)
{
    if (isQueueFull(q))
    {
        printf("Queue: Queue is full, unable to insert data\n");
	return FAILURE;
    }
    
    pthread_mutex_lock(&queue_update_mutex);
    q->lastIndex = (q->lastIndex + 1) % MAX_QUEUE_LENGTH;
    q->currentQueueLen += 1;
    q->queueData[q->lastIndex] = data;
    printf("Queue: Inserted data successfully into queue. Queue size is %d\n", q->currentQueueLen);
    pthread_mutex_unlock(&queue_update_mutex);

    return SUCCESS;
}

/* Method to retrieve Packet Data from the Queue */
PACKET_DATA retrieveFromQueue(QUEUE *q)
{
    if (isQueueEmpty(q))
    {
        printf("Queue: Queue is empty, unable to retrieve data\n");
	PACKET_DATA invalidData;
	invalidData.dataType = DATA_TYPE_INVALID;
	return invalidData;
    }
    
    pthread_mutex_lock(&queue_update_mutex);
    PACKET_DATA validData = q->queueData[q->firstIndex];
    q->firstIndex = (q->firstIndex + 1) % MAX_QUEUE_LENGTH;
    q->currentQueueLen -= 1;
    printf("Queue: Retrieved data successfully from queue. Queue size is %d\n", q->currentQueueLen);
    pthread_mutex_unlock(&queue_update_mutex);

    return validData;
}

/* Method that provides the current Queue length */
int getCurrentQueueLength(QUEUE *q)
{
    return q->currentQueueLen;
}

/* Method to check for Queue being full */
int isQueueFull(QUEUE *q)
{
    return (getCurrentQueueLength(q) == MAX_QUEUE_LENGTH);
}

/* Method to check if Queue is empty */
int isQueueEmpty(QUEUE *q)
{
    return (getCurrentQueueLength(q) == 0);
}
