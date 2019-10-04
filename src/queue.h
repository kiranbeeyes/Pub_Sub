/* 
 * File: queue.h
 * Purpose: This file contains the Queue definition - data structure and methods.
 */

#include <stdio.h>
#include <stdlib.h>
#include "packetData.h"

#define MAX_QUEUE_LENGTH 50   //TODO - remove this and make size one of the inputs to initializeQueue()

typedef struct Queue 
{
    int firstIndex, lastIndex, currentQueueLen;
    PACKET_DATA queueData[MAX_QUEUE_LENGTH];
}QUEUE;

QUEUE * initializeQueue();
void destroyQueue(QUEUE *q);
int insertIntoQueue(QUEUE *q, PACKET_DATA data);
struct packetData retrieveFromQueue(QUEUE *q);
int getCurrentQueueLength(QUEUE *q);
int isQueueFull(QUEUE *q);
int isQueueEmpty(QUEUE *q);
