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

    for (int iter = 1; iter <= NUM_PACKETS_TO_PRODUCE; iter++)
    {
        PACKET_DATA data;
        randomDataGenerator(&data);
        printPacketData(data, threadId);
        insertIntoQueue(globalQ, data);
	usleep(TIME_BETWEEN_PACKET_PRODUCTION);
    }
    return (int *)SUCCESS;
}

void randomDataGenerator(PACKET_DATA *data)
{
    int randDataType = DATA_TYPE_INVALID;

    // Generate one of the DATA_TYPEs at random
    while (randDataType == DATA_TYPE_INVALID)
    {
	randDataType = rand() % (DATA_TYPE_STRING + 1); // This is the current max value for DATA_TYPE
    }
    if (randDataType == DATA_TYPE_INT)
    {	    
        data->dataType = DATA_TYPE_INT;
        data->data.intData = rand();
    }
    else if (randDataType == DATA_TYPE_FLOAT)
    {
        data->dataType = DATA_TYPE_FLOAT;
        data->data.floatData = ((float)rand()/(float)(RAND_MAX)) * 10000; // Number less than 10000
    }
    else // DATA_TYPE_STRING
    {
        data->dataType = DATA_TYPE_STRING;
        generateRandomString(data->data.strData, MAX_DATA_STRING_LENGTH);
    }
}

void generateRandomString(char *str, int length) 
{
    static const char charsToUse[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";

    for (int i = 0; i < length; ++i) {
        str[i] = charsToUse[rand() % (sizeof(charsToUse) - 1)];
    }

    str[length] = 0;
}
