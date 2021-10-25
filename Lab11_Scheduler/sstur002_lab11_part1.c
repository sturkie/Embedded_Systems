/*    Author: sstur002
*  Partner(s) Name: Raajitha Rajkumar
*    Lab Section: 21
*    Assignment: Lab #11  Exercise #1
*    Exercise Description: [optional - include for your own benefit]
*
*    I acknowledge all content contained herein, excluding template or example
*    code, is my own original work.
*/


#include <avr/io.h>
#include "timer.h"

	
//SHARED VARIABLES
unsigned char led0_output = 0x00;
unsigned char led1_output = 0x00;
unsigned char pause = 0;
//DONE

//when button is pressed, share variable "pause" is toggled
enum pauseButtonSM_States{pauseButton_wait, pauseButton_press, pauseButton_release};
int pauseButtonSMTick(int state){
	unsigned char press = ~PINA & 0x01;
	switch(state){
		case pauseButton_wait:
			state = press == 0x01? pauseButton_press: pauseButton_wait;
			break;
		case pauseButton_press:
			state = pauseButton_release;
			break;
		case pauseButton_release:
			state = press == 0x00? pauseButton_wait: pauseButton_press;
			break;
		default:
			state = pauseButton_wait;
			break;	
	}
	switch(state){
		case pauseButton_wait:
			break;
		case pauseButton_press:
			pause = (pause == 0) ? 1 : 0;
			break;
		case pauseButton_release:
			break;
	}
	return state;
};

//if paused, do not toggle LED connected to pb0
//if unpaused, toggle led connected to pb0
enum toggleLED0_States {toggleLED0_wait, toggleLED0_blink};
int toggleLED0SMTick(int state){
	switch(state){
		case toggleLED0_wait: 
			state = !pause? toggleLED0_blink: toggleLED0_wait;
			break;
		case toggleLED0_blink:
			state = pause ? toggleLED0_wait: toggleLED0_blink;
			break;
		default:
			state = toggleLED0_wait;
			break;
	}
	switch(state){
		case toggleLED0_wait:
			break;
		case toggleLED0_blink:
			led0_output = (led0_output == 0x00) ? 0x01: 0x00;
			break;
	}
	return state;
};

//if paused, do not tiggle pb1
//if unpaused, toggle pb1
enum toggleLED1_States{toggleLED1_wait, toggleLED1_blink};
int toggleLED1SMTick(int state){
	switch(state){
		case toggleLED1_wait:
			state = !pause ? toggleLED1_blink: toggleLED1_wait;
			break;
		case toggleLED1_blink:
			state = pause? toggleLED1_wait: toggleLED1_blink;
			break;
		default:
			state = toggleLED1_wait;
			break;
	}
	switch(state){
		case toggleLED1_wait:
			break;
		case toggleLED1_blink:
			led1_output = (led1_output == 0x00) ? 0x01: 0x00;
			break;
	}
	return state;
};


//combine blinking LED outputs from toggleLED0 and toggleLED1 SM, and output on PORTB
enum display_States{display_display };
int displaySMTick(int state){
	unsigned char output;
	switch(state){
		case display_display:
			state = display_display;
			break;
		default:
			state = display_display;
			break;
	}
	switch(state){
		case display_display:
			output = led0_output | led1_output << 1;
	}
	PORTB = output;
	return state;
};

unsigned char GetBit(unsigned char x, unsigned char k){
	return((x & (0x01 << k)) != 0);
}

unsigned char GetKeypadKey(){
	PORTC = 0xEF;
	asm("nop"); //adding a delay
	if(GetBit(PINC,0)==0){return('1');}
	if(GetBit(PINC,1)==0){return('4');}
	if(GetBit(PINC,2)==0){return('7');}
	if(GetBit(PINC,3)==0){return('*');}
		
	//colm 2
	PORTC = 0x0F;
	asm("nop");
	if(GetBit(PINC,0)==0){return('2');}
	
	//col3
	PORTC = 0xBF;
	asm("nop");
	
	//col4
	
	
	return('\0'); //default
}

//task scheduler data structure
//struct for Tasks represent a running process in our simple rt os
typedef struct _task{
	signed char state;
	unsigned long int period;
	unsigned long int elapsedTime;
	int(*TickFct)(int);
	} task;

int main(void)
{
	unsigned char x;
	DDRA = 0x00; PORTA = 0xFF;
	DDRB = 0xFF; PORTB = 0x00;
	DDRC = 0xF0; PORTC = 0x0F; 
	
	static task task1, task2, task3, task4;
	task *tasks[] = {&task1, &task2, &task3, &task4};
	const unsigned short numTasks = sizeof(tasks)/sizeof(task*);
	
	
	//TASK 1
	task1.state = -1;
	task1.period = 50;
	task1.elapsedTime = task1.period;
	task1.TickFct = &pauseButtonSMTick;
	
	//TASK 2
	task2.state = -1;
	task2.period - 500;
	task2.elapsedTime = task2.period;
	task2.TickFct = &toggleLED0SMTick;
	
	//TASK 3
	task3.state = -1;
	task3.period = 1000;
	task3.elapsedTime = task3.period;
	task3.TickFct = &toggleLED1SMTick;
	
	//TASK 4
	task4.state = -1;
	task4.period = 10;
	task4.elapsedTime = task4.period;
	task4.TickFct = &displaySMTick;
	
	
	TimerSet(10);
	TimerOn();	
	
    unsigned short i;
    while (1) 
    {
		//new stuff
		for( i = 0; i < numTasks; i++){
			if(tasks[i]->elapsedTime == tasks[i]->period){
				tasks[i]->state = tasks[i]->TickFct(tasks[i]->state);
			}
		}
		
		
		//old
		x = GetKeypadKey();
		switch(x){
			case '\0':
				PORTB = 0x1F; break;
			case '1':
				PORTB = 0x01; break;
			case '2':
				PORTB = 0x02; break;
			case '4':	
				PORTB = 0x04; break;
			case '7':
				PORTB = 0x07; break;
			case '*':
				PORTB = 0x0E; break;
			default:
				PORTB = 0x1B; break; //middle LED off
		}
    }
}

