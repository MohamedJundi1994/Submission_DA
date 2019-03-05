#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
	DDRB |= (1<<PB2);                 // Output is set to PB2
	TCCR1B = (1<<CS12) | (1<<CS10);   // Setting prescaler to 1024 on counter 1 (binary = 101 => 1024)
	
	while(1)						  // Infinite loop
	{
		if((PINC & 0x02) == 0x02)     // Reading from 1st pin
		{
			TCNT1 = 0;                // Counter set to zero
			while (TCNT1 < 0x2625)    // Loop as long as counter is less than TCNT calculated value
			{
				PORTB = 0xFF;         // LED ON while loop runs
			}
		}
		else
		{
			PORTB = 0x00;			  // LED OFF if nothing read from 1st pin
		}
	}
	
	return 0;
}

