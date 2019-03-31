#ifndef LCD_LIB
#define LCD_LIB

#include <stdio.h>
#include <avr/io.h>
#include <avr/pgmspace.h>
#include <inttypes.h>
#include <util/delay.h>

#define PR_LCD_RS	PORTC 	//define MCU pin connected to LCD RS
#define DR_LCD_RS	DDRC  	//define MCU pin connected to LCD RS

#define PR_LCD_E	PORTC	//define MCU pin connected to LCD E
#define DR_LCD_E	DDRC	//define MCU pin connected to LCD E

#define PR_LCD_D4	PORTD	//define MCU pin connected to LCD D3
#define DR_LCD_D4	DDRD	//define MCU pin connected to LCD D3

#define PR_LCD_D5	PORTD	//define MCU pin connected to LCD D4
#define DR_LCD_D5	DDRD	//define MCU pin connected to LCD D4

#define PR_LCD_D6	PORTB	//define MCU pin connected to LCD D5
#define DR_LCD_D6	DDRB	//define MCU pin connected to LCD D5	

#define PR_LCD_D7	PORTB	//define MCU pin connected to LCD D6
#define DR_LCD_D7	DDRB	//define MCU pin connected to LCD D6

#define LCD_RS	0 	//define MCU pin connected to LCD RS
#define LCD_E	1	//define MCU pin connected to LCD E
#define LCD_D4	2	//define MCU pin connected to LCD D4
#define LCD_D5	6	//define MCU pin connected to LCD D5
#define LCD_D6	3	//define MCU pin connected to LCD D6
#define LCD_D7	5	//define MCU pin connected to LCD D7


void LCDinit(void);		// Lcd Init
void LCDclr(void);		//Clears LCD
void LCDsendChar(uint8_t);	//send Characters to LCD
void LCD_EnableCmd(void);//Enable 
void LCD_EnableChar(void);//Enable
void LCDsendCommand(uint8_t);
void LCDsend_nibble(uint8_t Dat); 

#endif