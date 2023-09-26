#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "timer.h"
//typedef unsigned char uint8;
#define NMH return 0;

int sec1 = 0, sec2 = 0, mins1 = 0, mins2 = 0, hours1 = 0, hours2 = 0;

//void Timer1_CTC() {
//	TCCR1A = (1 << FOC1A);
//	TCCR1B = (1 << WGM12) | (1 << CS11) | (1 << CS10); //prescaler 64
//	TCNT1 = 0;
//	OCR1A = 15625;
//	TIMSK |= (1 << OCIE1A);
//}

ISR(INT0_vect) {
	sec1 = 0, sec2 = 0, mins1 = 0, mins2 = 0, hours1 = 0, hours2 = 0;
	TCNT1 = 0;
	TCCR1A = (1<<FOC1A);
	TCCR1B = (1<<WGM12) | (1<<CS11) | (1<<CS10);
}
void INT0_Init(void) {
	MCUCR |= (1 << ISC01);
	GICR  |= (1<<INT0);
}
ISR(INT1_vect) {
	TCCR1A = 0;
	TCCR1B = 0;
}
void INT1_Init(void) {
	MCUCR |= (1<<ISC11) | (1<<ISC10);
	GICR  |= (1<<INT1);
}
ISR(INT2_vect) {
	TCCR1A = (1<<FOC1A);
	TCCR1B = (1<<WGM12) | (1<<CS11) | (1<<CS10);
}
void INT2_Init(void) {
	MCUCSR &= ~(1<<ISC2);
	GICR  |= (1<<INT2);
}




int main()
{
	SREG |= (1<<7);
	Timer1_ConfigType Tconfig={0,15625,PRESCALER_64,CTC};
	Timer1_init(&Tconfig);
	INT0_Init();
	INT1_Init();
	INT2_Init();

	DDRB &= ~(1<<PB2);
	DDRD &= ~(1<<PD2) | ~(1<<PD3);
	PORTB |= (1<<PB2);
	PORTD |= (1<<PD2);

	DDRC |= 0x0F;
	DDRA |= 0x3F;

	PORTC &= (0xF0);



	while(1)
	{
		PORTC = (PORTC & 0xF0) | (sec1 & 0x0F);

		PORTA |=  (1 << PA0);

		_delay_us(2);

		PORTA &= ~(1 << PA0);

		PORTC = (PORTC & 0xF0) | (sec2 & 0x0F);

		PORTA |=  (1 << PA1);

		_delay_us(2);

		PORTA &= ~(1 << PA1);

		PORTC = (PORTC & 0xF0) | (mins1 & 0x0F);

		PORTA |=  (1 << PA2);

		_delay_us(2);

		PORTA &= ~(1 << PA2);

		PORTC = (PORTC & 0xF0) | (mins2 & 0x0F);

		PORTA |=  (1 << PA3);

		_delay_us(2);

		PORTA &= ~(1 << PA3);

		PORTC = (PORTC & 0xF0) | (hours1 & 0x0F);

		PORTA |=  (1 << PA4);

		_delay_us(2);

		PORTA &= ~(1 << PA4);

		PORTC = (PORTC & 0xF0) | (hours2 & 0x0F);

		PORTA |=  (1 << PA5);

		_delay_us(2);

		PORTA &= ~(1 << PA5);

	}
	NMH
}

