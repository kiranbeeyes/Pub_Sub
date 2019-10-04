# Pub_Sub
This project implements a Publisher Subscriber model with multiple threads.
A single global queue is accessed by the Producer and Consumer threads.
Producers generate differnt types of data and put them on the queue.
Consumers retrieve data from the queue.
Access to the queue is synchronized.

Implementation is in C.

Compilation: Go into the src directory and execute

gcc pubSub.c consumer.c producer.c packetData.c queue.c -o pubSub

NOTE: On linux, we may need to include -lpthread for successful compilation

Execution: ./pubSub
