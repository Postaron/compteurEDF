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
unsigned char flag;

void uart_init(void);
unsigned char uart_flagCheck(void);

ISR(USART_RX_vect) { // interruption when start bit set to 0 (receive begin)
	while(!(UCSR0A & (1 << RXC0))); //wait until RXC0 buffer is full
	data = UDR0; // get the data
}

int main(void) {
	uart_init();

	for (;;) {
		if(data != 0){ //if data is not empty
			flag = uart_flagCheck(); // flag to know if there transmission problem
			switch (flag){
			case 1 : // Frame error
				break;
			case 2 : // Parity error
				break;
			case 3 : // Data Overrun (not possible but you know, info is like magic sometimes)
				break;
			default :
				break;
			}
		}
	}

	return 0;
}

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
