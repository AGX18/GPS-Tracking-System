#include "Leds&switches.h"
#include "GPIO.h"
#include "stdbool.h"
#define RED_LED_ON 0x02
unsigned char Switch_Pressed;

bool destinationReached (){
	
	Switch_Pressed=readSW2();
	if(!Switch_Pressed) return true;
	else return false;
	
}

void ledOnDestination(){
	
if(destinationReached()) {
		Leds_output(RED_LED_ON);
	}
}
int main(){
	GPIO_PORTF_SW2_INIT();
	GPIO_PORTF_LED12_INIT();
while(1){
ledOnDestination();
}

}
