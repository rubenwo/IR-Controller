/*
 * sender.c
 *
 * Created: 20-3-2019 11:30:01
 *  Author: olaf
 */ 
#include "sender.h"
#include <avr/io.h>
#include <util/delay.h>

void sender_sendIRSignal(int signal)
{
	DDRB = 0b00100000;
	
	PORTB = 0b00100000;
	_delay_ms(500);
	PORTB = 0b00000000;
	_delay_ms(500);
}