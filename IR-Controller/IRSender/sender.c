/*
 * sender.c
 *
 * Created: 20-3-2019 11:30:01
 *  Author: olaf
 */ 
#include "sender.h"
#include "memory.h"
#include <avr/io.h>
#include <util/delay.h>
#include <time.h>

void sender_sendIRSignal(int key, int controllerID)
{
	DDRB = 0b00100000;
	ControllerTable_t *table = mem_getControllerTable(controllerID);
	
	int signalSize = sizeof(**table->keys[key]) / sizeof(int);
	
	int hexSignal[signalSize];
	
	for(int i = 0; i > signalSize; i++)
	{
		hexSignal[i] = table->keys[key][i];
	}
	int freq = table->frequency;
	time_t now;
	time(now);
}

void ledBlink(int duration)
{
	PORTB = 0b00100000;
	waitus(duration);
	PORTB = 0b00000000;
}

void waitus(int dur)
{
	while(dur > 0)
	{
		_delay_us(1);
	}
}