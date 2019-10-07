/* 
 * File: producer.c
 * Purpose: This file contains the Producer thread.
 *          It generates random data and puts it into the Queue.
 *          It generates the configured number of packets with a configured interval between packets.
 */

#include "pubSub.h"

void *producerMethod(void *input)
{
    int *id = (int *)input;
    char threadId[MAX_THREAD_NAME_LEN];
    sprintf(threadId, "%s%d", "ProducerThread", *id);
    printf("%s: Starting the producerMethod\n", threadId);

    // Initialize the random number generator
    time_t t;
    srand((unsigned int)time(&t));   // TODO - currently all threads are generating same data. Address this.

    int iter;
    for (iter = 1; iter <= NUM_PACKETS_TO_PRODUCE; iter++)
    {
        unsigned char *data;
	int sizeOfStr = 20; // TODO - remove hardcoded 20 here, can generate any length
        // sizeOfStr includes the NUL character
	
        // Allocate memory for byte array
        data = (unsigned char *) malloc (sizeOfStr * sizeof(unsigned char));
        randomDataGenerator(data, sizeOfStr, threadId);

        insertIntoQueue(globalQ, data);
	usleep(TIME_BETWEEN_PACKET_PRODUCTION);
    }
    return (int *)SUCCESS;
}

void randomDataGenerator(unsigned char *data, int sizeOfStr, char *threadId)
{
    static const char charsToUse[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
    
    char dataString[sizeOfStr];
    int i;
    for (i = 0; i < sizeOfStr-1; ++i) { 
        dataString[i] = charsToUse[rand() % (sizeof(charsToUse) - 1)];
    }
    dataString[sizeOfStr-1] = '\0';
    printf("%s: String Data is %s\n", threadId, dataString);

    // Convert the string to byte array
    int strIndex = 0;
    for (strIndex = 0; strIndex < sizeOfStr; strIndex++)
    {
        data[strIndex] = dataString[strIndex];
    }
}
