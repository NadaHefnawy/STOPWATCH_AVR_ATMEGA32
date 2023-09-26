/*
 * timer.h
 *
 *  Created on: Jul 1, 2023
 *      Author: DELL
 */

#ifndef TIMER_H_
#define TIMER_H_
#include "std_types.h"
typedef enum {
	NO_CLOCK_SOURCE, PRESCALER_1, PRESCALER_8,
	PRESCALER_64,PRESCALER_256,PRESCALER_1024,


} Timer1_Prescaler;


typedef enum {
	NORMAL,CTC=4

} Timer1_Mode;

typedef struct {
	uint16 initial_value;
	uint16 compare_value; // it will be used in compare mode only.
	Timer1_Prescaler prescaler;
	Timer1_Mode mode;
} Timer1_ConfigType;

void Timer1_init(const Timer1_ConfigType * Config_Ptr);

void Timer1_deInit(void);

void Timer1_setCallBack(void(*a_ptr)(void));
#endif /* TIMER_H_ */
