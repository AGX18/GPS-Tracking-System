#include "lcd.h"

/*
    RS =PB0
    RW =PB1
		EN =PB4
		
		D0 =PD0
		D1 =PD1
		D2 =PD2
		D3 =PD3
		D4 =PE1
		D5 =PE2
		D6 =PE3
		D7 =PE4
*/



void lcd_init(){
	lcd_command(0x38);   //This command sets the LCD to use an 8-bit data bus and enables 2 lines with 5x7 matrix
	lcd_command(0x06);   //increments the cursor position after writing to the display (shift cursor to right)
  lcd_command(0x0C);   //display on, cursor off
  lcd_command(0x01);   //clear display screen
  lcd_command(0x80);   //sets the cursor to the beginning of the first line 
}

void delay (long d){
	while(d--);
}

void print_data(unsigned char data){
	//bit0 = D0 = PD0
	if( GET_BIT(data,0)==1 )  SET_BIT(GPIO_PORTD_DATA_R,0); 
	else                      CLR_BIT(GPIO_PORTD_DATA_R,0); 
	
	//bit1 = D1 = PD1
	if( GET_BIT(data,1)==1 )  SET_BIT(GPIO_PORTD_DATA_R,1); 
	else                      CLR_BIT(GPIO_PORTD_DATA_R,1); 
	
	//bit2 = D2 = PD2
	if( GET_BIT(data,2)==1 )  SET_BIT(GPIO_PORTD_DATA_R,2); 
	else                      CLR_BIT(GPIO_PORTD_DATA_R,2); 
	
	//bit3 = D3 = PD3
	if( GET_BIT(data,3)==1 )  SET_BIT(GPIO_PORTD_DATA_R,3); 
	else                      CLR_BIT(GPIO_PORTD_DATA_R,3); 
	
	//bit4 = D4 = PE1
	if( GET_BIT(data,4)==1 )  SET_BIT(GPIO_PORTE_DATA_R,1); 
	else                      CLR_BIT(GPIO_PORTE_DATA_R,1); 
	
	//bit5 = D5 = PE2
	if( GET_BIT(data,5)==1 )  SET_BIT(GPIO_PORTE_DATA_R,2); 
	else                      CLR_BIT(GPIO_PORTE_DATA_R,2);
	
	//bit6 = D6 = PE3
	if( GET_BIT(data,6)==1 )  SET_BIT(GPIO_PORTE_DATA_R,3); 
	else                      CLR_BIT(GPIO_PORTE_DATA_R,3);
	
	//bit7 = D7 = PE4
	if( GET_BIT(data,7)==1 )  SET_BIT(GPIO_PORTE_DATA_R,4); 
	else                      CLR_BIT(GPIO_PORTE_DATA_R,4);
	
}

void lcd_data(unsigned char data){
	print_data(data);           //pass 8-bit data to the data lines of the lcd
	CLR_BIT(GPIO_PORTB_DATA_R,1);   //clear RW pin for write operation
  SET_BIT(GPIO_PORTB_DATA_R,0);   //set RS pin for writing to the data register
  SET_BIT(GPIO_PORTB_DATA_R,4);	  //set EN pin to enable the lcd
	delay(10000);
	CLR_BIT(GPIO_PORTB_DATA_R,4);   //turn off EN
}


void lcd_command(unsigned char cmd){
	print_data(cmd);           //pass 8-bit data to the data lines of the lcd
	CLR_BIT(GPIO_PORTB_DATA_R,1);   //clear RW pin for write operation
  CLR_BIT(GPIO_PORTB_DATA_R,0);   //clear RS pin for writing to the instruction register
  SET_BIT(GPIO_PORTB_DATA_R,4);	  //set EN pin to enable the lcd
	delay(10000);
	CLR_BIT(GPIO_PORTB_DATA_R,4);   //turn off EN
}

void lcd_string(char *str ){
	while(*str !='\0'){         //writing each character of the string on lcd
		lcd_data(*str);
		str++;
	}
		
}

void floatToString(float number, char *str, int size, int precision){
    snprintf(str, size, "%.*f", precision,number);
}