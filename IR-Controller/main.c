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


int now = 2;
int counter = 0;

int main()
{
	DDRC = 0x00;
	DDRD = 0xFF;
	ADCSRA = 0b10000000;
	ADMUX = 0b01100001;
	uint8_t tekst = "Test";
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

	

    /* Set PB5 to output */
	
	//while(1){
	//
	//char string[16];
	//int temp = ADCH;
	//sprintf(string, "Temp: 0x%.2X", temp);
	//PORTC = ADCH;
	//_delay_ms(1000);
	//DDRC = 0b00000000;
	//if (PC3 >= 0)
	//{
		//DDRD = 0b11111111;
		//PORTD |= (1<< PD5);
		//_delay_ms(1000);
		//PORTD &= (1<<PD5);
	//}
	//}
    //return 0;
}

void searchirsignal(){
	while(1){
		ADCSRA |= (1<<ADSC);
		while((ADCSRA & (1<< ADIF)) == 0){
			int temp = ADC;
			if(temp != now){
				PORTD ^= (1<<PD5);
				int i;
				for(i =0; i<1000; i++)
				_delay_ms(1);
				PORTD ^= (1<<PD5);
				now = temp;
			}
		}
	}
}
	