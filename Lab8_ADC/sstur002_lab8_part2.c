/*    Author: sstur002
*  Partner(s) Name: Raajitha Rajkumar
*    Lab Section: 21
*    Assignment: Lab #8  Exercise #2
*    Exercise Description: [optional - include for your own benefit]
*
*    I acknowledge all content contained herein, excluding template or example
*    code, is my own original work.
*/


#include <avr/io.h>

void ADC_init(){
	ADCSRA |= (1 << ADEN) | (1 << ADSC) | (1 << ADATE);
	
}

int main(void)
{
	
	DDRA = 0x00; PORTA = 0xFF;
	DDRB = 0xFF; PORTB = 0x00;
	DDRD = 0xFF; PORTD = 0x00;
	
	ADC_init();
	
    /* Replace with your application code */
    while (1) 
    {
		unsigned short x = ADC;
		
		unsigned char outputB = (char)x;
		unsigned char outputD = (char)(x >> 8);
		
		PORTB = outputB;
		PORTD = outputD;
    }
	
	return 0;
}

