/* 
 * File: queue.h
 * Purpose: This file contains the Queue definition - data structure and methods.
 */

#include <stdio.h>
#include <stdlib.h>

#define MAX_QUEUE_LENGTH 5000   //TODO - remove this and make size one of the inputs to initializeQueue()

typedef struct Queue 
{
    int firstIndex, lastIndex, currentQueueLen;
    unsigned char *queueData[MAX_QUEUE_LENGTH];  // Byte array as generic data format
    // Ideally have an XML or JSON string converted to byte array and send it
    // Consumer knows how to interpret the data
    // Memory for the data will be allocated by producer and freed up by consumer
}QUEUE;

QUEUE * initializeQueue();
void destroyQueue(QUEUE *q);
int insertIntoQueue(QUEUE *q, unsigned char *data);
unsigned char * retrieveFromQueue(QUEUE *q);
int getCurrentQueueLength(QUEUE *q);
int isQueueFull(QUEUE *q);
int isQueueEmpty(QUEUE *q);
