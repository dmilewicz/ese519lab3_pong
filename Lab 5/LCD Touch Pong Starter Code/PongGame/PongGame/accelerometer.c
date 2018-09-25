//
// Created by David Milewicz on 9/25/18.
//

#include <avr/io.h>
#include <avr/interrupt.h>
#include "uart.h"
#include "adc.h"

ISR(ADC_vect) {
        printf("%d\n", sampler_insert(ADC));
        ADCSRA |= _BV(ADSC);
}

int main() {
    uart_init();
    sei();
    adc_init();

    while(1)  ;
}