/* 
 * File: queue.c
 * Purpose: This file contains the Queue implementation.
 */

#include "queue.h"
#include "common.h"
#include <pthread.h>

pthread_mutex_t queue_update_mutex; // Mutex for synchronisation

/* CRIO Work Item1: The initializeQueue(), insertIntoQueue() and retrieveFromQueue() 
 *                  methods can be cleared out for users to fill in.
 *                  Specify that these methods should use the Queue structure and
 *                  methods defined in queue.h
 *                  Learning: Fundamental Queue operations 
 * 
 * CRIO Work Item2: The mutex related lines of code can be removed for users to implement.
 *                  Without this synchronisation, we can see inconsistent queue length 
 *                  for consecutive inserts/removals.
 *                  Learning: Synchronisation
 */

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

void destroyQueue(QUEUE *q)
{
    printf("Queue: Destroying Queue\n");
    free(q);
    pthread_mutex_destroy(&queue_update_mutex); 
}

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

int getCurrentQueueLength(QUEUE *q)
{
    return q->currentQueueLen;
}

int isQueueFull(QUEUE *q)
{
    return (getCurrentQueueLength(q) == MAX_QUEUE_LENGTH);
}

int isQueueEmpty(QUEUE *q)
{
    return (getCurrentQueueLength(q) == 0);
}
