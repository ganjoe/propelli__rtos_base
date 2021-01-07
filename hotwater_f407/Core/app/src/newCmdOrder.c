/*
 * newCmdOrder.c
 *
 *  Created on: 07.01.2021
 *      Author: danie
 */

#include "../newCmdOrder.h"
#include "FreeRTOS.h"
#include "queue.h"
#include "cmsis_os2.h"
#include "../terminal.h"
#include "string.h"
#include "../datatypes.h"

extern osMessageQueueId_t myTxQueueHandle;

static TD_TERMINAL_CALLBACKS callbacks[CALLBACK_LEN];

static int callback_write = 0;

void term_lol_setCallback(const char *command, const char *help,
	const char *arg_names, void (*cbf)(int argc, const char **argv))
    {
    int callback_num = callback_write;
    for (int i = 0; i < callback_write; i++)
	{
	// First check the address in case the same callback is registered more than once.
	if (callbacks[i].command == command)
	    {
	    callback_num = i;
	    break;
	    }
	// Check by string comparison.
	if (strcmp(callbacks[i].command, command) == 0)
	    {
	    callback_num = i;
	    break;
	    }
	// Check if the callback is empty (unregistered)
	if (callbacks[i].cbf == 0)
	    {
	    callback_num = i;
	    break;
	    }
	}
    callbacks[callback_num].command = command;
    callbacks[callback_num].help = help;
    callbacks[callback_num].arg_names = arg_names;
    callbacks[callback_num].cbf = cbf;

    if (callback_num == callback_write)
	{
	callback_write++;
	if (callback_write >= CALLBACK_LEN)
	    {
	    callback_write = 0;
	    }
	}
    }
/*--------------------------*/
void cmd_init_callbacks()
    {
    term_lol_setCallback("reset", "mcu reset", "countdown", reset);
    }
/*--------------------------*/
void term_lol_parse(TD_LINEOBJ *line)
    {

    char strbuffer[TD_LINEOBJ_MAX_SSIZE];

    char *strbufferptr = &strbuffer;

    int ArgCount = 0;

    char *ptrArgBuffer[4]; //max arguemtns

    //cmd ist der erste stringabschnitt von links
    strbufferptr = strtok(line->string, strdup(" "));

    //argumente separieren, und in ptr-array speichern
    while (strbufferptr && ArgCount < 4)
	{
	ptrArgBuffer[ArgCount++] = strbufferptr;

	strbufferptr = strtok(0,strdup(" "));
	}

/*
    if (argc == 0)
	{
	term_qPrintf(myTxQueueHandle, "No command received\n");
	return;
	}
    if (strcmp(argv[0], "help") == 0)
	{
	term_qPrintf(myTxQueueHandle, "registered commands:\n");

	for (int i = 0; i < callback_write; i++)
	    {
	    term_qPrintf(myTxQueueHandle, callbacks[i].command);
	    term_qPrintf(myTxQueueHandle, "\rhelp: ");
	    term_qPrintf(myTxQueueHandle, callbacks[i].help);
	    term_qPrintf(myTxQueueHandle, "\r");
	    }
	}
*/
    for (int i = 0; i < callback_write; i++)
	{
	if (callbacks[i].cbf != 0 && strcmp(ptrArgBuffer[0], callbacks[i].command) == 0)
	    {
	    callbacks[i].cbf(ArgCount, (const char**) ptrArgBuffer);
	    return;
	    }
	}    //
    }
/*--------------------------*/
void reset(int argc, const char **argv)
    {
    float f = -1;

    if (argc == 2)
	{
	sscanf(argv[1], "%f", &f);
	term_qPrintf(myTxQueueHandle, "\r[parseCmd] reset ok:%5fs ok\r", f);
	HAL_NVIC_SystemReset();
	}
    }
/*--------------------------*/
