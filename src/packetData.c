/* 
 * File: packetData.c
 * Purpose: This file contains a print method for the Packet Data.
 */

#include <stdio.h>
#include "packetData.h"

void printPacketData(PACKET_DATA data, char *str)
{
    if(data.dataType != DATA_TYPE_INVALID)
    {
	if (data.dataType == DATA_TYPE_INT)
	{
            printf("%s: Integer Data is %d\n", str, data.data.intData);
	}
	else if (data.dataType == DATA_TYPE_FLOAT)
	{
            printf("%s: Float Data is %f\n", str, data.data.floatData);
	}
	else // DATA_TYPE_STRING
	{
            printf("%s: String Data is %s\n", str, data.data.strData);
	}
    }
    else // DATA_TYPE_INVALID
    {
        printf("%s: No Data found\n", str);
    }
}
