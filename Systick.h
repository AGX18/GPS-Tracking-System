#ifndef _systick_
#define _systick_

#include "stdint.h"
#include "tm4c123gh6pm.h"


void SYSTick_Init(void);			//Systick initialisation
void systick_Wait1ms(void);		
void DELAY(int time);

#endif
