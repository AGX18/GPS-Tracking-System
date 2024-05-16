#include "GPIO.h"



void GPIO_PORTB_INIT(){
	SET_BIT(SYSCTL_RCGCGPIO_R,1);                  // port B clock enable
	while(GET_BIT(SYSCTL_PRGPIO_R,1)==0);          // delay
	SET(GPIO_PORTB_CR_R, 0x13);                    // allow changes to PB0 , PB1 , PB4
	CLR(GPIO_PORTB_AMSEL_R, 0x13);                 // disable analog function 
	CLR(GPIO_PORTB_PCTL_R,0x000F00FF);             // clear PCTL
	CLR(GPIO_PORTB_AFSEL_R, 0x13);                 // no alternate functions
	SET(GPIO_PORTB_DIR_R, 0x13);                   //PB0 , PB1 , PB4 output
	SET(GPIO_PORTB_DEN_R, 0x13);                   //enable digital pins PB0 , PB1 , PB4
	CLR(GPIO_PORTB_DATA_R, 0x13);                  //initialize pins to 0
}

void GPIO_PORTD_INIT(){
	SET_BIT(SYSCTL_RCGCGPIO_R,3);                  // port D clock enable
	while(GET_BIT(SYSCTL_PRGPIO_R,3)==0);          // delay
	SET(GPIO_PORTD_CR_R, 0x0F);                    // allow changes to PD0 , PD1 ,PD2, PD3
	CLR(GPIO_PORTD_AMSEL_R, 0x0F);                 // disable analog function 
	CLR(GPIO_PORTD_PCTL_R,0x0000FFFF);             // clear PCTL
	CLR(GPIO_PORTD_AFSEL_R, 0x0F);                 // no alternate functions
	SET(GPIO_PORTD_DIR_R, 0x0F);                   //PD0 , PD1 ,PD2, PD3 output
	SET(GPIO_PORTD_DEN_R, 0x0F);                   //enable digital pins PD0 , PD1 ,PD2, PD3
	CLR(GPIO_PORTD_DATA_R, 0x0F);                  //initialize pins to 0
}

void GPIO_PORTE_INIT(){
	SET_BIT(SYSCTL_RCGCGPIO_R,4);                  // port E clock enable
	while(GET_BIT(SYSCTL_PRGPIO_R,4)==0);          // delay
	SET(GPIO_PORTE_CR_R, 0x1E);                    // allow changes to PE1 , PE2 ,PE3, PE4
	CLR(GPIO_PORTE_AMSEL_R, 0x1E);                 // disable analog function 
	CLR(GPIO_PORTE_PCTL_R,0x000FFFF0);             // clear PCTL
	CLR(GPIO_PORTE_AFSEL_R, 0x1E);                 // no alternate functions
	SET(GPIO_PORTE_DIR_R, 0x1E);                   //PE1 , PE2 ,PE3, PE4 output
	SET(GPIO_PORTE_DEN_R, 0x1E);                   //enable digital pins PE1 , PE2 ,PE3, PE4
	CLR(GPIO_PORTE_DATA_R, 0x1E);                  //initialize pins to 0
}

void GPIO_PORTF_SW2_INIT(){
	SET(SYSCTL_RCGCGPIO_R,0x20);                   // port F clock enable
	while((SYSCTL_PRGPIO_R & 0x20)==0);            // delay   
	GPIO_PORTF_LOCK_R=GPIO_LOCK_KEY;               // Unlock GPIO Port F
	SET(GPIO_PORTF_CR_R,0x01 ) ;                   // allow changes to PF0
	CLR(GPIO_PORTF_AMSEL_R ,0x01 ) ;               // disable analog function
	CLR(GPIO_PORTF_AFSEL_R ,0x01 ) ;               // no alternate functions
	CLR(GPIO_PORTF_PCTL_R ,0x000f );               // clear PCTL
	CLR(GPIO_PORTF_DIR_R ,0x01 );                  //PF0 input 
	SET(GPIO_PORTF_DEN_R,0x01 );                   //enable digital pins PF0
	SET(GPIO_PORTF_PUR_R ,0x01);                   // enable pull-up on PF0
}
	
void GPIO_PORTF_LEDs_INIT(){
	SET(SYSCTL_RCGCGPIO_R,0x20);                   // port F clock enable
	while((SYSCTL_PRGPIO_R & 0x20)==0);            // delay
  GPIO_PORTF_LOCK_R=GPIO_LOCK_KEY;               // Unlock GPIO Port F	
	SET(GPIO_PORTF_CR_R,0x0E ) ;                   // allow changes to  PF12 ,PF2
	CLR(GPIO_PORTF_AMSEL_R ,0x0E ) ;               // disable analog function
	CLR(GPIO_PORTF_AFSEL_R ,0x0E ) ;               // no alternate functions
	CLR(GPIO_PORTF_PCTL_R ,0xfff0 );               // clear PCTL
	SET(GPIO_PORTF_DIR_R ,0x0E );                  // PF1&PF2 output   
	SET(GPIO_PORTF_DEN_R,0x0E );                   //enable digital pins PF12 ,PF2
	CLR(GPIO_PORTF_DATA_R ,0x0E);                  //initialize leds to be off 
}

void GPIO_PORTF_INTERRUPT(){
	GPIO_PORTF_IS_R = ~0X11;
	GPIO_PORTF_IBE_R=  ~0X11;
	GPIO_PORTF_IEV_R=0X11;
	GPIO_PORTF_IM_R=0X11;
	NVIC_PRI7_R|=0X20000;
	NVIC_EN0_R|=0X40000000;
	__enable_irq();
}







