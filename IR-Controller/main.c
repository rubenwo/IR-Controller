/*
* IR-Controller.c
*
* Created: 3/20/2019 11:10:12 AM
* Author : Ruben
*/

#include <avr/io.h>
#include "IRsender/sender.h"

#define F_CPU 16000000

int main(void)
{
	/* Replace with your application code */
	while (1)
	{
		sender_sendIRSignal(0);
	}
}

