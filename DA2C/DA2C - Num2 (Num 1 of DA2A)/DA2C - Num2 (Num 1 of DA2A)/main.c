// The following Code is #2 of DA2C, covering the topic of #1 (Duty Cycle) from DA2A

#define F_CPU 16000000UL              // Frequency of the board
#include <avr/io.h>
#include <util/delay.h>               // Library must include to use delays
#include <avr/interrupt.h>            // Library must be sued to include interrupts
int ocount = 0;

int main(void)
{
	DDRB |= (1 << DDB2);          		 // Setting LED 2 as the output
	TCCR0A = 0;							 // Used to verify we are in normal mode
	TIMSK0 |= (1 <<TOIE0);				 // Setting a 1 to TIMSK0 which will enable overflow interrupt
	TCNT0 = 0xFF;                        // Set TCNT to 0xFF
	sei();                               // Set Global Interrupt Enable
	TCCR0B |= (1 << CS02) | (1 << CS00); // Prescaler set to 1024
	
	while(1)
	{
		// Infinite while loop waiting on interrupt
	}
	
}
ISR (TIMER0_OVF_vect)               // Timer0 overflow interrupt
{
	while((TIFR0 & 0x02) == 2)      // While timer interrupt flag is equal to 2 loop
	{
		TCNT0 = 0xFF;               // TCNT0 set to 0xFF
		TIFR0 = 0x02;               // TIFR0 is 0x02 so OCF0A is set due to compare match
		ocount++;                   // Increment overflow counter
		
		if (ocount <= 18)           // If overflow counter < 18, keep LED OFF (40%)
		PORTB = (0 << DDB2);        // Turn OFF LED
		
		else if (ocount >= 27)      // If overflow counter is >= 27, LED ON (60%)
		PORTB = (1 << DDB2);        // Turn ON LED
		
		if (ocount == 44)           // If overflow counter is equal to 44, reset overflow counter
		ocount = 0;                 // Overflow counter reset to 0 so operation will restart
	}
}
