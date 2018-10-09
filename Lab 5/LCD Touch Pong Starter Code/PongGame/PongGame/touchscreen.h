

//#include "uart.h"
#include <avr/io.h>
#include <avr/interrupt.h>

volatile int x_touch = 0;
volatile int y_touch = 0;

#define Y_minus PC0
#define X_plus PB5
#define Y_plus PB4
#define X_minus PC1



void y_read(){

    DDRB |= (1 << X_plus); //Set X+ as digital output
    PORTB &= ~(1 << X_plus); //Set X+ low

    DDRC |= (1 << X_minus); //Set X- as digital output
    PORTC |= (1 << X_minus); //Set X- high

    DDRB &= ~(1 << Y_plus);
    PORTB &= ~(1 << Y_plus); //Set Y+ high z

    ADMUX = _BV(REFS0) | 0x00; //Channel select
    ADCSRA |= _BV(ADPS0) | _BV(ADPS1) |_BV(ADPS2); // set prescaler
    ADCSRA |= _BV(ADEN) | _BV(ADIE) | _BV(ADSC) | _BV(ADATE); // enables ADC
    ADCSRB = 0; //Free running mode
}


void x_read(){

    DDRB |= (1 << Y_plus); //Set Y+ as digital output
    PORTB &= ~(1 << Y_plus); //Set Y+ low

    DDRC |= (1 << Y_minus); //Set Y- as digital output
    PORTC |= (1 << Y_minus); //Set Y- high

    DDRB &= ~(1 << X_plus); //Set X+ high z
    PORTB &= ~(1 << X_plus);

    ADMUX = _BV(REFS0) | 0x01; //Channel select
    ADCSRA |= _BV(ADPS0) | _BV(ADPS1) |_BV(ADPS2); // set prescaler
    ADCSRA |= _BV(ADEN) | _BV(ADIE) | _BV(ADSC) | _BV(ADATE); // enables ADC
    ADCSRB = 0; //Free running mode

}