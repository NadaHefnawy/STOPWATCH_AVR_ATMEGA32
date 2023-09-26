/*
 * timer.c
 *
 *  Created on: Jul 1, 2023
 *      Author: DELL
 */

#include <avr/io.h>
#include "timer.h"
#include "std_types.h"
#include <avr/interrupt.h>
extern int sec1 , sec2 , mins1 , mins2 , hours1 , hours2 ;
static volatile void (*g_callBackPtr)(void) = NULL_PTR;

ISR(TIMER0_OVF_vect) {
	if (sec1 == 9) {
				sec1 = 0;
				if (sec2 == 5) {
					sec2 = 0;
					if (mins1 == 9) {
						mins1 = 0;
						if (mins2 == 5) {
							mins2 = 0;
							if (hours1 == 9) {
								hours1 = 0;
								if (hours2 == 9) {
									sec1 = 0, sec2 = 0, mins1 = 0, mins2 = 0, hours1 = 0, hours2 = 0,TCNT1=0;
								} else {
									hours2++;
								}
							} else {
								hours1++;
							}
						} else {
							mins2++;
						}
					} else {
						mins1++;
					}
				} else {
					sec2++;
				}
			} else {
				sec1++;
			}

}
ISR(TIMER1_COMPA_vect) {
	if (sec1 == 9) {
			sec1 = 0;
			if (sec2 == 5) {
				sec2 = 0;
				if (mins1 == 9) {
					mins1 = 0;
					if (mins2 == 5) {
						mins2 = 0;
						if (hours1 == 9) {
							hours1 = 0;
							if (hours2 == 9) {
								sec1 = 0, sec2 = 0, mins1 = 0, mins2 = 0, hours1 = 0, hours2 = 0,TCNT1=0;
							} else {
								hours2++;
							}
						} else {
							hours1++;
						}
					} else {
						mins2++;
					}
				} else {
					mins1++;
				}
			} else {
				sec2++;
			}
		} else {
			sec1++;
		}
}
void Timer1_init(const Timer1_ConfigType *Config_Ptr) {

	TCCR1A = (1 << FOC1A) | (Config_Ptr->mode & 3);
	if (Config_Ptr->mode == CTC) {

		TIMSK |= (1 << OCIE1A); /* Enable Timer1 Compare A Interrupt */
		OCR1A = Config_Ptr->compare_value;
	}
	if (Config_Ptr->mode == NORMAL) {
		TIMSK |= (1 << TOIE0); // Enable Timer0 Overflow Interrupt
	}
	TCCR1B = (Config_Ptr->prescaler) | ((Config_Ptr->mode >> 2) << 3);
	TCNT1 = Config_Ptr->initial_value;

}

void Timer1_deInit(void)
{
	TCCR1A=0;
	TCCR1B=0;

}
void Timer1_setCallBack(void(*a_ptr)(void))
{
	g_callBackPtr = a_ptr;

}
