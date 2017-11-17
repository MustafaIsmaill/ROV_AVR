/*
 * initialization.h
 *
 * Created: 11/17/2017 12:41:15 PM
 *  Author: Mustafa Ismail
 */ 


#ifndef INITIALIZATION_H_
#define INITIALIZATION_H_

#include <avr/io.h>

void i2c_init(void);
void timer1_init(void);
void ports_init(void);

#endif /* INITIALIZATION_H_ */