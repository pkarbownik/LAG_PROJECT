/*
 * LAG_atmega.c
 *
 * Created: 2015-12-11 12:57:46
 *  Author: Przemek
 */ 
#ifndef F_CPU
#define F_CPU 1000000UL
#endif
//#define BAUD	9600L
//#define BAUDRATE	((unsigned int)((F_CPU)/(BAUD*16))-1)

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "main.h"
#include "pinout.h"
#include "usart.h"
#include "tpm.h"

volatile char a,b;			//start counter values
uint16_t count0, count2;	//numbers of steps


ISR(TIMER0_OVF_vect) 
{
	if(count0)
	{
		toggle_pin(X_STEP_PIN);						//toggle x
		if(!(--count0)) set_pin_high(X_ENABLE_PIN);	//stepping is done, so disable 
		TCNT0=255-a;							//set start of countering
	}
}

ISR(TIMER2_OVF_vect) 
{
	if(count2)
	{
		toggle_pin(Y_STEP_PIN);						//toggle x
		if(!(--count2)) set_pin_high(Y_ENABLE_PIN);	//stepping is done, so disable
		TCNT2=255-b;							//set start of countering
	}
}

ISR(BADISR_vect)
{
												// user code here
}



int main(void)
{
	DDRA=0xff;
	PORTA=0;
	disable_motors();
	Timer0_Init();
	Timer2_Init();
	USART_Init();
	a=255;						
	b=255;
	sei();
	while(1)
	{
		a=USART_Receive();		//receive start of countering from UASRT
		b=USART_Receive();		//receive start of countering from UASRT
		enable_motors();
		
		if (((a >> 7) & 0x01) == 0x01) PORTA |= X_DIR_PIN; else PORTA &= ~X_DIR_PIN;
		count0=(a & 0x7F) * 8;				//number of steps

		if (((b >> 7) & 0x01) == 0x01) PORTA |= Y_DIR_PIN; else PORTA &= ~Y_DIR_PIN;
		count2=(b & 0x7F) * 8;			//number of steps
	}
}

void set_pin_high(uint8_t pin) { PORTA |= pin; }
void set_pin_low(uint8_t pin)  { PORTA &= ~pin; }
void toggle_pin(uint8_t pin)   { PORTA ^= pin; }

void enable_motors(void)
{		
	set_pin_low(X_ENABLE_PIN);
	set_pin_low(Y_ENABLE_PIN);
}

void disable_motors(void)
{
	set_pin_high(X_ENABLE_PIN);
	set_pin_high(Y_ENABLE_PIN);
}

