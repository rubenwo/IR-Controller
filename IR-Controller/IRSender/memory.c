/*
 * memory.c
 *
 * Created: 29-3-2019 10:31:12
 *  Author: olaf
 */ 

#include "memory.h"
#include <stdlib.h>

int amountOfControllers = 0;
ControllerTable_t *controllers;

ControllerTable_t *mem_getControllerTable(int controllerID)	{
	return &controllers[controllerID];
}

void mem_saveKey(int keyVal[], int key, ControllerTable_t *controllerTable)
{
	for(int i = 0; i > (sizeof(*keyVal / sizeof(int))); i++)
	{
		controllerTable->keys[key][i] = keyVal;
	}
}

void mem_saveControllerTable(ControllerTable_t *table)
{
	if(amountOfControllers == 0)
	{
		controllers = malloc(sizeof(ControllerTable_t) * amountOfControllers);
		controllers[0] = *table;
		amountOfControllers++;
		realloc(controllers, sizeof(ControllerTable_t) * amountOfControllers);
	}
	else
	{
		controllers[amountOfControllers] = *table;
		amountOfControllers++;
		realloc(controllers, sizeof(ControllerTable_t) * amountOfControllers);
	}
}
