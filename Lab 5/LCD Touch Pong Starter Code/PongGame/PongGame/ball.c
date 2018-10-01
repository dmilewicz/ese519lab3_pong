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
paddle padLeft;
paddle padRight;


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
    b.v.deltax = 7;
    b.v.deltay = 3;
    b.r = 5;

    padLeft.h = 25
    padleft.w = 2
    padLeft.p.x = 0
    padLeft.p.y = 19

    padLeft.h = 25
    padleft.w = 2
    padLeft.p.x = 62
    padLeft.p.y = 19


    int x = 125;
    int y = 20;
    int count = 0;

    //char countChar[20];


    while (1)
    {
        clear_buffer(buff);
        //drawline(buff, b.r , 0 , b.r, 64, 1);

        fillRect(buff, padLeft.p.x, padLeft.p.y, padLeft.w, padLeft.h, 1);
        fillRect(buff, padRight.p.x, padRight.p.y, padRight.w, padRight.h, 1)


        void fillrect(uint8_t *buff,uint8_t x, uint8_t y, uint8_t w, uint8_t h,uint8_t color) {

        fillcircle(buff, b.p.x, b.p.y, b.r, 1);

        vert_collide(&b);
        paddle_collide(&b);
        horiz_collide(&b);

        //collide(&b);
        update_pos(&b.p, &b.v);
        //sprintf(countChar, "%d", count);
        //drawstring(buff, 0, 0, countChar);
        write_buffer(buff);
        _delay_ms(100);
        count++;
    }
}