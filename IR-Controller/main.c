/*
* IR-Controller.c
*
* Created: 3/20/2019 11:10:12 AM
* Author : Ruben
*/
#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>

int main(void)
{
	
	DDRB &= ~(1<<DDB7);
	while(1)
	{
		if(!(PINB & (1<<PINB7))){
			PORTB = 0B00111111;
			PORTD = 0B11111100;
			_delay_ms(1000);
			PORTB = 0B00000000;
			PORTD = 0B00000000;
			_delay_ms(1000);
		}
		
	}
	
}

