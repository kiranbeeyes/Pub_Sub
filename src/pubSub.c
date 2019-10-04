/* 
 * File: pubSub.c
 * Purpose: Starting point for the pubSub pod
 *          This creates the Queue and starts up the Producer and Consumer threads.
 *          It waits for the threads to finish and cleans up.
 */

#include <pthread.h>
#include "pubSub.h"

QUEUE *globalQ;

/* Everything starts here */
int main() 
{
    printf("PubSub: Starting up the Pub Sub pod\n");
    globalQ = initializeQueue();
    startProducersConsumers();
    destroyQueue(globalQ);
    return SUCCESS;
}

/* Start up the Producers and Consumers */
void startProducersConsumers()
{
    pthread_t producerThreads[NUM_PRODUCERS];
    pthread_t consumerThreads[NUM_CONSUMERS];
    
    int producerIds[NUM_PRODUCERS];  // Needed to pass the Id to the threads
    for(int producerIndex = 0 ; producerIndex < NUM_PRODUCERS; producerIndex++)
    {	
	producerIds[producerIndex] = producerIndex;
        int retVal = pthread_create(&producerThreads[producerIndex], NULL, producerMethod, 
			(void *)&producerIds[producerIndex]);
	if (retVal != SUCCESS)
	{
            printf("PubSub: Failure in creating Producer Thread\n");
	}
    }

    int consumerIds[NUM_CONSUMERS];  // Needed to pass the Id to the threads
    for(int consumerIndex = 0 ; consumerIndex < NUM_PRODUCERS; consumerIndex++)
    {	    
	consumerIds[consumerIndex] = consumerIndex;
        int retVal = pthread_create(&consumerThreads[consumerIndex], NULL, consumerMethod, 
			(void *)&consumerIds[consumerIndex]);
	if (retVal != SUCCESS)
	{
            printf("PubSub: Failure in creating Consumer Thread\n");
	}
    }

    // Wait for all the threads to complete before exiting the program
    for (int iter = 0; iter < NUM_PRODUCERS; iter++)
    {
        pthread_join(producerThreads[iter], NULL);
    }	
    for (int iter = 0; iter < NUM_CONSUMERS; iter++)
    {
        pthread_join(consumerThreads[iter], NULL);
    }

    return;
}
