#ifndef  _UART_
#define _UART_

#include "bits.h"

#include "tm4c123gh6pm.h"

// initialize UART0
void UART0_init();

// function to read data from fifo (UART 0)
char UART0_readchar();
// function to transmit data(UART 0)
void UART0_writechar(char data);

// initialize UART2
void UART2_init();
// function to read data from fifo (UART 2)
char UART2_readchar();
// function to transmit data(UART 2)
void UART2_writechar(char data);
// function to save every char recieved from GPS module in the array till '*'
void get_array(char*GPS);
//function sends string to the serial monitor (UART0)
void string_out(char *str);

#endif
