#define F_CPU 16000000UL      // CPU Frequency set to 16MHz
#include <avr/io.h>           // Header file for AVR
#include <avr/interrupt.h>    // Header file allowing use of interrupts
#include <util/delay.h>       // Header file allowing use of delays

int main(void)
{
	DDRB = (1<<5);           // Set PB4 as output
	PORTB = 0xFF;            // Set to turn off all LEDs
	PORTD = 1<<2;            // Set Pin PD2 as input
	EICRA = 0x2;             // 0x2 set to the register so falling edge of INT0 generates an interrupt request
	
	EIMSK = (1<<INT0);       // Enable external interrupt zero
	sei ();                  // Used to enable interrupts
	
	while (1)                // While loop for infinite loop
	{
		// No content in loop, used as a standby until interrupt
	}
}
ISR (INT0_vect)              // Interrupt service routine for external interrupt
{
	PORTB ^= (1<<5);         // XOR output on PB3
	_delay_ms(1250);         // Given delay time to use in ms
}


