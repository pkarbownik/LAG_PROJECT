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
#include "pinout.h"
#include "usart.h"
#include "tpm.h"

volatile char a,b;			//start counter values
uint16_t count0, count2;	//numbers of steps


ISR(TIMER0_OVF_vect) 
{
	if(count0)
	{
		PORTA^=X_STEP_PIN;						//toggle x
		if(!(--count0)) PORTA|=X_ENABLE_PIN;	//stepping is done, so disable 
		TCNT0=255-a;							//set start of countering
	}
}

ISR(TIMER2_OVF_vect) 
{
	if(count2)
	{
		PORTA^=Y_STEP_PIN;						//toggle x
		if(!(--count2)) PORTA|=Y_ENABLE_PIN;	//stepping is done, so disable
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
	Timer0_Init();
	Timer2_Init();
	USART_Init();
	a=255;						
	b=255;
	sei();
	while(1)
	{
		a=USART_Receive();		//receive start of countering from UASRT
		PORTA&=~X_ENABLE_PIN;	//enable
		count0=100;				//number of steps
		
		b=USART_Receive();		//receive start of countering from UASRT
		PORTA&=~Y_ENABLE_PIN;	//enable
		count2=200;				//number of steps
	}
}



