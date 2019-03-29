/*
* IR-Controller.c
*
* Created: 3/20/2019 11:10:12 AM
* Author : Ruben
*/

#include <avr/io.h>
#include <util/delay.h>
#include <time.h>
#include "IRsender/sender.h"
#include "IRSender/memory.h"

#define F_CPU 16000000UL

int main(void)
{
	/* Replace with your application code */
	while (1)
	{
		sender_sendIRSignal(0, 0);
		_delay_ms(2000);
	}
}

