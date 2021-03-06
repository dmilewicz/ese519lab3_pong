#include <avr/interrupt.h>
#include <avr/io.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <util/delay.h>
#include "lcd.h"
#include "adc.h"
#include "uart.h"

#define FREQ 16000000
#define BAUD 9600
#define HIGH 1
#define LOW 0
#define BUFFER 1024
#define BLACK 0x000001

char displayChar = 0;
uint16_t y_curr = 0;

ISR(ADC_vect) {
        uint16_t v = circ_sampler_insert(ADC);
//        printf("%d\n", v);
        y_curr = adc_bucket(v);

        ADCSRA |= _BV(ADSC);
}



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
    uart_init();
	lcd_init();
	lcd_command(CMD_DISPLAY_ON);
	lcd_set_brightness(0x18);
	write_buffer(buff);
	_delay_ms(1000);
	clear_buffer(buff);

    sei();
    adc_init();
	
	while (1)
	{
        clear_buffer(buff);
        drawrect(buff, 45, y_curr, 5, 5, 1);
        write_buffer(buff);
	}
}

