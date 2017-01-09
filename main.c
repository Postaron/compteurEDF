#include <avr/io.h>

#define F_CPU 16000000UL
#define BAUD 1200
#define BAUDRATE (((F_CPU / (BAUD * 16UL))) - 1)
#define START 0x0A //the real one
#define END 0x0D //same reason
#define SPACE 0x20 //a space between the tag, data and checksum


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
void uart_init(void);
void uart_checkError(void);
char uart_getChar(void);
void decode(char data);

int main(void) {
	uart_init();

	for (;;) {
		char data = uart_getChar();
		uart_checkError(); //reboot µC
		decode(data);
	}

	return 0;
}

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
