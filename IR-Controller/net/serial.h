/*
* serial.h
*
* Created: 3/29/2019 11:33:10 AM
*  Author: Ruben
*/


#ifndef SERIAL_H_
#define SERIAL_H_

int serial_begin();
int serial_write_string(char* str, int len);
int serial_read_string(char* buf);

#endif /* SERIAL_H_ */