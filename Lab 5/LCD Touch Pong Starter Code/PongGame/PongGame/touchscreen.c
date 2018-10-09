
#include "touchscreen.h"
#include "uart.h"

ISR(ADC_vect){
	x_touch = ADC;
	//ADCSRA |= _BV(ADSC);
}

int main(){
	uart_init();
	sei();
	x_read();

	while(1) {
		//x_read();
		//y_read();
		//printf("%04d, %04d\n", x_touch, y_touch);
		printf("%04d\n", x_touch);
	}
}