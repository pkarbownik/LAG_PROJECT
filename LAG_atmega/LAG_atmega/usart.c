/*
 * CFile1.c
 *
 * Created: 2015-12-12 18:08:43
 *  Author: Przemek
 */ 


// chip: atmega16


#include <avr/io.h>
#include <stdio.h>

void USART_Init(void)
{
	UCSRB|=(1<<RXCIE)|(1<<RXEN)|(1<<TXEN);	//RXCIE-interrupt reciver and RX/TX-enable
	UBRRH=0;								//baudrate 9600 for 1MHz
	UBRRL=12;								//baudrate 9600 for 1MHz
	UCSRA=(1<<U2X);							//double speed mode BAUD=fosc/8(UBRR+1)
	UCSRC=(1<<URSEL)|(1<<UCSZ0)|(1<<UCSZ1);	//8-bit data,URSEL - writing UCRSC
	
}

void USART_Transmit(char data)   //procedura umo¿liwiaj¹ca wysy³anie danych do telefonu
{
	while ( !( UCSRA & (1<<UDRE)) );		//Wait for data to be received
	UDR = data;								//write data
}


char USART_Receive( void )
{
	while ( !(UCSRA & (1<<RXC)) );			//Wait for data to be received
	return UDR;								//Get and return received data from buffer
}