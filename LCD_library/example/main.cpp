/*
 * example.cpp
 *
 * Created: 28-Aug-19 8:40:02 AM
 * Author : Shimanto
 */ 

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include "lcd.h"

#define  lcd_port PORTC
#define lcd_DDR DDRC

int main(void)
{
	
	lcd myLCD (0,1,4,5,6,7); //RS,E,D4,D5,D6,D7
	uint16_t a = 1000;
	double b = 1.23;
	char* c = "Bismillah";
	
		
	while (1)
	{
		myLCD.print(a);
		_delay_ms(1000);
		myLCD.clear();
		myLCD.print(b);
		_delay_ms(1000);
		myLCD.clear();
		myLCD.print(c);
		_delay_ms(1000);
		myLCD.clear();
	}
}