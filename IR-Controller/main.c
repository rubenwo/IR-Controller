/*
* IR-Controller.c
*
* Created: 3/20/2019 11:10:12 AM
* Author : Ruben
*/
#define F_CPU 16000000UL

#include <avr/interrupt.h>
#include <util/delay.h>

#include "net/server.h"
#include "utils/debug_util.h"
#include "net/serial.h"


int main( void )
{
	sei();

	init_server();
	serial_print_response();

	while( 1 )
	{
		update_server();
		_delay_ms(100);
	}

	return 0;
}


