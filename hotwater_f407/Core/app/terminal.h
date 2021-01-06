/*
 * terminal.h
 *
 *  Created on: Jul 7, 2020
 *      Author: daniel
 */

#ifndef INC_TERMINAL_H_
#define INC_TERMINAL_H_
#include "stdio.h"
#include "stdarg.h"
#include "main.h"
#include "usart.h"
#include "datatypes.h"
#include "queue.h"
#include "semphr.h"

/*-----------------------------------------------------------*/
//size for static td - do not change
#define CALLBACK_LEN		40

//array size for snprintf
#define UART_PRINTBUFFER 	32

//bytes send to uart every taskloop
#define TX_BYTES_AT_ONCE	8

//HAL USART HANDLE
#define HUART &huart1
/*-----------------------------------------------------------*/
/*-----------------------------------------------------------*/

//wrapper for vsnprintf. prints to queue
void qprintf(osMessageQueueId_t QueueHandle, char *fmt, ...);

//prints out formatted string
void term_vprintLineObj(osMessageQueueId_t QueueHandle, TD_LINEOBJ *line);

BaseType_t dBase_StoreQueue(osMessageQueueId_t QueueHandle, TD_LINEOBJ *line);

void term_makeLineObj(TD_LINEOBJ *line,
			char* filename,
			char* string,
			char* header,
			char* postfix,
			uint16_t linenr,
		   	char 	*fmt,
			... );
/*-----------------------------------------------------------*/
/*-----------------------------------------------------------*/
extern TD_TERMINAL btTerm;


#endif /* INC_TERMINAL_H_ */
