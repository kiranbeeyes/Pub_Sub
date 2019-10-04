/* 
 * File: testQueue.c
 * Purpose: To test Queue implementation in queue.c
 * Compilation: gcc testQueue.c ../src/queue.c -I../src -o testQueue
 * Execution: ./testQueue
 * NOTE: Change MAX_QUEUE_LENGTH in queue.h to 3 to test this, 
 *       till queue size can be one of the inputs to initializeQueue() 
 */

#include "queue.h"
#include <string.h>

/* Main test method */
int main()
{
    QUEUE *q = initializeQueue();

    PACKET_DATA datax, datay, dataz, dataw;
    datax.dataType = DATA_TYPE_INT;
    datax.data.intData = 5;
    datay.dataType = DATA_TYPE_FLOAT;
    datay.data.floatData = 1.2;
    dataz.dataType = DATA_TYPE_STRING;
    strncpy(dataz.data.strData,"abc", MAX_DATA_STRING_LENGTH);
    dataw.dataType = DATA_TYPE_INT;
    dataw.data.intData = 9;
 
    int result;
    result = insertIntoQueue(q, datax);
    printf("TestQueue: result of insertion is %d\n", result);
    result = insertIntoQueue(q, datay);
    printf("TestQueue: result of insertion is %d\n", result);
    result = insertIntoQueue(q, dataz);
    printf("TestQueue: result of insertion is %d\n", result);
    result = insertIntoQueue(q, dataw);
    printf("TestQueue: result of insertion is %d\n", result);
    
    PACKET_DATA dataA = retrieveFromQueue(q);
    printf("Data Type is %d, Integer Data is %d\n", dataA.dataType, dataA.data.intData);
    PACKET_DATA dataB = retrieveFromQueue(q);
    printf("Data Type is %d, Float Data is %f\n", dataB.dataType, dataB.data.floatData);
    PACKET_DATA dataC = retrieveFromQueue(q);
    printf("Data Type is %d, String Data is %s\n", dataC.dataType, dataC.data.strData);
    PACKET_DATA dataD = retrieveFromQueue(q);
    printf("Data Type is %d\n", dataD.dataType);

    destroyQueue(q);
    return 0;
}
