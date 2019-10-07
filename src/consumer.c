/* 
 * File: consumer.c
 * Purpose: This file contains the Consumer thread.
 *          It retrieves data from the Queue.
 *          It retrieves the configured number of packets with a configured interval between retrievals.
 */

#include "pubSub.h"

void printPacketData(unsigned char *data, char *threadId)
{
    // TODO - optimize this function
    // Convert byte array to string and print
    int byteArrayIndex = 0;
    while(data[byteArrayIndex] != 0)  // 0 is the last character indicating '\0'
    {
	byteArrayIndex++;
    }

    char str[byteArrayIndex];  // including for '\0' character
    byteArrayIndex = 0;
    while(data[byteArrayIndex] != 0)
    {
        str[byteArrayIndex] = data[byteArrayIndex];
	byteArrayIndex++;
    }
    str[byteArrayIndex] = '\0';
    printf("%s: String Data is %s\n", threadId, str);
}

void *consumerMethod(void *input)
{
    int *id = (int *)input;
    char threadId[MAX_THREAD_NAME_LEN];
    sprintf(threadId, "%s%d", "ConsumerThread", *id);
    printf("%s: Starting the consumerMethod\n", threadId);
        
    int iter;
    for (iter = 1; iter <= NUM_PACKETS_TO_RETRIEVE; iter++)
    {
        unsigned char *data = retrieveFromQueue(globalQ);
	if (data != NULL)
	{
	    printPacketData(data, threadId);
            // Free up the memory allocated for the data
	    free (data);
	}
	usleep(TIME_BETWEEN_PACKET_RETRIEVAL);
    }
    return (int *)SUCCESS;
}
