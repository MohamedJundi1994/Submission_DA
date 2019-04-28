#ifndef F_CPU
#define F_CPU 16000000UL
#endif

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>


#ifndef BAUD				// Used to set UART for printf();
#define BAUD 9600
#endif
#include "STDIO_UART.h"

#include "nrf24l01.h"		// Must	include nRF24L01+ library
#include "nrf24l01-mnemonics.h"
#include "spi.h"

void print_config(void);
void read_adc(void);       
void adc_init(void);
volatile unsigned int adc_temp;
char outs[20];

volatile bool message_received = false; //	Used in IRQ ISR
volatile bool status = false;

int main(void)
{
	char tx_message[32];	// Used to declare string
	strcpy(tx_message,"This is the message from Moe");	// Copy this string into the array
	
	uart_init();	// Call function to initialize UART
	adc_init();		// Call function to  initialize ADC

	nrf24_init();	// Call function to initialize NRF24L01+
	print_config();	// Call function to print configure
	
	nrf24_start_listening();	// Call function to start listening
	
	while (1)
	{
		read_adc();
		adc_temp = (adc_temp*500)/1023 + 20;
		snprintf(outs,sizeof(outs),"%3d\r\n", adc_temp); 
		strcpy(tx_message,outs);	
		nrf24_send_message(tx_message);
		_delay_ms(1500);
		if (message_received)
		{
			message_received = false;
			printf("Message received: %s\n",nrf24_read_message());	// When message received, print the message
		
			_delay_ms(500);
			status = nrf24_send_message(tx_message);
			if (status == true) printf("Message sent successfully\n");	// When message sent, print this message
		}
	}
}

ISR(INT0_vect)	//	Interrupt on IRQ pin
{
	message_received = true;
}

// INIT ADC
void adc_init(void)
{
	/** Setup and enable ADC **/
	ADMUX = (0<<REFS1)|    // Reference Selection Bits
	(1<<REFS0)|    // AVcc - external cap at AREF
	(0<<ADLAR)|    // ADC Left Adjust Result
	(1<<MUX2)|     // Analog Channel Selection Bits
	(0<<MUX1)|     // ADC4 (PC4 PIN27)
	(0<<MUX0);
	ADCSRA = (1<<ADEN)|    // ADC ENable
	(0<<ADSC)|     // ADC Start Conversion
	(0<<ADATE)|    // ADC Auto Trigger Enable
	(0<<ADIF)|     // ADC Interrupt Flag
	(0<<ADIE)|     // ADC Interrupt Enable
	(1<<ADPS2)|    // ADC Prescaler Select Bits
	(0<<ADPS1)|
	(1<<ADPS0);
}
// READ ADC PINS
void read_adc(void)
{
	unsigned char i = 4;
	adc_temp = 0;
	while (i--)
	{
		ADCSRA |= (1<<ADSC);
		while(ADCSRA & (1<<ADSC));
		adc_temp+= ADC;
		_delay_ms(50);
	}
	adc_temp = adc_temp / 4;  // Average a few samples
}

void print_config(void)
{
	uint8_t data;
	printf("Startup successful\n\n nRF24L01+ configured as:\n");
	printf("-------------------------------------------\n");
	nrf24_read(CONFIG,&data,1);
	printf("CONFIG		0x%02X\n",data);
	nrf24_read(EN_AA,&data,1);
	printf("EN_AA			0x%02X\n",data);
	nrf24_read(EN_RXADDR,&data,1);
	printf("EN_RXADDR		0x%02X\n",data);
	nrf24_read(SETUP_RETR,&data,1);
	printf("SETUP_RETR		0x%02X\n",data);
	nrf24_read(RF_CH,&data,1);
	printf("RF_CH			0x%02X\n",data);
	nrf24_read(RF_SETUP,&data,1);
	printf("RF_SETUP		0x%02X\n",data);
	nrf24_read(STATUS,&data,1);
	printf("STATUS		0x%02X\n",data);
	nrf24_read(FEATURE,&data,1);
	printf("FEATURE		0x%02X\n",data);
	printf("-------------------------------------------\n\n");
}

