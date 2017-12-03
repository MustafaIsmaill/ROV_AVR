/*
 * ROV.c
 *
 * Created: 11/17/2017 12:39:45 PM
 * Author : Mustafa Ismail
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include "initialization.h"

volatile uint8_t PWMcount = 0;
volatile const uint16_t compare1[6]={0,6666,13332,19998,26664,33330}; //base value for each thruster
volatile uint16_t compare2[6]={5300,5300,5300,5300,5300,5300}; //pwm received from i2c


volatile uint8_t TWIcount=0;
volatile uint8_t bytes[2]={0,0};
volatile uint16_t twoBytes;

int main(void)
{
	i2c_init(); //i2c
	ports_init(); //ports
	sei(); //global interrupt enable
	OCR1A = compare1[PWMcount];
	timer1_init(); //timer1
    while(1);
} 

ISR(TIMER1_COMPA_vect){
	PORTD |= (1<<PWMcount); //set pin
	OCR1B = compare1[PWMcount] + compare2[PWMcount]; //set pulse width
} 

ISR(TIMER1_COMPB_vect){
	PORTD &= ~(1<<PWMcount); //reset pin
	if(PWMcount == 5){PWMcount = 0;} //reset counter
	else{PWMcount++;} //increment counter
	OCR1A = compare1[PWMcount]; //set base value for the next thruster
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
			bytes[TWIcount] = TWDR;
			TWIcount++;
			break;
		case 0xA0: //stop or restart
			TWCR |= (1<<TWINT);
			break;
	}
	if(TWIcount==1){
		uint8_t lByte = bytes[1];
		uint8_t hByte = bytes[0];
		twoBytes = (hByte<<8) | lByte;
		bytes[0]=0; bytes[1]=0;
		TWIcount=0;
	}
}