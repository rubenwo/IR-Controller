/*
* wifi.c
*
* Created: 3/20/2019 11:17:05 AM
*  Author: Ruben
*/
#ifndef F_CPU
#define F_CPU 16000000UL
#endif

#include <avr/io.h>
#include <util/delay.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "serial.h"

int init_esp8266(){
	return serial_begin();
}

int init_esp8266_wifi(char* SSID,  char* password){
	char* command = malloc(sizeof(char)*256);
	sprintf(command, "AT+CWJAP=\"%s\",\"%s\"\r\n",SSID, password);
	
	serial_write_string(command, strlen(command));
	free(command);
	return 0;
}

int init_esp8266_server(){
	char* cipmux = "AT+CIPMUX=1\r\n";
	serial_write_string( cipmux, strlen(cipmux) );

	char* serv = "AT+CIPSERVER=1,80\r\n";
	return serial_write_string(serv, strlen(serv));
}

int init_esp8266_client(){
	return 0;
}
int esp8266_on_event(){
	return 0;
}
int receive(char* buffer){
	return serial_read_string(buffer);
}

int transmit(char* addr, int port, char* data){
	return 0;
}
