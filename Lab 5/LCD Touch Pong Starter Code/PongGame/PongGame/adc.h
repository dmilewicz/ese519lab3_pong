//
// Created by David Milewicz on 9/19/18.
//

#ifndef LAB2_ADC_H
#define LAB2_ADC_H

#include <avr/io.h>
#include <stdio.h>

#define NUM_BUCKETS  59
#define SAMPLE_SIZE  10

#define INVERT

#if defined(ACCEL)

#define ADC_MIN 280
#define ADC_MAX 410

#elif defined(TOUCH)

#define ADC_MIN 217
#define ADC_MAX 774

#endif



unsigned int adc_sampler[SAMPLE_SIZE];
float adc_sampler_avg = 0;
int index_last = 0;

void adc_init(uint8_t chan) {
    ADMUX = _BV(REFS0) | chan; // reference V, channel 4
    ADCSRA |= _BV(ADPS0) | _BV(ADPS1) |_BV(ADPS2); // set prescaler
    ADCSRA |= _BV(ADEN) | _BV(ADIE) | _BV(ADSC) | _BV(ADATE); // enables ADC
    ADCSRB = 0;

    // set array values to 0
    memset(adc_sampler, 0x00, SAMPLE_SIZE * sizeof(unsigned int));
}

uint8_t adc_bucket(unsigned int input) {
    if (input < ADC_MIN) {
        return 0;
    } if (input > ADC_MAX) {
        return NUM_BUCKETS - 1;
    }

    return (uint8_t) ((input - ADC_MIN)/ ((float)(ADC_MAX - ADC_MIN) / NUM_BUCKETS));
}

uint8_t adc_bucket_n(unsigned int input, unsigned int num_buckets) {
    if (input < ADC_MIN) {
        return 0;
    } if (input > ADC_MAX) {
        return num_buckets - 1;
    }

    return (uint8_t) ((input - ADC_MIN)/ ((float)(ADC_MAX - ADC_MIN) / num_buckets));
}

uint16_t adc_invert(uint16_t val) {
    return (ADC_MAX - (val - ADC_MIN));
}

uint16_t sampler_insert(uint16_t val) {
    // update running average
    adc_sampler_avg -= (adc_sampler[SAMPLE_SIZE-1] / (float) SAMPLE_SIZE);
    adc_sampler_avg += (val / (float) SAMPLE_SIZE);

    for (int i = SAMPLE_SIZE-1; i > 0; i--) {
        adc_sampler[i] = adc_sampler[i-1];
    }

    // update recent value
    adc_sampler[0] = val;

    return (uint16_t) adc_sampler_avg;
}



uint16_t circ_sampler_insert(uint16_t val) {
    // replace old value in the running average
    adc_sampler_avg -= (adc_sampler[index_last] / (float) SAMPLE_SIZE);
    adc_sampler_avg += (val / (float) SAMPLE_SIZE);

    //insert new value
    adc_sampler[index_last] = val;

    //increment index
    index_last = ++index_last % SAMPLE_SIZE;

    return (uint16_t) adc_sampler_avg;
}


#endif //LAB2_ADC_H
