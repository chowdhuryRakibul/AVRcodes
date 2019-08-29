/*
 * LCD.cpp
 *
 * Created: 25-Aug-19 2:36:35 PM
 * Author : Shimanto
 */ 


#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>
#include <stdio.h>

//define LCD pins
#define lcd_port PORTC
//char* lcd_port = "PORTC";
#define RS 0
#define E 1

#define D4 4
#define D5 5
#define D6 6
#define D7 7


void lcd_init();
void send_cmd(unsigned char cmd);
void lcd_printCh(unsigned char str);
void lcd_print(char *str);
void lcd_print(int num);
void lcd_print(double num);



int main(void)
{
	float a = 10.12;
	lcd_init();
	lcd_print(a);
	
    
    while (1) 
    {
    }
}

void lcd_init()
{
	//set everything as output
	DDRC = DDRC | (1<<RS) | (1<<E) | (1<<D4) | (1<<D5) | (1<<D6) | (1<<D7);
	_delay_ms(20);
	
	send_cmd(0x02);		// send for 4 bit initialization of LCD  
	send_cmd(0x28);	// 2 line, 5*7 matrix in 4-bit mode
	send_cmd(0x0C);	// Display on cursor off 
	send_cmd(0x01); // Clear Display
	
}
void send_cmd(unsigned char cmd)
{
	
	lcd_port = (lcd_port & 0x0F) | (cmd & 0xF0); //sending the higher nibble of the cmd to the last 4 pins of lcd_port
	lcd_port &= ~(1<<RS); //command register select (0)
	lcd_port |= (1<<E); //making enable pin high, ready for receiving data
	_delay_us(10);
	lcd_port &= ~(1<<E);
	
	_delay_us(200);
	lcd_port = (lcd_port & 0x0F) | (cmd << 4); //sending the higher nibble of the cmd to the last 4 pins of lcd_port
	lcd_port &= ~(1<<RS); //command register select (0)
	lcd_port |= (1<<E); //making enable pin high, ready for receiving data
	_delay_us(10);
	lcd_port &= ~(1<<E);
	
	_delay_ms(5);
	
}
void lcd_printCh(unsigned char str)
{
	lcd_port = (lcd_port & 0x0F) | (str & 0xF0); // Sending upper nibble
	lcd_port |= (1<<RS);  // RS=1, data reg.
	lcd_port|= (1<<E);
	_delay_us(1);
	lcd_port &= ~ (1<<E);
	_delay_us(200);
	
	lcd_port = (lcd_port & 0x0F) | (str <<4); // Sending upper nibble
	lcd_port |= (1<<RS);  // RS=1, data reg.
	lcd_port|= (1<<E);
	_delay_us(1);
	lcd_port &= ~ (1<<E);
	_delay_ms(5);
}

void lcd_print(char *str)
{
	int i;
	for(i=0;str[i]!=0;i++)		/* Send each char of string till the NULL */
	{
		lcd_printCh(str[i]);
	}
}


void lcd_print(int num)
{
	char temp_str[16]; //as the maximum length is 16
	itoa(num,temp_str,10);
	lcd_print(temp_str);
}

/*
* Thanks to the writer of this link
* https://startingelectronics.org/articles/atmel-AVR-8-bit/print-float-atmel-studio-7/
*/
void lcd_print(double num)
{
	char buf[16];
	sprintf(buf,"%.2f", num);
	lcd_print(buf);
}