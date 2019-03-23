// The following Code is #3 of DA2C, covering the topic of #2 (Switch) from DA2A

#include <avr/io.h>
#include <avr/interrupt.h>

int ocount = 0;                              // Counter initialized

int main(void)
{
	DDRB |= (1<<DDB2);                       // Output is set to PB2
	TCCR0A |= (1 << WGM01);                  // Using CTC Mode
	TCNT0 = 0x00;                            // Declaring Timer Register set to 0
	OCR0A = 0xFF;                            // Top timer value (255) to output compare register
	TCCR0B |= (1 << CS02 | (1 << CS00));     // Used to set prescaler to 1024
	sei();									 // Set Global Interrupt Enable
	TIMSK0 = (1 << OCIE0A);                  // Compare match is enabled when OCIE0A is set
	
	while(1)
	{
		// Infinite loop
	}

}
ISR (TIMER0_COMPA_vect)                  // Timer0 Compare match
{
	while((TIFR0 & 0x01) == 1)           // While timer interrupt flag is equal to 2 loop
	{
		TCNT0 = 0x00;                    // TCNT0 set to 0x00 and will count up to 255
		TIFR0 = 0x01;                    // TIFR0 is 0x02 so TOV0 is set due to overflow occurrence
		ocount++;                        // Increment overflow counter
		
		if((PINC & 0x02) == 0x02)        // Reading from 1st pin
		{
			TCNT0 = 0x00;                // TCNT set to count to 255 for counter
			if (ocount < 35)             // Loop as long as counter is less than calculated timer value
			{
				PORTB = 0xFF;            // LED ON while loop runs
				ocount = 0;				 // Resetting counter back to 0
			}
		}
		
		else if (ocount > 35)            // If counter is greater than 17, LED needs to be OFF
		{
			PORTB = 0x00;			     // LED OFF if nothing read from 1st pin
			ocount = 0;                  // Counter set back to 0
		}
	}
}