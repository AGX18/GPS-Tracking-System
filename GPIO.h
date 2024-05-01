#ifndef _GPIO_
#define _GPIO_


#include "tm4c123gh6pm.h"
#include "bits.h"

// Function to initialize port B
void GPIO_PORTB_INIT();
// Function to initialize port D
void GPIO_PORTD_INIT();
// Function to initialize port E
void GPIO_PORTE_INIT();
// Function to initialize port F SW2
void GPIO_PORTF_SW2_INIT();
// Function to initialize port F LED12
void GPIO_PORTF_LED12_INIT();

#endif