#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>
#include <stdio.h>

//the default port is PORTC
#ifndef lcd_port
#define lcd_port PORTC
#define lcd_DDR DDRC
#endif

class lcd{
	private:
	int RS, E, D4, D5, D6, D7;
	void send_cmd(unsigned char cmd)
	{
		lcd_port = (lcd_port & 0x0F) | (cmd & 0xF0); //sending the higher nibble of the cmd to the last 4 pins of lcd_port
		lcd_port &= ~(1<<RS); //command register select (0)
		lcd_port |= (1<<E); //making enable pin high, ready for receiving data
		_delay_us(10);
		lcd_port &= ~(1<<E); //turning off the Enable pin
		
		_delay_us(200);
		lcd_port = (lcd_port & 0x0F) | (cmd << 4); //sending the higher nibble of the cmd to the last 4 pins of lcd_port
		lcd_port &= ~(1<<RS); //command register select (0)
		lcd_port |= (1<<E); //making enable pin high, ready for receiving data
		_delay_us(10);
		lcd_port &= ~(1<<E); //turning off the enable pin
		
		_delay_ms(5);
	}

	public:
	lcd(int register_select, int enable, int data4, int data5, int data6, int data7)
	{
		//if lcd_port not defined then the default lcd_port is PORTC
		
		RS = register_select;
		E = enable;
		D4 = data4;
		D5 = data5;
		D6 = data6;
		D7 = data7;

		//make the lcd pins output
		lcd_DDR = lcd_DDR | (1<<RS) | (1<<E) | (1<<D4) | (1<<D5) | (1<<D6) | (1<<D7);
		_delay_ms(20);
		
		send_cmd(0x02);	// send for 4 bit initialization of LCD
		send_cmd(0x28);	// 2 line, 5*7 matrix in 4-bit mode
		send_cmd(0x0C);	// Display on cursor off
		send_cmd(0x01); // Clear Display
	}
	
	void printCh(unsigned char str)
	{
		lcd_port = (lcd_port & 0x0F) | (str & 0xF0); // Sending upper nibble
		lcd_port |= (1<<RS);  // RS=1, data reg.
		lcd_port|= (1<<E); //turn on the enable pin
		_delay_us(1);
		lcd_port &= ~ (1<<E); //turn off the enable pin
		_delay_us(200);
		
		lcd_port = (lcd_port & 0x0F) | (str <<4); // Sending upper nibble
		lcd_port |= (1<<RS);  // RS=1, data reg.
		lcd_port|= (1<<E); //turn on the enable pin
		_delay_us(1);
		lcd_port &= ~ (1<<E); //turn off the enable pin
		_delay_ms(5);
	}
	void print(char *str)
	{
		int i;
		for(i=0;str[i]!=0;i++)		// Send each char of string till the NULL
		{
			printCh(str[i]);
		}
	}
	void print(int num)
	{
		char temp_str[16]; //as the maximum length is 16
		itoa(num,temp_str,10); //convert the number to char*
		print(temp_str);
	}
	void print(uint16_t num)
	{
		char temp_str[16]; //as the maximum length is 16
		itoa(num,temp_str,10); //convert the number to char*
		print(temp_str);
	}
	
	//
	// Thanks to the writer of this link
	// https://startingelectronics.org/articles/atmel-AVR-8-bit/print-float-atmel-studio-7/
	//
	
	void print(double num)
	{
		char buf[16];
		sprintf(buf,"%.2f", num); //convert the double to formatted char*
		print(buf);
	}
	
	void clear()
	{
		send_cmd(0x01); // Clear Display
	}
	
};