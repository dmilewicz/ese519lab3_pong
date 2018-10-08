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
#define MAXSCORE 9
#define BUZZER 0x40

char displayChar = 0;
uint16_t y_curr = 0;

ball b;
paddle padLeft;
paddle padRight;

char score1 = '0';
char score2 = '0';


void collide(ball *b, paddle *pad1, paddle *pad2) {
    vert_collide(b);
    paddle_collide(b, pad1);
    paddle_collide(b, pad2);
    horiz_collide(b);
}

void move() {
    update_pos(&b.p, &b.v);
    update_pos_paddle(&padLeft);
    update_pos_paddle(&padRight);
}

int main(void)
{
    //setting up the gpio for backlight
    DDRD |= 0x80;
    DDRD |= BUZZER;
    PORTD &= ~0x80;
    PORTD |= 0x00;

    DDRB |= 0x05;
    DDRB |= 0x08;
    PORTB &= ~0x05;
    PORTB |= 0x00;

    //Buzzer initialization with timer 2
    TCCR2A |= (1 << WGM21); //Set CTC bit
    OCR2A = 70; //Comparator value to attain 440 Hz with 256 prescaler

    TCCR2B = (1 << CS21) | (1 << CS22); //Set prescaler to 256 //Make CA21?
    TCCR2A &= !(1 << COM2A0); //Disconnect buzzer

    //lcd initialisation
    lcd_init();
    lcd_command(CMD_DISPLAY_ON);
    lcd_set_brightness(0x18);
    write_buffer(buff);
    _delay_ms(1000);
    clear_buffer(buff);

    //uart_init();

    sei();
    adc_init(4);

    b.r = 3;
    ball_reset(&b.p, &b.v);

    padLeft.h = 10;
    padLeft.l = 2;
    padLeft.p.x = 2;
    padLeft.p.y = 19;
    padLeft.v.deltax = 0;
    padLeft.v.deltay = 0;


    padRight.h = 10;
    padRight.l = 2;
    padRight.p.x = 126-padRight.l;
    padRight.p.y = 19;
    padRight.v.deltax = 0;
    padRight.v.deltay = 0;

    int x = 125;
    int y = 20;
    int count = 0;

    //char countChar[20];

    while (1)
    {
        clear_buffer(buff);
        //drawline(buff, b.r , 0 , b.r, 64, 1);

        drawline(buff, 0, 0, 127, 0, 1);
        drawline(buff, 0, 0, 0, 63, 1);
        drawline(buff, 127, 63, 0, 63, 1);
        drawline(buff, 127, 63, 127, 0, 1);

        drawchar(buff, (LCDWIDTH/2) - CHARWIDTH - 3, 0, score1);
        drawchar(buff, (LCDWIDTH/2) + 3, 0, score2);

        fillrect(buff, padLeft.p.x, padLeft.p.y, padLeft.l, padLeft.h, 1);
        fillrect(buff, padRight.p.x, padRight.p.y, padRight.l, padRight.h, 1);

        fillcircle(buff, b.p.x, b.p.y, b.r, 1);

        collide(&b, &padLeft, &padRight);

        pad_travel_to(&padLeft, b.p.y);

        move();

        write_buffer(buff);
        _delay_ms(50);
        //count++;
       
    }
}

char buf[20];
int counter = 0;

ISR(ADC_vect) {
    if (counter % 50 == 0) {
        int velocity = adc_bucket_n(circ_sampler_insert(adc_invert(ADC)), V_RANGE) - MAX_V;


//        printf("%d\n", velocity);

        padRight.v.deltay = velocity;
    }
    counter++;

}
