/*
 * memory.h
 *
 * Created: 29-3-2019 10:31:33
 *  Author: olaf
 */ 


#ifndef MEMORY_H_
#define MEMORY_H_

typedef struct{
	//hex values of keys
	int* keys[12][32]; //0 - 9 numbers, 10 = on/off, 11 volUp, 12 volDown (all hex values)
	int frequency;
	int highTime;
	int lowTime;
	char *name;
} ControllerTable_t;

ControllerTable_t *mem_getControllerTable(int);

void mem_saveKey(int*, int, ControllerTable_t*);

void initMemory(void);

#endif /* MEMORY_H_ */