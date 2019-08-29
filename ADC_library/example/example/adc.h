#include <avr/io.h>
#include <util/delay.h>

class adc
{
	public:
		adc()
		{
			//AREF = AVcc, ADLAR = 0
			ADMUX |= (1<<REFS0);
			
			//ADC Enable and pre-scaler of 128
			//16000000/128 = 125000 -> 125kHz
			//ADATE, ADIF, ADIE -> 0
			ADCSRA = (1<<ADEN)|(1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0);
			_delay_ms(10);
		}
		
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
		
		~adc(){
			
		}

	private:
};
