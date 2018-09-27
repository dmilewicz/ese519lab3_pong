//
// Created by David Milewicz on 9/27/18.
//

#include <avr/interrupt.h>
#include <avr/io.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <util/delay.h>
#include "lcd.h"
#include "adc.h"
//#include "uart.h"
#include "ball.h"

#define FREQ 16000000
#define BAUD 9600
#define HIGH 1
#define LOW 0
#define BUFFER 1024
#define BLACK 0x000001

char displayChar = 0;
uint16_t y_curr = 0;

ball b;


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
//    uart_init();
    lcd_init();
    lcd_command(CMD_DISPLAY_ON);
    lcd_set_brightness(0x18);
    write_buffer(buff);
    _delay_ms(1000);
    clear_buffer(buff);

    //sei();
    //adc_init();

    b.p.x = 50;
    b.p.y = 50;

    b.v.deltax = 3;
    b.v.deltay = 4;

    b.r = 5;
    int x = 125;
    int y = 20;



    while (1)
    {
        clear_buffer(buff);



        fillcircle(buff, b.p.x, b.p.y, b.r, 1);


        collide(&b);
        update_pos(&b.p, &b.v);
        write_buffer(buff);
        _delay_ms(100);
    }
}