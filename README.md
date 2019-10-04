# Pub_Sub
This project implements a Publisher Subscriber model with multiple threads.
A single global queue is accessed by the Producer and Consumer threads.
Producers generate differnt types of data and put them on the queue.
Consumers retrieve data from the queue.
Access to the queue is synchronized.

Implementation is in C. Unit testing framework is Unity

Compilation: Go into the src directory and execute

gcc pubSub.c consumer.c producer.c packetData.c queue.c -o pubSub  (on Mac terminal)

NOTE: On linux, we may need to include -lpthread for successful compilation

Execution: ./pubSub


"CRIO Work Item" in the code marks the work that can be implemented by users for learning concepts.


Pending work:

* Detailed Test Cases with Unity framework. Currently one sample unit test is implemented. CMock needs to be explored with Unity.

* Create Makefile

* Address TODOs

* Doxygen style comments
