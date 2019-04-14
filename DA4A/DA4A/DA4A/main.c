#define F_CPU 16000000UL        // Frequency of the board
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

int adc_value;     // Used to hold ADC value
int p_button = 0;       // Used to hold button value to control motor ON/OFF

int main()
{
	sei();         // Enable global interrupt

	DDRC = (1 << PC2);   // Used to set PC2 as output
	DDRD = (1 << PD6);   // Used to set PD6 as output
	PORTC |= (1 << PC1);  // Used to enabled the pull up resistor

	TCCR0A= (1 << COM0A1) | (1 << WGM01) | (1 << WGM00);  // Used to set mode to Fast PWM with clear OCR0A on match
	TCCR0B= (1 << CS02) | (1 << CS00);  // Used to set the prescaler to 1024 for calculations

	PCICR = (1 << PCIE1);  // PCIE1 is set high, to enable PCMSK1
	PCMSK1 = (1 << PCINT9);  // PIN change interrupt source 9, so PC1 will serve as external interrupt source

	ADMUX = (0<<REFS1);   // Selecting voltage reference for ADC
	ADCSRA = 0b11100111;  // ADC enabled, ADC will start conversion, ADC auto trigger enabled, division factor set to 128

	while (1)
	{
		// Infinite loop, wait
	}
}

ISR(PCINT1_vect)
{

	if(!(PINC & ( 1 << PC1))) // If PC1 button pressed, enter if statement
	{
		if(p_button == 1)  // If p_button is high, enter if statement
		{
			while((ADCSRA & (1 << ADIF)) == 0);  // ADC conversion completes when high
			adc_value = ADC;      // The value in ADC placed in variable
			OCR0A = adc_value;      // Motor will run as value of ADC set to OCR0A
			_delay_ms(500);       // Used to remove denouncing
		}
		
		else if (p_button == 0) // If p_button is 0, enter if statement
		{
			OCR0A = 0;   // Motor will stop now
			_delay_ms(500);  // Used to remove denouncing
		}
		p_button ^= 1;   // Reset the value of button to 1
	}
}