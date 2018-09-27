#include "uart.h"
#include <avr/io.h>
#include <avr/interrupt.h>

volatile int x_touch = 0, y_touch = 0;


void x_read(){

	DDRB |= 0x10; //Set X+ (PB4) as digital output
	PORTB &= ~(1<<PB4); //Set X+ low

	DDRC |= 0x01; //Set X- (PC0) as digital output
	PORTC |= (1<<PC0); //Set X- high

	DDRB &= ~(1<<PB5); //Set Y+ (PB5) high z

	ADMUX = _BV(REFS0) | 0x01; //Channel select
	ADCSRA |= _BV(ADPS0) | _BV(ADPS1) |_BV(ADPS2); // set prescaler
	ADCSRA |= _BV(ADEN) | _BV(ADIE) | _BV(ADSC) | _BV(ADATE); // enables ADC
	ADCSRB = 0; //Free running mode
}


void y_read(){

	DDRB |= 0x20; //Set Y+ (PB5) as digital output
	PORTB &= ~(1<<PB5); //Set Y+ low

	DDRC |= 0x02; //Set Y- (PC1) as digital output
	PORTC |= (1<<PC1); //Set Y- high

	DDRB &= ~(1<<PB4); //Set X+ (PB5) high z

	ADMUX = _BV(REFS0) | 0x00; //Channel select
	ADCSRA |= _BV(ADPS0) | _BV(ADPS1) |_BV(ADPS2); // set prescaler
	ADCSRA |= _BV(ADEN) | _BV(ADIE) | _BV(ADSC) | _BV(ADATE); // enables ADC
	ADCSRB = 0; //Free running mode

}

// ISR(ADC_vect){
// 	switch (ADMUX){
// 		case 0:
// 			x_touch = ADC;

// 			break;
// 		case 1:
// 			y_touch = ADC;
// 			break;
// 	}
// 	ADCSRA |= _BV(ADSC);
// }

ISR(ADC_vect){
	y_touch = ADC;
	//ADCSRA |= _BV(ADSC);
}

int main(){
	uart_init();
	sei();
	y_read();

	while(1){
		//x_read();
		//y_read();
		//printf("%04d, %04d\n", x_touch, y_touch);
		printf("%04d\n", y_touch);
	}
}