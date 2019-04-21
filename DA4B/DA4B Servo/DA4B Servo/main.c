#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>

int adc_value;					// variable used to hold ADC value

int main(void)
{
	DDRB = 0xFF;						// Used to set all pins as output for B
	DDRD = 0xFF;						// Used to set all pins as output for D
	
	ADMUX = (1 << REFS1) | (1 << REFS0);	// Internal 1.1 voltage reference
	ADCSRA = 0b10100110;				    // ADC enabled, ADC auto trigger enabled
	
	TCCR1A = (1 << COM1A1) | (1 << COM1B1) | (1 << WGM11) ;  // Used to clear OC1A on compare match fast PWM
	TCCR1B = (1 << WGM13) | (1 << WGM12) | (1 << CS12) | (1 << CS10); // Used for setting a prescaler of 1024 and Fast PWM

	ICR1 = 5000;					// ICR1 value set
	
	while(1)
	{										
		while((ADCSRA & (1 << ADIF)) == 0); // while conversion starts
		adc_value = ADC;			
		
		if(adc_value == 0)          // If pot value is at it's lowest enter if statement
		{
			OCR1A = 0;				// Used to turn to 0
			_delay_ms(600);			// Give time for transition
		}
		
		else if(adc_value == 255)   // If pot value is at it's highest enter if statement
		{
			OCR1A = 535;			// Used to turn to 180
			_delay_ms(600);         // Give time for transition 
		}
	}
}

