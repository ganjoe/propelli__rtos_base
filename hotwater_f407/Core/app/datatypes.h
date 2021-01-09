/*
 * datatypes.h
 *
 *  Created on: Jan 2, 2021
 *      Author: danie
 */

#ifndef APP_DATATYPES_H_
#define APP_DATATYPES_H_


#include "cmsis_os2.h"

typedef struct
	{
	const char *command;
	const char *help;
	const char *arg_names;
	void (*cbf)(int argc, const char **argv);
	}
TD_TERMINAL_CALLBACKS;

typedef struct
    {
    //TODO: replace with freeRTOS datatypes
    char byte_received;
    char* string_rx;
    unsigned int newString;

    /*
    //char* sep;
    //char* eoc;

    //char* string_tx;
    //int uart_buffer_tx_len;
     */

    int flag_newString, flag_newTransmission;
    }
TD_TERMINAL;

/*
 * Linedata Object for filewrite, lcd, uart
 *
 */
#define TD_LINEOBJ_MAX_SSIZE 16

typedef struct
{
    char	timestring[18];
    char	filename[8];	//rom l999 cmd
    char	string[TD_LINEOBJ_MAX_SSIZE];	//setdate 10 10 10
    char	header[4];	//tmcu, thot, tcld, fhot, fcld, lvlh, lvlc
    char	postfix[5];	// "%4.3f"
    uint16_t	linenr;
    float 	value;
    osMessageQueueId_t myQueueHandle;
}
TD_LINEOBJ;

#endif /* APP_DATATYPES_H_ */



