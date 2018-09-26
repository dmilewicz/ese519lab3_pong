#include <avr/interrupt.h>
#include <avr/io.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <util/delay.h>
#include "lcd.h"

#define FREQ 16000000
#define BAUD 9600
#define HIGH 1
#define LOW 0
#define BUFFER 1024
#define BLACK 0x000001

char displayChar = 0;

int main(void)
{
	//setting up the gpio for backlight
	DDRD |= 0x80;
	PORTD &= ~0x80;
	PORTD |= 0x00;
	
	DDRB |= 0x05;
	PORTB &= ~0x05;
	PORTB |= 0x00;
	
	//lcd initialisation
	lcd_init();
	lcd_command(CMD_DISPLAY_ON);
	lcd_set_brightness(0x18);
	write_buffer(buff);
	_delay_ms(1000);
	clear_buffer(buff);
	
	while (1)
	{
		//Geometric & screen control demo 

		lcd_command(CMD_SET_ALLPTS_NORMAL);
		lcd_command(CMD_SET_DISP_NORMAL);

		lcd_command(CMD_SET_VOLUME_FIRST);
		lcd_command(32);

		drawstring(buff, 0, 0, "Embedded Systems");

		drawline(buff, 40, 50, 75, 50, 0);
		drawline(buff, 10, 40, 10, 60, 0);

		fillrect(buff, 10, 10, 20, 20, 0);
		drawrect(buff, 40, 10, 20, 20, 0);

		drawcircle(buff, 100, 20, 10, 0);
		fillcircle(buff, 100, 50, 10, 0);

		write_buffer(buff);

		_delay_ms(1000);



		lcd_command(CMD_SET_DISP_REVERSE);
		_delay_ms(1000);
		lcd_command(CMD_SET_ALLPTS_ON);
		_delay_ms(1000);



	}
}

