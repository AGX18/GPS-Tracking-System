#include "Systick.h"

void SYSTick_Init(void){
NVIC_ST_CTRL_R = 0;
NVIC_ST_RELOAD_R = 0x00FFFFFF;
NVIC_ST_CURRENT_R = 0;
NVIC_ST_CTRL_R = 0x05;
}

void systick_Wait1ms(void){
NVIC_ST_RELOAD_R = 80000-1;
NVIC_ST_CURRENT_R = 0;
while((NVIC_ST_CTRL_R & 0x00010000) == 0){};
}

void DELAY(int time){
int i;
 for(i = 0; i <time; i++){
   systick_Wait1ms();
}
}
