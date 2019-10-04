/* 
 * File: mockTestQueue.c
 * Purpose: To test Queue implementation in queue.c using Unity framework
 * Compilation: gcc mockTestQueue.c ../src/queue.c unity.c -I../src -o mockTestQueue
 * Execution: ./mockTestQueue
 */

#include "queue.h"
#include <string.h>
#include "unity.h"

void setUp (void) {} /* Is run before every test, put unit init calls here. */
void tearDown (void) {} /* Is run after every test, put unit clean-up calls here. */

void test_Queue_Insertion_Removal()
{
    QUEUE *q = initializeQueue();

    PACKET_DATA datax, datay, dataz, dataw;
    datax.dataType = DATA_TYPE_INT;
    datax.data.intData = 5;
    
    int result;
    result = insertIntoQueue(q, datax);
    TEST_ASSERT_EQUAL_INT( 1, result);

    PACKET_DATA dataA = retrieveFromQueue(q);
    TEST_ASSERT_EQUAL_INT(DATA_TYPE_INT, dataA.dataType);
    TEST_ASSERT_EQUAL_INT(5, dataA.data.intData);

    destroyQueue(q);
    return;
}

int main(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_Queue_Insertion_Removal);
    return UNITY_END();
}


