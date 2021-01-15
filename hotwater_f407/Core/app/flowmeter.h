/*
 * flowmeter.h
 *
 *  Created on: Jan 14, 2021
 *      Author: danie
 */

#ifndef APP_FLOWMETER_H_
#define APP_FLOWMETER_H_

#define FLOW_TIMEOUT 300 //ms

typedef struct
{
    uint64_t RevsOdo;
    uint32_t RevsSession;
    uint32_t TicksTimeout;
    double cal_xn[12];
    char name[8];
    int timeout;
}
TD_FLOWMETER;

extern TD_FLOWMETER flowhot, flowcold;

#endif /* APP_FLOWMETER_H_ */
