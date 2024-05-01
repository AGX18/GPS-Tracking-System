#ifndef _LEDandSW_
#define _LEDandSW_

#include "bits.h"
#include "tm4c123gh6pm.h"

unsigned char readSW2(); // read if sw2 is pressed or not
void Leds_output(unsigned char data);  

#endif
