/*
 * initialization.c
 *
 * Created: 11/17/2017 12:40:47 PM
 *  Author: Mustafa Ismail
 */ 

#include "initialization.h"

void i2c_init(void){
	 TWCR |= (1<<TWEN)|(1<<TWIE)|(1<<TWEA)|(1<<TWINT); //enable i2c, enable interrupt, enable ACK, set flag
	 TWAR = 0x20; //slave address
	 TWSR = 0x00; //initialize status register as zero
}

void timer1_init(void){
	TCCR1A |= (1<<WGM11)|(1<<COM1A1)|(1<<COM1B1); //fast pwm, ICR as top, non-inverting mode
	TCCR1B |= (1<<WGM12) | (1<<WGM13) | (1<<CS11); //pre-scale 8
//	TIMSK1 |= (1<<TOIE1) | (1<<OCIE1A) | (1<<OCIE1B); //interrupts enable
	ICR1 = 40000; //top value
	OCR1A = 20000; //pwm 1
	OCR1B = 10000; //pwm 2
}

void ports_init(void){
	DDRD = 0xFF; //port D as output
	DDRB = 0xFF; //port B as output
}