/*
 * uart.h
 *
 *  Created on: 5 févr. 2017
 *      Author: postaron
 */

#ifndef UART_H_
#define UART_H_
#include <avr/io.h>

#ifndef BAUD
#define BAUD 1200
#endif

#ifndef BAUDRATE
#define BAUDRATE (((F_CPU / (BAUD * 16UL))) - 1)
#endif

void uart_init(void);
void uart_checkError(void);
char uart_getChar(void);
void decode(char data);



#endif /* UART_H_ */
