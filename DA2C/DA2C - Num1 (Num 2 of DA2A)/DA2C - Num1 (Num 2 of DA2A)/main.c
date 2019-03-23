// The following Code is #1 of DA2C, covering the topic of #2 (Switch) from DA2A

#include <avr/io.h>

int ocount = 0;                              // Counter initialization

int main(void)
{
	DDRB |= (1<<DDB2);                       // Output is set to PB2
	TCCR0A = 0;                              // Using Normal mode
	TCNT0 = 0x00;                            // Declaring Timer Register set to 0
	TCCR0B |= (1 << CS02 | (1 << CS00));     // Used to set prescaler to 1024
	
	while(1)						         // Infinite loop
	{
		while((TIFR0 & 0x01) == 1)           // While timer interrupt flag is equal to 1 loop
		{
			TCNT0 = 0x0A;                    // TCNT0 set to 0x0A and will count up to 255
			TIFR0 = 0x01;                    // TIFR0 is 0x01 so TOV0 is set due to overflow occurrence
			ocount++;                        // Increment overflow counter
			
			if((PINC & 0x02) == 0x02)        // Reading from 1st pin
			{
				TCNT0 = 0xFF;                // Counter set to 0xFF, will lessen counter timing
				if (ocount < 35)             // Loop as long as counter value is less than calculation for time (1.25s)
				{
					PORTB = 0xFF;            // LED ON while loop runs
					ocount = 0;              // Counter set back to 0
				}
			}
			
			else if (ocount > 35)           // Loop as long as counter value is greater than calculation for time (1.25s)
			{
				PORTB = 0x00;			    // LED OFF if nothing read from 1st pin
				ocount = 0;                 // Counter set back to 0
			}
		}
	}
}
