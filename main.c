/*
 * ROV.c
 *
 * Created: 11/17/2017 12:39:45 PM
 * Author : Mustafa Ismail
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include "initialization.h"


int main(void)
{
	i2c_init(); //i2c
	timer1_init(); //timer1
	ports_init(); //ports

	sei(); //global interrupt enable

    while(1);
}

ISR(TWI_vect){ //i2c interrupt
	switch (TWSR){
		case 0x60: //address + write
			TWCR |= (1<<TWINT)|(1<<TWEA);
			TWCR &= ~(1<<TWSTO);
			break;
		case 0x80: //data
			TWCR |= (1<<TWINT)|(1<<TWEA);
			TWCR &= ~(1<<TWSTO);
			PORTB = TWDR; //output data to port D
			break;
		case 0xA0: //stop or restart
			TWCR |= (1<<TWINT);
			break;
	}
}