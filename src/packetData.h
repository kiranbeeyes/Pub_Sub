/* 
 * File: packetData.h
 * Purpose: This file contains the definition for Packet Data.
 *          The packetData structure contains a union of 3 data types.
 *          A dataType field in the structure specifies which of the 3 data types are populated.
 */

#define DATA_TYPE_INVALID 0
#define DATA_TYPE_INT 1
#define DATA_TYPE_FLOAT 2
#define DATA_TYPE_STRING 3

#define MAX_DATA_STRING_LENGTH 10

typedef struct packetData {
    int dataType;
    union { 
        int intData; 
        float floatData;
        char strData[MAX_DATA_STRING_LENGTH]; 
    }data;
}PACKET_DATA;

void printPacketData(PACKET_DATA data, char *str);
