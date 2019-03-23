// The following Code is #1 of DA2C, covering the topic of #1 (Duty Cycle) from DA2A


#define F_CPU 16000000UL                 // Frequency of the board
#include <avr/io.h>

int main(void)
{
	int ocount = 0;                      // Declaring overflow counter
	DDRB |= (1 << DDB2);                 // LED 2 is the output
	TCCR0A = 0;                          // Using Normal mode
	TCNT0 = 0x00;                        // Declaring Timer Register set to 0
	TCCR0B |= (1 << CS02 | (1 << CS00)); // Used to set prescaler to 1024
	
	while(1)                             // Infinite loop
	{
		while((TIFR0 & 0x01) == 1)       // While timer interrupt flag is equal to 1 loop
		{
			TCNT0 = 0x00;                // TCNT0 set to 0x00 and will count up to 254
			TIFR0 = 0x01;                // TIFR0 is 0x01 so TOV0 is set due to overflow occurrence
			ocount++;                    // Increment overflow counter
			
			if (ocount <= 18)            // If overflow counter < 18, keep LED OFF (40%)
			PORTB = (0 << DDB2);         // Turn OFF LED
			
			else if (ocount >= 27)       // If overflow counter is >= 27, LED ON (60%)
			PORTB = (1 << DDB2);         // Turn ON LED
			
			if (ocount == 44)            // If overflow counter is equal to 44, reset overflow counter
			ocount = 0;                  // Overflow counter reset to 0 so operation will restart
		}
	}
}
