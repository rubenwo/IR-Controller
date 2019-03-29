/*
* IR-Controller.c
*
* Created: 3/20/2019 11:10:12 AM
* Author : Ruben
*/
#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "net/server.h"


int main( void )
{
	sei();
	//_delay_ms(1000);
	DDRB = 0b00111111;
	DDRD = 0b11111100;
	init_server();

	while( 1 )
	{
		PORTB = 0b00111111;
		PORTD = 0b11111100;
		_delay_ms(500);
		PORTB=0b00000000;
		PORTD=0b00000000;
		_delay_ms(500);
	}

	return 0;
}


