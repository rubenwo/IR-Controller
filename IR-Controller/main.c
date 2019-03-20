/*
* IR-Controller.c
*
* Created: 3/20/2019 11:10:12 AM
* Author : Ruben
*/

#define F_CPU 16000000

#include <avr/io.h>
#include <util/delay.h>

#include "net/server.h"
#include "net/wifi.h"


int main(void)
{
	init_wifi("...", "...");
	init_server();
	
	DDRB = 0b00111111;
	DDRD = 0b11111100;

	while (1)
	{
		PORTB = 0b00111111;
		PORTD = 0b11111100;
		_delay_ms(500);
		PORTB = 0b00000000;
		PORTD = 0b00000000;
		_delay_ms(500);
	}
}

