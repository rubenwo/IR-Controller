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

int now = 2;
int counter = 0;
static void searchirsignal();
int main()
{
	DDRC = 0x00;
	DDRD = 0xFF;
	ADCSRA = 0b10000000;
	ADMUX = 0b011000010;
	LCDinit();
	LCDclr();

	printf("Started..");
	_delay_ms(1000);
	LCDclr();
	printf("press btn 1");
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
	LCDclr();
	printf("press btn 0");
	searchirsignal();
	LCDclr();
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
	int signaal = 1;
	while (signaal)
	{
			int temp = ADCH;
			if (temp != now)
			{
				_delay_ms(1000);
				now = temp;
				LCDclr();
				printf("%d",temp);
				signaal = 0;
				break;
			}
	}
}
