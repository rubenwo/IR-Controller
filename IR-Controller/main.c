/*
* IR-Controller.c
*
* Created: 3/20/2019 11:10:12 AM
* Author : Ruben
*/
#define F_CPU 16000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include <inttypes.h>
#include <util/delay.h>
#include <stdint.h>
#include <stdlib.h>
#include "lcd_lib.h"

#include "net/server.h"
#include "utils/debug_util.h"
#include "net/serial.h"
#define F_CPU 16000000UL

int now = 2;
int counter = 0;
static void searchirsignal();
int main()
{
	DDRC = 0x00;
	DDRD = 0xFF;
	ADCSRA = 0b10000000;
	ADMUX = 0b01100001;
	LCDinit();
	LCDclr();

	printf("Started..");
	_delay_ms(1000);
	LCDclr();
	printf("Press btn 1");
	searchirsignal();
	LCDclr();
	printf("press btn 2");
	searchirsignal();
	LCDclr();
	printf("press btn 3");
	searchirsignal();
	LCDclr();
	printf("press btn 4");
	searchirsignal();
	LCDclr();
	printf("press btn 5");
	searchirsignal();
	LCDclr();
	printf("press btn 6");
	searchirsignal();
	LCDclr();
	printf("press btn 7");
	searchirsignal();
	LCDclr();
	printf("press btn 8");
	searchirsignal();
	LCDclr();
	printf("press btn 9");
	searchirsignal();
	printf("press btn 0");
	LCDclr();
	searchirsignal();
	printf("press volume up");
	searchirsignal();
	LCDclr();
	printf("press volume dwn");
	searchirsignal();
	LCDclr();
	printf("Done :D");

	sei();
	init_server();

	while (1)
	{
		update_server();
		_delay_ms(100);
	}

	return 0;
}

static void searchirsignal()
{
	while (1)
	{
		ADCSRA |= (1 << ADSC);
		while ((ADCSRA & (1 << ADIF)) == 0)
		{
			int temp = ADC;
			if (temp != now)
			{
				PORTD ^= (1 << PD5);
				int i;
				for (i = 0; i < 1000; i++)
					_delay_ms(1);
				PORTD ^= (1 << PD5);
				now = temp;
			}
		}
	}
}
