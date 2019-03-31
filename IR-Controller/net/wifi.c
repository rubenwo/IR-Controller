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

int init_esp8266()
{
	serial_init();
	return serial_begin();
}

int init_esp8266_wifi(char *SSID, char *password)
{
	char *command = malloc(sizeof(char) * 256);
	char *rst = "AT+RST\r\n\0";
	char *mode = "AT+CWMODE=1\r\n\0";
	char *ip = "AT+CIFSR\r\n\0";

	serial_write_string(rst, strlen(rst)); // Reset wifi module

	serial_write_string(mode, strlen(mode)); // Set esp8266 mode to sta (non-ap)

	sprintf(command, "AT+CWJAP=\"%s\",\"%s\"\r\n", SSID, password); // Connect esp8266 to AP using SSID and password
	serial_write_string(command, strlen(command));

	serial_write_string(ip, strlen(ip)); // Get the ip address

	free(command);
	return 0;
}

int init_esp8266_server()
{
	char *cipmux = "AT+CIPMUX=0\r\n\0";
	serial_write_string(cipmux, strlen(cipmux));

	char *serv = "AT+CIPSERVER=1,80\r\n\0";
	serial_write_string(serv, strlen(serv));

	return 0;
}

int init_esp8266_client()
{
	return 0;
}
int esp8266_on_event()
{
	return 0;
}

char esp8266_receive(void)
{
	return serial_receive_char();
}

int receive(char *buffer)
{
	return serial_receive_string(buffer);
}

int transmit(char *addr, int port, char *data)
{
	return 0;
}
