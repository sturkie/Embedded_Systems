/*    Author: sstur002
*  Partner(s) Name: Raajitha Rajkumar
*    Lab Section: 21
*    Assignment: Lab #9  Exercise #1
*    Exercise Description: [optional - include for your own benefit]
*
*    I acknowledge all content contained herein, excluding template or example
*    code, is my own original work.
*/


#include <avr/io.h>

void set_PWM(double frequency){
	static double current_frequency;
	if(frequency != current_frequency){
		if(!frequency){ TCCR3B &= 0x08; }
		else{ TCCR3B |= 0x03; }
		
		if(frequency < 0.954){ OCR3A = 0xFFFF; }
		else if(frequency > 31250){ OCR3A = 0x0000; }
		else { OCR3A = (short)(8000000 / (128 * frequency)) - 1;}
		TCNT3 = 0;
		current_frequency = frequency;
	}
}

void PWM_on(){
	TCCR3A = (1 << COM3A0);
	TCCR3B = (1 << WGM32) | (1 << CS31) | (1 << CS30);
	set_PWM(0);
}

void PWM_off(){
	TCCR3A = 0x00;
	TCCR3B = 0x00;
}

int main(void)
{
	DDRA = 0x00; PORTA = 0xFF;
	DDRB = 0x40; PORTB = 0x00;
	

	
	PWM_on();	

    while (1) 
    {
		unsigned char buttonOne = (~PINA & 0x01);
		unsigned char buttonTwo = (~PINA & 0x02);
		unsigned char buttonThree = (~PINA & 0x04);
		
		//C = 261.63
		//D = 293.66
		//E = 329.63
		
		if(buttonOne && !buttonTwo && !buttonThree){
			set_PWM(261.63);
		}
		else if(!buttonOne && buttonTwo && !buttonThree){
			set_PWM(293.66);
		}
		else if(!buttonOne && !buttonTwo && buttonThree){
			set_PWM(329.63);
		}
		else
		{
			set_PWM(0);
		}
		
    }
	return 0;
}

