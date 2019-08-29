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
#include "adc.h"

#define lcd_port PORTC
#define lcd_DDR DDRC

int main()
{
	int adc_result;
	
	lcd myLCD(0,1,4,5,6,7);
	adc myADC;
	while(1)
	{
		adc_result = myADC.analogRead(0);      // read ADC value at PA0
		myLCD.print(adc_result);
		_delay_ms(1000);
		myLCD.clear();
	}
}
