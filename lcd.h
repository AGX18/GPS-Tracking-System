#ifndef _lcd_
#define _lcd_


#include "GPIO.h"
#include <stdio.h>

//Function to initialize lcd
void lcd_init();

//Function to pass data to the datalines of lcd
void print_data(unsigned char data);

//Function to write a character on lcd
void lcd_data(unsigned char data);

//Function to pass instruction to the lcd
void lcd_command(unsigned char cmd);

//Function to write a string on lcd
void lcd_string(char *str );

//delay function
void delay (long d);

//function converts float to string to print it on lcd
void floatToString(float number, char *str, int size, int precision);

#endif
