/*
* serial.h
*
* Created: 3/29/2019 11:33:10 AM
*  Author: Ruben
*/

#ifndef SERIAL_H_
#define SERIAL_H_

// serial_init initialises a uart connection with the esp8266 wifi module.
int serial_init(void);
// serial_begin starts the uart connection.
int serial_begin(void);
/*
serial_write_char writes the given char to the esp8266
@param ch - the character that should be written.
*/
int serial_write_char(char ch);
/*
    serial_receive_char receives and returns a character from the uart register
*/
char serial_receive_char(void);
/*
    serial_write_string is a wrapper around serial_write_char for sending a complete string at once.
    @param str - The string that should be written over the uart connection.
    @param len - The length of the string.
*/
int serial_write_string(char *str, int len);
/*
    serial_receive_string is a wrapper around serial_receive_char for receiving an entire string at once.
    @param str - An initialized char* (pass by reference)
*/
int serial_receive_string(char *str);
/*
    serial_print_response prints the response saved in the buffer variable
*/
void serial_print_response(void);
#endif /* SERIAL_H_ */