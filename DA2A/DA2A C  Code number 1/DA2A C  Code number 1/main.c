#include <avr/io.h>

#define F_CPU 16000000UL  // Frequency board running


#include <util/delay.h>

int main(void)
{

	DDRB |= (1<<PB2);  // Define digital pin13/PORTB5 as an output so we can blink our led

	while(1) // Create infinite loop
	{
		PORTB |= (1<<PB2);                    // Turn led on
		_delay_ms(435);                        // Wait 0.435 second
		PORTB &= ~(1<<PB2);                    // Turn led off
		_delay_ms(300);                        // Wait 0.300 second
	}
}

