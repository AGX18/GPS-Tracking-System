#include "Leds&switches.h"


unsigned char readSW2(){
	return (GPIO_PORTF_DATA_R &0x01);
}	
void Leds_output(unsigned char data){
CLR(GPIO_PORTF_DATA_R,0x06);
	
SET(GPIO_PORTF_DATA_R ,data);
}