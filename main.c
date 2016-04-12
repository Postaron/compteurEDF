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
	//The 0 is for the timer0
	UBRR0H |= (BAUDRATE >> 8);
	UBRR0L |= BAUDRATE;
	UCSR0C = 0b00100100; /*asynchronous mode enable, parity even, 7-bit data
	 1 stop bit */
	UCSR0B |= (1 << RXEN0); // Enable RX
	UCSR0B |= (1 << RXCIE0); // Enable interruption when RX buffer is full
	sei();
	// Enable global interruption
}

ISR(USART_RX_vect) {

}

int main(void) {
	uart_init();

	for (;;) {
	}

	return 0;
}
