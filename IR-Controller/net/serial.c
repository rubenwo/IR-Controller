/*
* serial.c
*
* Created: 3/29/2019 11:33:01 AM
*  Author: Ruben
*/
#ifndef F_CPU
#define F_CPU 16000000UL
#endif

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#include "serial.h"
#include "../utils/debug_util.h"

#define BAUD 9600
#define BIT(x) (1 << x)

char buffer[256];
int received = 0;

int serial_init(void)
{
	UBRR0 = (((F_CPU / (BAUD * 16UL))) - 1);
	UCSR0B = _BV(RXEN0) | _BV(TXEN0);
	UCSR0C = 0b00000110;
	return 0;
}

int serial_begin(void)
{
	UCSR0B |= (1 << RXCIE0);
	return 0;
}

int serial_write_char(char ch)
{
	while (!(UCSR0A & BIT(UDRE0)))
		;
	UDR0 = ch;
	return 0;
}

char serial_receive_char(void)
{
	while (!(UCSR0A & BIT(RXC0)))
		;
	return UDR0;
}

int serial_write_string(char *str, int len)
{

	int i = 0;

	for (i = 0; i < len; i++)
	{
		if (serial_write_char(str[i]) != 0)
		{
			return -1;
		}
	}
	return 0;
}

int serial_receive_string(char *str)
{
	int stop = 0; // boolean for stop value
	int count = 0;
	char ch;
	while (!stop) // while contunie
	{
		ch = serial_receive_char(); // read ch
		if (count == 50)			// stop at LF
			stop = 1;
		else
			*str++ = ch; // else fill buffer
		count++;
	}
	*str = '\0'; // string terminator
	return 0;
}

void serial_print_response(void)
{
	serial_write_string(buffer, strlen(buffer));
}

ISR(USART_RX_vect)
{
	char ReceivedByte;

	ReceivedByte = UDR0;
	buffer[received] = ReceivedByte;
	received++;

	if (received >= 256)
		received = 0;
	//blink_onboard();
}