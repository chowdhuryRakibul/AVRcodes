/*
 * digitalIO.cpp
 *
 * Created: 25-Aug-19 1:10:25 PM
 * Author : Shimanto
 */ 

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
	DDRA |= (1<<0); //setting A0 as output
	DDRC &= ~(1<<0); //setting C0 as input
	PORTA &= (1<<0);
	_delay_ms(100);
	for(int i = 0; i<6; i++)
	{
		PORTA ^= (1<<0); //toggle A0
		_delay_ms(100);
	}
	/* Replace with your application code */
    while (1) 
    {
		if((PINC & (1<<0)) == 1)
		{
			PORTA ^= (1<<0); //toggle A0
			_delay_ms(100);			
		}
		
    }
}

