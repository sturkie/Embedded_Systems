/*    Author: sstur002
*  Partner(s) Name: Raajitha Rajkumar
*    Lab Section: 21
*    Assignment: Lab #8  Exercise #1
*    Exercise Description: [optional - include for your own benefit]
*
*    I acknowledge all content contained herein, excluding template or example
*    code, is my own original work.
*/


#include <avr/io.h>

//variable fun time

//ADC initializaiton function
void ADC_init(){
	ADCSRA |= (1 << ADEN) | (1 << ADSC) | (1 << ADATE);
	
}


//WHAT
//unsigned short my_short = 0xABCD
//unsigned char my_char = (char)my_short;
//my_char = (char)(my_short >> 4);

int main(void)
{
	DDRA = 0x00; PORTA = 0xFF;
	DDRB = 0xFF; PORTB = 0x00;
	DDRD = 0xFF; PORTD = 0x00;
	
	ADC_init();
   
	
 
    while (1) 
    {
		unsigned short x = ADC;
	
		unsigned char outputB = (char)x;
		unsigned char outputD = (char)(x >> 8);
		
		//output = (char)(x >> 4);
		PORTB = outputB;
		PORTD = outputD;
    }
	return 0;
}

