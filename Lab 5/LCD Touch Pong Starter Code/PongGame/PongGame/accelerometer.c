//
// Created by David Milewicz on 9/25/18.
//

#include <avr/io.h>
#include <avr/interrupt.h>
#include "uart.h"
#include "adc.h"





int main() {
    uart_init();
    sei();
    adc_init();


    while(1)  ;
}


ISR(ADC_vect) {
//    if (circ_sampler_insert(ADC) == sampler_insert(ADC)) {
//        printf("TRUE\n");
//    } else {
//        printf("FALSE\n");
//    }
    printf("%d\n", circ_sampler_insert(ADC));
    ADCSRA |= _BV(ADSC);
}
