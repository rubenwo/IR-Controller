/*
* server.c
*
* Created: 3/20/2019 11:18:41 AM
*  Author: Ruben
*/

#include "../utils/debug_util.h"
#include "wifi.h"
#include "api.h"
#include "json_parser.h"
#include "server.h"

int init_server(void)
{
	init_esp8266();
	blink_onboard();
	init_esp8266_wifi("ssid", "password");
	update_server();
	blink_onboard();
	init_esp8266_server();
	update_server();
	blink_onboard();
	return 0;
}

int update_server(void)
{
	char c = esp8266_receive();
	if (c == 0)
	{
		return -1;
	}
	blink_onboard();
	return c;
}
