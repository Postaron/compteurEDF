#include <avr/io.h>
#include <avr/interrupt.h>

#define F_CPU 16000000UL
#define BAUD 1200
#define BAUDRATE (((F_CPU / (BAUD * 16UL))) - 1)
#define START 0x01 //not the real one
#define END 0x02 //same reason

void uart_init(void);
void uart_checkError(void);
char uart_getChar(void);
void decode(char data);

int main(void) {
	uart_init();

	for (;;) {
		char data = uart_getChar();
		if (data != 0) { //if data is not empty
			uart_checkError(); // reboot µC
			decode(data);
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
}

//not finished yet : reboot µC (watchdog ?)
void uart_flagCheck(void) {
	switch (UCSR0A) {
	case (1 << FE0):
		break;
	case (1 << DOR0):
		break;
	case (1 << UPE0):
		break;
	default:
		break;
	}
}

void decode(char data) {

}
