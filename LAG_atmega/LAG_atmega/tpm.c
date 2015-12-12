/*
 * CFile1.c
 *
 * Created: 2015-12-12 23:19:29
 *  Author: Przemek
 */ 
#include <avr/io.h>

void Timer0_Init(void)
{
	TCNT0 = 0;
	TCCR0 |= (1<<CS01)|(1<<CS00);
	TIMSK |= (1<<TOIE0);
}


void Timer2_Init(void)
{
	TCNT2 = 0;
	TCCR2 |= (1<<CS21)|(1<<CS20) ;
	TIMSK |= (1<<TOIE2);
}