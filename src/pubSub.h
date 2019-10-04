/* 
 * File: pubSub.h
 * Purpose: Header file for the main pubSub pod
 */

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include "queue.h"

#define NUM_PRODUCERS 5
#define NUM_CONSUMERS 5
#define NUM_PACKETS_TO_PRODUCE 50
#define TIME_BETWEEN_PACKET_PRODUCTION 50000   // In microseconds
#define NUM_PACKETS_TO_RETRIEVE 50
#define TIME_BETWEEN_PACKET_RETRIEVAL 50000  // In microseconds
#define MAX_THREAD_NAME_LEN 25

#define SUCCESS 1
#define FAILURE 0

extern QUEUE *globalQ;   // Global Queue to be shared between Producers and Consumers

void startProducersConsumers();
void *producerMethod(void *input);
void *consumerMethod(void *input);
void randomDataGenerator(PACKET_DATA *data);
void generateRandomString(char *str, int length); 
