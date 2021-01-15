/*
 * datatypes.c
 *
 *  Created on: Jan 15, 2021
 *      Author: danie
 */

#include "../datatypes.h"
#include "main.h"


void modflag_ovf_callback()
    {
    ++mf_systick.ovf;
    }

uint64_t modflag_tickdiff(TD_MODFLAG *cnt)
    {
    uint64_t counter = TIM6->CNT;
    cnt->ovf = mf_systick.ovf;

    cnt->systick = counter + (cnt->ovf * 0xFFFF);
    cnt->newtick = cnt->systick;
    cnt->tickdiff = cnt->newtick - cnt->oldtick;
    cnt->oldtick = cnt->newtick;
    return cnt->tickdiff;
    }

TD_MODFLAG mf_systick;
