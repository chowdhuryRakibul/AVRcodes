/*
 * ADC.cpp
 *
 * Created: 28-Aug-19 6:05:29 PM
 * Author : Shimanto
 */ 

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>

#include "lcd.h"

#define lcd_port PORTC
#define lcd_DDR DDRC

//initialize ADC
void adc_init()
{
	//AREF = AVcc, ADLAR = 0
	ADMUX |= (1<<REFS0);
	
	//ADC Enable and pre-scaler of 128
	//16000000/128 = 125000 -> 125kHz
	//ADATE, ADIF, ADIE -> 0
	ADCSRA = (1<<ADEN)|(1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0);
	_delay_ms(10);
}

// read ADC value
int analogRead(uint8_t ch)
{
	int result = 0;
	// select the corresponding channel 0~7
	// ANDing with '7' will always keep the value of 'ch' between 0 and 7
	ch &= 0x07;  // AND operation with 7 -> 0000 0111
	ADMUX = (ADMUX & 0xF8) | ch;     // clears the bottom 3 bits before ORing F8 -> 1111 1000
	
	// start single conversion
	// write '1' to ADSC
	ADCSRA |= (1<<ADSC);
	
	// wait for conversion to complete
	// ADSC becomes '0' again
	// till then, run loop continuously
	while(ADCSRA & (1<<ADSC));
	result = result | (ADCL) | (ADCH<<8); //As ADLR = 0
	
	return (result);
}

int main()
{
	int adc_result;
	
	lcd myLCD(0,1,4,5,6,7);
	adc_init();
	while(1)
	{
		adc_result = analogRead(0);      // read ADC value at PA0
		myLCD.print(adc_result);
		_delay_ms(1000);
		myLCD.clear();
	}
}
