/*
* wifi.h
*
* Created: 3/20/2019 11:17:15 AM
*  Author: Ruben
*/

#ifndef WIFI_H_
#define WIFI_H_

int init_esp8266();
/*
init_esp8266_wifi is used to initialize a connection with a WiFi AP.
@param SSID is the SSID of the WiFi AP.
@param password is the password for the WiFi AP
*/
int init_esp8266_wifi(char *SSID, char *password);

int init_esp8266_server(void);

int init_esp8266_client(void);

int esp8266_on_event(void);

char esp8266_receive(void);

/*
receive is used to receive data from a connection.
@param buffer
*/
int receive(char *buffer);

/*
transmit is used to send data to a connection.
@param addr is a the IP-address of the client.
@param port is the port of the client.
@param data is the
*/
int transmit(char *addr, int port, char *data);

#endif /* WIFI_H_ */