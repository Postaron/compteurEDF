/*
 * main.c
 *
 *  Created on: 1 avr. 2016
 *      Author: postaron
 */

#include <avr/io.h>
#include <avr/interrupt.h>
#define F_CPU 16000000UL
#define BAUD 1200
#define BAUDRATE (((F_CPU / (BAUD * 16UL))) - 1)

volatile char data;

void uart_init(void) {
	// set baudrate to 1200bit/second
	UBRRH |= (BAUDRATE >> 8);
	UBRRL |= BAUDRATE;
	UCSRC = 0b00100100; /*asynchronous mode enable, parité paire, 7-bit data
	 1 bit de stop */
	UCSRB |= (1 << RXEN); // autorisation de la réception de donnée
	UCSRB |= (1 << RXCIE); // Interruption pour réception des infos
	sei();
	// autorisation globale des interruptions
}

ISR(USART_RXC_vect) {
	while (!(UCSRA & (1 << RXC)))
		; //wait until data is completely received
	data = UDR; //puts the received data in the variable data
}

int main(void) {
	uart_init();

	for (;;) {
	}

	return 0;
}
