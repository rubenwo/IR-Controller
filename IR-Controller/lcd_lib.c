#define F_CPU 16000000

#include <stdio.h>
#include <avr/io.h>
#include <avr/pgmspace.h>
#include <inttypes.h>
#include "lcd_lib.h"

#include <util/delay.h>

static int LCDsendstream(char c, FILE *stream);
static FILE LCD_caracter = FDEV_SETUP_STREAM(LCDsendstream, NULL, _FDEV_SETUP_WRITE);
static int LCDsendstream(char c, FILE *stream)
{
	LCDsendChar(c);
	return 0;
}

void LCDinit(void)
{
	DR_LCD_RS |= (1 << LCD_RS);
	DR_LCD_E |= (1 << LCD_E);
	DR_LCD_D4 |= (1 << LCD_D4);
	DR_LCD_D5 |= (1 << LCD_D5);
	DR_LCD_D6 |= (1 << LCD_D6);
	DR_LCD_D7 |= (1 << LCD_D7);

	PR_LCD_RS &= ~(1 << LCD_RS);
	PR_LCD_E &= ~(1 << LCD_E);
	PR_LCD_D4 &= ~(1 << LCD_D4);
	PR_LCD_D5 &= ~(1 << LCD_D5);
	PR_LCD_D6 &= ~(1 << LCD_D6);
	PR_LCD_D7 &= ~(1 << LCD_D7);
	_delay_ms(20);

	PR_LCD_RS &= ~(1 << LCD_RS);

	LCDsend_nibble(0b0011);
	LCD_EnableCmd();
	_delay_ms(6);
	LCDsend_nibble(0b0011);
	LCD_EnableCmd();
	LCDsend_nibble(0b0011);
	LCD_EnableCmd();
	LCDsend_nibble(0b0010);
	LCD_EnableCmd();
	LCDsend_nibble(0b0010);
	LCD_EnableCmd();
	LCDsend_nibble(0b1100);
	LCD_EnableCmd();
	LCDsend_nibble(0b0000);
	LCD_EnableCmd();
	LCDsend_nibble(0b1100);
	LCD_EnableCmd();
	LCDsend_nibble(0b0000);
	LCD_EnableCmd();
	LCDsend_nibble(0b0001);
	LCD_EnableCmd();
	LCDsend_nibble(0b0000);
	LCD_EnableCmd();
	LCDsend_nibble(0b0110);
	LCD_EnableCmd();

	stdout = &LCD_caracter;
}

void LCDclr(void)
{
	LCDsendCommand(0b00000001);
	LCDsendCommand(0b00000010);
}

void LCDsendCommand(uint8_t Dato)
{
	PR_LCD_RS &= ~(1 << LCD_RS);

	uint8_t DatAux = Dato;
	Dato >>= 4;
	LCDsend_nibble(Dato);
	LCD_EnableCmd();
	LCDsend_nibble(DatAux);
	LCD_EnableCmd();
}

void LCD_EnableCmd(void)
{
	PR_LCD_E |= 1 << LCD_E;
	_delay_ms(1);
	PR_LCD_E &= ~(1 << LCD_E);
	_delay_ms(1);
}

void LCDsend_nibble(uint8_t Dat)
{
	union LCD_Dat {
		struct Lcd_Bit
		{
			unsigned int lcd_D4 : 1;
			unsigned int lcd_D5 : 1;
			unsigned int lcd_D6 : 1;
			unsigned int lcd_D7 : 1;
		} Bit;

		struct Lcd_Byte
		{
			unsigned int lcd_D;
		} Byte;
	} LCD;

	LCD.Byte.lcd_D = Dat;

	if (LCD.Bit.lcd_D4 == 0)
		PR_LCD_D4 &= ~(1 << LCD_D4);
	if (LCD.Bit.lcd_D5 == 0)
		PR_LCD_D5 &= ~(1 << LCD_D5);
	if (LCD.Bit.lcd_D6 == 0)
		PR_LCD_D6 &= ~(1 << LCD_D6);
	if (LCD.Bit.lcd_D7 == 0)
		PR_LCD_D7 &= ~(1 << LCD_D7);

	if (LCD.Bit.lcd_D4 == 1)
		PR_LCD_D4 |= 1 << LCD_D4;
	if (LCD.Bit.lcd_D5 == 1)
		PR_LCD_D5 |= 1 << LCD_D5;
	if (LCD.Bit.lcd_D6 == 1)
		PR_LCD_D6 |= 1 << LCD_D6;
	if (LCD.Bit.lcd_D7 == 1)
		PR_LCD_D7 |= 1 << LCD_D7;
}

void LCDsendChar(uint8_t Dato)
{
	PR_LCD_RS |= 1 << LCD_RS;

	uint8_t DatAux = Dato;
	Dato >>= 4;
	LCDsend_nibble(Dato);
	PR_LCD_E |= 1 << LCD_E;
	_delay_us(100);
	PR_LCD_E &= ~(1 << LCD_E);
	_delay_us(100);
	LCDsend_nibble(DatAux);
	PR_LCD_E |= 1 << LCD_E;
	_delay_us(100);
	PR_LCD_E &= ~(1 << LCD_E);
	_delay_us(100);
}