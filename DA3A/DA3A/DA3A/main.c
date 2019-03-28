#define F_CPU 16000000UL                                       // Run at 16MHz
#include <avr/io.h>
#include <avr/interrupt.h>                                     // Interrupt library included
#include <stdio.h>                                             // Stdio library included
#define BAUDRATE 9600                                          // Needed for communication with board
#define BAUD_PRESCALLER (((F_CPU / (BAUDRATE * 16UL))) - 1)    // Needed for communication with board

void USART_init( unsigned int ubrr );                          // Used to call function for integer
void USART_tx_string( char *data );                            // Used to call function for string


char String[] = "I LOVE PANCAKES";                             // "I LOVE PANCAKES" will display and be used to hold string value
char outs[25];                                                 // Display 25 spaces when running
char blank[] = " ";                                            // Used for spacing
int ran_dom;                                                   // Used for random number holder
float my_number = 19.94;                                       // Used 19.94 as my float number


int main(void)
{
	sei();                                                     // Declare global interrupt
	TCCR1A |= (1 << CS12 | (1 << CS10)) ;                      // Used to set prescaler of 1024
	TIMSK1 = (1 << TOIE1);                                     // TOIE1 will be set high and enable overflow
	TCNT1 = 49911;                                             // Set to count from 49911 to count up to 65535 to achieve 1 second
	USART_init(BAUD_PRESCALLER);                               // Used to initialize USART BAUD PRESCALLER
	USART_tx_string("Connected!\r\n");						   // Used to initialize and give heads up for display
	USART_tx_string(blank);                                    // Inserted to make a separation
	
	while (1)
	{
		                                                       // loop forever
	}
}
ISR (TIMER0_OVF_vect)                                          // Interrupt overflow
{
	USART_tx_string(String);                                   // Used to display my string of I LOVE PANCAKES
	USART_tx_string(blank);                                    // Used to create space
	ran_dom = rand();                                          // Used to generate a random number for display
	my_number = 19.94;                                         // Used to display my decimal of choice
	dtostrf(my_number, 2, 2, outs);                            // Used to allow for 2 decimal places to left, and right
	USART_tx_string(outs);                                     // Used for spacing of string
	USART_tx_string(blank);                                    // Used to create more space
	snprintf(outs, sizeof(outs), "%3d\r\n", ran_dom);          // Used to print out
	USART_tx_string(outs);                                     // Used for spacing of string
	USART_tx_string(blank);                                    // Used to create more space

	TCNT1 = 49911;                                             // Reset my TCNT1 value back so it can count to 1 second
}

/* INIT USART (RS-232)  */
void USART_init( unsigned int ubrr )
{
	UBRR0H = (unsigned char)(ubrr>>8);
	UBRR0L = (unsigned char)ubrr;
	UCSR0B = (1 << TXEN0)
	UCSR0C = (3 << UCSZ00);
}
/* SEND A STRING TO THE RS-232 */
void USART_tx_string( char *data )
{
	while ((*data != '\0'))
	{
		while (!(UCSR0A & (1 <<UDRE0)));
		UDR0 = *data;
		data++;
	}
}
