/*    Author: sstur002
*  Partner(s) Name: Raajitha Rajkumar
*    Lab Section: 21
*    Assignment: Lab #7  Exercise #1
*    Exercise Description: [optional - include for your own benefit]
*
*    I acknowledge all content contained herein, excluding template or example
*    code, is my own original work.
*/


#include <avr/io.h>
#include <io.h>
#include <io.c>
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

enum States{init, dec_on, dec_off, inc_on, inc_off, zero_on, zero_off, wait} state;

unsigned char buttonInc = 0x00;
unsigned char buttonDec = 0x00;
unsigned char buttonBoth = 0x00;
unsigned char output = 0x00;



void Tick(){
	buttonInc = ~PINA & 0x01;
	buttonDec = ~PINA & 0x02;
	buttonBoth = ~PINA & 0x03;
	switch(state){ //transitions
		case init:
		state = wait;
		break;
		case wait:
		if(buttonBoth == 0x03){
			state = zero_on;
		}
		else if(buttonInc){
			if(!buttonDec){
				state = inc_on;
			}
			else if(buttonDec){
				state = zero_on;
			}
		}
		else if(buttonDec){
			if(!buttonInc){
				state = dec_on;
			}
			else if(buttonInc){
				state = zero_on;
			}
		}
		break;
		case dec_on:
		if(buttonInc){
			state = zero_on;
		}
		else{
			state = dec_off;
		}
		break;
		case inc_on:
		if(buttonDec){
			state = zero_on;
		}
		else{
			state = inc_off;
		}
		break;
		case inc_off:
		break;
		case dec_off:
		break;
		case zero_off:
		break;
		case zero_on:
		if(buttonBoth == 0x00){
			state = zero_off;
		}
		break;
		default:
		state = init;
		break;
	}
	switch(state){
		case init:
		break;
		case wait:
		break;
		case dec_on:
		break;
		case zero_on:
		break;
		case dec_off:
		if(output > 0x00){
			output -= 0x01;
		}
		state = wait;
		break;
		case inc_on:
		break;
		case inc_off:
		if(output < 0x09){
			output += 0x01;
		}
		state = wait;
		break;
		case zero_off:
		output = 0x00;
		state = wait;
		break;
	}
	
}

int main(void)
{
	DDRA = 0x00; PORTA = 0xFF; //pulluppulluppullpup
	DDRB = 0xFF; PORTB = 0x00;
	DDRC = 0xFF; PORTC = 0x00; //LCD data lines
	DDRD = 0xFF; PORTD = 0x00; //LCD control lines
	
	//initializes LCD display
	LCD_init();
	//LCD_ClearScreen();
	//LCD_DisplayString(1,"420! Blaze it");
	//LCD_DisplayString(1,"Hello World!");
    /* Replace with your application code */
	
	state = init;
	
	TimerSet(1000);
	TimerOn();
	
	//LCD_ClearScreen();
	//LCD_Cursor(1);
	//LCD_WriteData(6 + '0');
	
    while (1) 
    {
		Tick();
		LCD_Cursor(1);
		LCD_WriteData(output + '0');
		
		while(!TimerFlag){};
			TimerFlag = 0;
		//continue;
    }
}
