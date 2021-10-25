/*    Author: sstur002
*  Partner(s) Name: Raajitha Rajkumar
*    Lab Section: 21
*    Assignment: Lab #7  Exercise #2
*    Exercise Description: [optional - include for your own benefit]
*
*    I acknowledge all content contained herein, excluding template or example
*    code, is my own original work.
*/


#include <avr/io.h>
#include <avr/interrupt.h>
#include "io.c"
#include "io.h"

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

enum States{init, light, light_press, stop_press, stop_release, wait} state;

unsigned char lightCount = 0x01;
unsigned char button = 0x00;
unsigned char score = 0x00;
unsigned char win = 0x00;

void Tick(){
	button = (~PINA & 0x01);
	switch(state){//transitions
		case init:
		state = light;
		break;
		case light:
		if(button){
			state = stop_press;
		}
		break;
		case light_press:
		if(!button){
			state = light;
		}
		break;
		case stop_press:
		if(!button){
			state = stop_release;
		}
		break;
		case stop_release:
		if(button){
			state = light_press;
		}
		else{
			state = wait;
		}
		break;
		case wait:
			if(button){
				state = light_press;
			}
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
		case light_press:
		break;
		case stop_press:
		break;
		case stop_release:
		if(lightCount == 0x02){
			if(score < 0x09){
				if((score + 1) == 0x09){
					win = 0x01;
				}
				else{
					score++;
				}
			}
		}
		else if(lightCount == 0x01 || lightCount == 0x04){
			if(score > 0x00){
				score--;
			}
		}
		break;
		case wait:
			break;
		
		
	}
	PORTB = lightCount;
}

int main(void)
{
	DDRA = 0x00; PORTA = 0xFF; //pulluppulluppullpup
	DDRB = 0xFF; PORTB = 0x00;
	DDRC = 0xFF; PORTC = 0x00; //LCD data lines
	DDRD = 0xFF; PORTD = 0x00; //LCD control lines
	
	//initializes LCD display
	LCD_init();
	LCD_ClearScreen();
	//LCD_DisplayString(1,"420! Blaze it");
	//LCD_DisplayString(1,"Hello World!");
	/* Replace with your application code */
	
	state = init;
	
	TimerSet(300);
	TimerOn();
	
	//LCD_ClearScreen();
	//LCD_Cursor(1);
	//LCD_WriteData(6 + '0');
	
	while (!win)
	{
		Tick();
		//PORTB = lightCount;
		LCD_ClearScreen();
		LCD_Cursor(1);
		LCD_WriteData(score + '0');
		
		while(!TimerFlag){};
		TimerFlag = 0;
		//continue;
	}
	
	LCD_ClearScreen();
	LCD_DisplayString(1, "winner winner chicken dinner");
}


