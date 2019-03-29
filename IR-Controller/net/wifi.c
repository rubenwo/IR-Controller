/*
* wifi.c
*
* Created: 3/20/2019 11:17:05 AM
*  Author: Ruben
*/
#include <avr/io.h>
#include <avr/delay.h>
#include "serial.h"

int init_esp8266(){
	serial_begin();
}

int init_esp8266_wifi(char* SSID,  char* password){
	char* command;
	sprintf(command, "AT+CWJAP=\"%c\",\"%c\"\r\n",SSID, password);
	
	serial_write_string(command, strlen(command));
	return 0;
}

int init_esp8266_server(){
	char* cipmux = "AT+CIPMUX=1\r\n";
	serial_write_string( cipmux, strlen(cipmux) );

	char* serv = "AT+CIPSERVER=1,80\r\n";
	serial_write_string(serv, strlen(serv));
}

int init_esp8266_client(){
	
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
