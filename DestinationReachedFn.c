#include "Leds&switches.h"
#include "GPIO.h"
#include "stdbool.h"
#include "UART .h"
#include "GPS.h"
#include "string.h"
#include "lcd.h"
#include "Systick.h"
#include <stdio.h>
#define RED_LED_ON 0x02
#define GREEN_LED_ON 0x08

unsigned char j=0;
unsigned char Switch_Pressed;
float startLat;				//saving start point latitude on GPS
float startLong;			//saving start point latitude on GPS
char str[16];  				// Buffer to hold the resulting string
int precision = 4; 		// Number of decimal places
bool destination_reached=false; // flag that is set when destination is reached
float previous_lat;		//storing previous lat. for distance calculation
float previous_long;	//storing previous long. for distance calculation
 
//a function that is call when destination is read manually (without interrupts)
void destinationReached (){
	Switch_Pressed=readSW2();
	if(!Switch_Pressed) destination_reached=true;
	else   destination_reached=false;
	
}
 //turns led on once destination is reached
void ledOnDestination(){
	if(destination_reached) {
		Leds_output(RED_LED_ON);
	}
}
//handler for interrupt when switch 0 is pressed
void GPIOF_Handler(){
	if(GPIO_PORTF_MIS_R&0X1){
   	destination_reached=true;
	}
	GPIO_PORTF_ICR_R|=0X1;
}

int main(){
	float distance=0;						//a variable that stores total distance covered
	destination_reached=false;	//initialising bool for the destination reached flag
	//ports initialisation in main
	GPIO_PORTF_SW2_INIT();
	GPIO_PORTF_LED12_INIT();
	UART0_init();
	UART2_init();
	GPIO_PORTB_INIT();
	GPIO_PORTD_INIT();
	GPIO_PORTE_INIT();
	//initialisation of ISR , systick timer and lcd
	GPIO_PORTF_INTERRUPT();
	SYSTick_Init();
	lcd_init();
	//reading first value from GPS to set start lat. and long.
	GPS_read();
	Leds_output(GREEN_LED_ON); //LED turned on to indicate GPS has read data successfully
	startLat=currentlat;
	startLong=currentlong;

	while(1){
		//setting previous values of lat. and long. for distance calculations
		previous_lat=currentlat;
		previous_long=currentlong;
		//GPS update time is 0.1 sec
		DELAY(100);
		Leds_output(0); 	//turn Leds off to detect when GPS reads successfully
		GPS_read();
		Leds_output(GREEN_LED_ON);  
		//calling distance function to add calculated distance to distance covered previously
		distance+=(getDistance(currentlong,currentlat,previous_long,previous_lat));
		//checks the bool of destination reached that is set by the ISR  to break the loop 
		//and stop reading from GPS
  	if(destination_reached) break; 
	}
	
	Leds_output(0);
	//converting distance (float value) to string to be printed on lcd
  floatToString(distance*1000, str, sizeof(str), precision);
	//red led turned on at destination reached
	Leds_output(RED_LED_ON); 
	//printing total distance on lcd
	lcd_string("Total distance = ");
	lcd_command(0xc0);
	lcd_string(str);

}
