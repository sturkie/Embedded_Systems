/*    Author: sstur002
*  Partner(s) Name: Raajitha Rajkumar
*    Lab Section: 21
*    Assignment: Lab #6  Exercise #1
*    Exercise Description: [optional - include for your own benefit]
*
*    I acknowledge all content contained herein, excluding template or example
*    code, is my own original work.
*/

#include <avr/io.h>
#include <avr/interrupt.h>

// TimerISR() sets this to 1. C programmer should clear to 0.
volatile unsigned char TimerFlag = 0;

//Internal variables for mapping AVR's ISR to our cleaner TimerISR model.
unsigned long _avr_timer_M = 1;
unsigned long _avr_timer_cntcurr = 0;

void TimerOn(){
	TCCR1B = 0x0B;
	OCR1A = 125;
	TIMSK1 = 0x02;
	TCNT1 = 0;
	
	_avr_timer_cntcurr = _avr_timer_M;
	SREG |= 0x80;
	
}

void TimerOff(){
	TCCR1B = 0x00;
}

void TimerISR(){
	TimerFlag = 1;
}

ISR(TIMER1_COMPA_vect){
	
	_avr_timer_cntcurr--;
	if(_avr_timer_cntcurr == 0){
		TimerISR();
		_avr_timer_cntcurr = _avr_timer_M;
	}
}

void TimerSet(unsigned long M){
	_avr_timer_M = M;
	_avr_timer_cntcurr = _avr_timer_M;
}

enum States{init, light} state;

unsigned char lightCount = 0x01;

void Tick(){
	switch(state){//transitions
		case init:
			state = light;
			break;
		case light:
			break;
		default:
			state = init;
			break;
	}
	switch(state){//state
		case init:
			break;
		case light:
			if(lightCount == 0x01){
				lightCount = 0x02;
			}
			else if(lightCount == 0x02){
				lightCount = 0x04;
			}
			else if(lightCount == 0x04){
				lightCount = 0x01;
			}
			break;
			
			
	}
}

int main(void)
{
	DDRB = 0xFF; PORTB = 0x00;
	
	state = init;
	
	TimerSet(1000);
	TimerOn();
	
    /* Replace with your application code */
    while (1) 
    {
		Tick();
		PORTB = lightCount;
		while(!TimerFlag);
		TimerFlag = 0;
    }
}

