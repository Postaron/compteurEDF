#include <avr/io.h>
#include "uart.h"

#define F_CPU 16000000UL


/*
 * The protocol is like that :
 * A start
 * then a tag (4 to 8 character)
 * a space
 * one data (1 to 12 character)
 * a space
 * checksum
 * end
 */
int main(void) {
	uart_init();

	for (;;) {
		char data = uart_getChar();
		uart_checkError(); //reboot µC
		decode(data);
	}

	return 0;
}


