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

char* flag = 0;


int init_server(void){
	init_esp8266();
	blink_onboard();
	init_esp8266_wifi("HUAWEI P20 lite", "appel324");
	blink_onboard();
	init_esp8266_server();
	return 0;
}
