/*
* serial.h
*
* Created: 3/29/2019 11:33:10 AM
*  Author: Ruben
*/


#ifndef SERIAL_H_
#define SERIAL_H_

int serial_init(void);
int serial_begin(void);
int serial_write_char(char ch);
char serial_receive_char(void);
int serial_write_string(char* str, int len);
int serial_receive_string(char* str);
void serial_print_response(void);
#endif /* SERIAL_H_ */