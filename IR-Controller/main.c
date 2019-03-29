/*
* IR-Controller.c
*
* Created: 3/20/2019 11:10:12 AM
* Author : Ruben
*/
#define F_CPU 16000000UL

#include <avr/interrupt.h>

#include "net/server.h"
#include "utils/debug_util.h"


int main( void )
{
	sei();

	init_server();

	while( 1 )
	{
		blink_onboard();
	}

	return 0;
}


