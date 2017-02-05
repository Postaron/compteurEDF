/*
 * uart.c
 *
 *  Created on: 5 févr. 2017
 *      Author: postaron
 */
#include "uart.h"

void uart_init(void) {
	// set baudrate to 1200bit/second
	//The 0 is for the timer0
	UBRR0 |= BAUDRATE;
	UCSR0C = 0b00100100; /*asynchronous mode enable, parity even, 7-bit data, 1 stop bit */
	UCSR0B |= (1 << RXEN0); // Enable RX
}

//not finished yet : reboot µC (watchdog ?)
void uart_checkError(void) {
	switch (~(0xE3 & UCSR0A)) { // 0xE3 = bits other than FE0 DOR0 and UPE0
	case (1 << FE0):
		break;
	case (1 << DOR0):
		break;
	case (1 << UPE0):
		break;
	case 0:
		//no errors
		break;
	default: //multiple errors
		break;
	}
}
char uart_getChar() {
	while ((UCSR0A & (1 << RXC0)) == 0)
		//do nothing while receive not complete
		;
	return UDR0;
}
void decode(char data) {

}
