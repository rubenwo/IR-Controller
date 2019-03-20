/*
* server.c
*
* Created: 3/20/2019 11:18:41 AM
*  Author: Ruben
*/


#include "wifi.h"
#include "api.h"
#include "json_parser.h"

char* flag = 0;


int init_server(void){
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