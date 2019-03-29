/*
* serial.c
*
* Created: 3/29/2019 11:33:01 AM
*  Author: Ruben
*/

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#include "serial.h"

#ifndef F_CPU
#define F_CPU 16000000UL
#endif

#define BAUD  9600
#define BIT(x) (1<<x)

char buffer[ 70 ];
int  received = 0;

static void delayms( uint16_t millis );
static int uart0_sendChar( char ch );

static void delayms( uint16_t millis )
{
	while ( millis )
	{
		_delay_ms( 1 );
		millis--;
	}
}


int serial_begin(){
	UBRR0   = ((( F_CPU / (BAUD * 16UL ))) - 1);
	UCSR0B  = _BV( RXEN0 ) | _BV( TXEN0 );
	UCSR0C  = 0b00000110;
	UCSR0B |= ( 1 << RXCIE0 );
}


static int uart0_sendChar( char ch )
{
	while (!(UCSR0A & BIT(UDRE0))) ; // wait until UDRE0 is set: tx buffer is ready
	UDR0 = ch; // send ch
	return 0; // OK
}

int serial_write_string(char* str, int len){
	
	int i = 0;

	for( i=0; i<len; i++ )
	{
		uart0_sendChar(str[i]);
	}
}


int serial_read_string(char* buf){
	
}

ISR( USART_RX_vect )
{
	char ReceivedByte;

	ReceivedByte       = UDR0;
	buffer[ received ] = ReceivedByte;

	received++;

	if( received >= 70 )
	received = 0;
}