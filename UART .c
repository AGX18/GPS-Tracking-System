#include "UART .h"
void UART0_init(){
	// activate UART0
	SET_BIT(SYSCTL_RCGCUART_R , 0);
	//while (GET_BIT(SYSCTL_PRUART_R,0)==0); //delay
	SET_BIT(SYSCTL_RCGCGPIO_R , 0);
	//while (GET_BIT(SYSCTL_PRGPIO_R,0)==0);//delay
	
	CLR_BIT(UART0_CTL_R,0);        //UART disable
	UART0_IBRD_R = 104;     	     // IBRD = INT( 16000000/(16*9600) ) = 104
	UART0_FBRD_R = 11;             // FBRD = INT( 0.16667*64 +0.5 ) = 11
	SET(UART0_LCRH_R,0x70);        // 8-bit Word Length , Enable FIFOs
	SET(UART0_CTL_R,0x301);         // enable UART , RX and TX
	SET(GPIO_PORTA_AFSEL_R,0x3);     // enable alternate function on PA0 and PA1
	CLR(GPIO_PORTA_PCTL_R,0x000000FF);  // UART on PA0 and PA1
	SET(GPIO_PORTA_PCTL_R,0x00000011);
	SET(GPIO_PORTA_DEN_R,0x3);         // enable digital I/O on PA0 and PA1
	CLR(GPIO_PORTA_AMSEL_R,0x3);      //disable analog function on PA0 and PA1
}

char UART0_readchar(){
	while((UART0_FR_R &UART_FR_RXFE )!=0);
	return (char)(GET_REG( UART0_DR_R)) ;} // returning first 8 bits

	void UART0_writechar(char data){
		while((UART0_FR_R & UART_FR_TXFF  )!=0);
		UART0_DR_R=data;
		
	}

void UART2_init(){
	// activate UART2
	SET_BIT(SYSCTL_RCGCUART_R , 2);
//	while (GET_BIT(SYSCTL_PRUART_R,2)==0); //delay
	
	SET_BIT(SYSCTL_RCGCGPIO_R , 3);// activate port D
	//while (GET_BIT(SYSCTL_PRGPIO_R,3)==0); //delay
	
	CLR_BIT(UART2_CTL_R,0);// UART disable
	UART2_IBRD_R = 104;      	// IBRD = INT( 16000000/(16*9600) ) = 104
	UART2_FBRD_R = 11;         // FBRD = INT( 0.16667*64 +0.5 ) = 11
	SET(UART2_LCRH_R,0x70);      // 8-bit Word Length , Enable FIFOs  
	SET(UART2_CTL_R,0x301);       // enable UART , RX and TX
	SET(GPIO_PORTD_AFSEL_R,0xC0);      // enable alternate function on PD6 and PD7
	CLR(GPIO_PORTD_PCTL_R,0xFF000000);  // UART on PD6 and PD7
	SET(GPIO_PORTD_PCTL_R,0x11000000);   
	SET(GPIO_PORTD_DEN_R,0xC0);        // enable digital I/O on PD6 and PD7
	CLR(GPIO_PORTD_AMSEL_R,0xC0);       // disable analog function on PD6 and PD7
}

char UART2_readchar(){
	while((UART2_FR_R &UART_FR_RXFE )!=0);
	
	return (char)(GET_REG( UART2_DR_R)) ;} // returning first 8 bits

	void UART2_writechar(char data){
		
		while((UART2_FR_R & UART_FR_TXFF  )!=0);
		
		UART2_DR_R=data;
		
	}
	
	
	void get_array(char*GPS){
		char recievedchar,counter=0;
		do{// to save every char recieved in the array
			
			recievedchar=UART2_readchar();
			
		if(recievedchar!=',')	GPS[counter++]=recievedchar;
		
			
		}	while(recievedchar!=',');//stop when reaching * in the string
		
		
	}
	
	
	
	
void string_out(char *str){
	while(*str !='\0'){
		UART0_writechar(*str);
		str++;
	}
}
	
