/*
* debug_util.c
*
* Created: 3/29/2019 4:13:05 PM
*  Author: Ruben
*/
#ifndef F_CPU
#define F_CPU 16000000UL
#endif

#include <avr/io.h>
#include <util/delay.h>
#include "debug_util.h"

void blink_onboard()
{
	DDRB = 0b00111111;
	DDRD = 0b11111100;
	PORTB = 0b00111111;
	PORTD = 0b11111100;
	_delay_ms(50);
	PORTB = 0b00000000;
	PORTD = 0b00000000;
	_delay_ms(50);
}