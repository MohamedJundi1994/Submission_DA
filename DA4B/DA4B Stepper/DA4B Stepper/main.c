#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>

int adc_value;					// variable used to hold ADC value

int main(void)
{
	DDRB = 0xFF;						// Used to set all pins as output
	PORTB = 0;							// Used to make initial value 0
	
	ADMUX = (0 << REFS1) | (1 << REFS0);	// AREF, internal Vref turned off
	ADCSRA = 0b11100111;				    // ADC enabled, ADC will start conversion, ADC auto trigger enabled, division factor set to 128
	
	TCCR1A = (1 << COM1A1);              // Used to clear OC1A on compare match
	TCCR1B = (1 << WGM12) | (1 << CS12) | (1 << CS10); // Used for setting mode to CTC and setting a prescaler of 1024
	
	adc_value = ADC;
	OCR1A = adc_value;						// OCR1A holds adc value
	
	while(1)
	{										// Following code used to rotate stepper motor counter clockwisse with full step sequence
		if ((OCR1A >= 0) && (OCR1A < 100))
		{
			PORTB = 0x09;
			_delay_ms(5);
			PORTB = 0x03;
			_delay_ms(5);
			PORTB = 0x06;
			_delay_ms(5);
			PORTB = 0x0c;
			_delay_ms(5);
			
			OCR1A = adc_value;
		}

		if ((OCR1A >= 100) && (OCR1A < 200))
		{
			PORTB = 0x09;
			_delay_ms(50);
			PORTB = 0x03;
			_delay_ms(50);
			PORTB = 0x06;
			_delay_ms(50);
			PORTB = 0x0c;
			_delay_ms(50);
			
			OCR1A = adc_value;
		}

		if ((OCR1A >= 200) && (OCR1A < 300))
		{
			PORTB = 0x09;
			_delay_ms(100);
			PORTB = 0x03;
			_delay_ms(100);
			PORTB = 0x06;
			_delay_ms(100);
			PORTB = 0x0c;
			_delay_ms(1000);
			
			OCR1A = adc_value;
		}

	}
}

