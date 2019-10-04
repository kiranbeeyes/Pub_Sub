/* 
 * File: consumer.c
 * Purpose: This file contains the Consumer thread.
 *          It retrieves data from the Queue.
 *          It retrieves the configured number of packets with a configured interval between retrievals.
 */

#include "pubSub.h"

/* Main consumer method */
void *consumerMethod(void *input)
{
    int *id = (int *)input;
    char threadId[MAX_THREAD_NAME_LEN];
    sprintf(threadId, "%s%d", "ConsumerThread", *id);
    printf("%s: Starting the consumerMethod\n", threadId);
        
    for (int iter = 1; iter <= NUM_PACKETS_TO_RETRIEVE; iter++)
    {
        PACKET_DATA data = retrieveFromQueue(globalQ);
        printPacketData(data, threadId);
	usleep(TIME_BETWEEN_PACKET_RETRIEVAL);
    }
    return (int *)SUCCESS;
}
