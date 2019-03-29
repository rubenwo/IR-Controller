/*
* server.c
*
* Created: 3/20/2019 11:18:41 AM
*  Author: Ruben
*/

#include <avr/io.h>
#include <avr/delay.h>
#include "wifi.h"
#include "api.h"
#include "json_parser.h"

char* flag = 0;


int init_server(void){
	init_esp8266();
	PORTB = 0b00111111;
	PORTD = 0b11111100;
	_delay_ms(500);
	PORTB=0b00000000;
	PORTD=0b00000000;
	_delay_ms(500);
	init_esp8266_wifi("HUAWEI P20 lite", "appel324");
	PORTB = 0b00111111;
	PORTD = 0b11111100;
	_delay_ms(500);
	PORTB=0b00000000;
	PORTD=0b00000000;
	_delay_ms(500);
	init_esp8266_server();
	return 0;
}

int run_server(void){
	while(flag == 0){
		
	}
	return 0;
}

int interrupt_server(char* f){
	flag = f;
	return 0;
}