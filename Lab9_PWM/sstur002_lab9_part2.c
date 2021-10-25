/*    Author: sstur002
*  Partner(s) Name: Raajitha Rajkumar
*    Lab Section: 21
*    Assignment: Lab #9  Exercise #2
*    Exercise Description: [optional - include for your own benefit]
*
*    I acknowledge all content contained herein, excluding template or example
*    code, is my own original work.
*/

#include <avr/io.h>
#include "pwm.h"
#include "timer.h"

unsigned char power = 0x00;

unsigned char i = 0x00; //set to frequency[0]
unsigned short frequency[9] = {0, 261.63, 293.66, 329.63, 349.23, 392.00, 440.00, 493.88, 523.25, };


enum States{init, on_press, on_released, up_press, up_released, down_press, down_released} state;

void Tick(){
	unsigned char buttonPower = (~PINA & 0x01);
	unsigned char buttonUp = (~PINA & 0x02);
	unsigned char buttonDown = (~PINA & 0x04);
	switch(state){//transations
		case init:
			if(buttonPower){
				state = on_press;
			}
			if(buttonUp){
				state = up_press;
			}
			if(buttonDown){
				state = down_press;
			}
			break;
		case on_press:
			if(!buttonPower){
				state = on_released;
			}
			break;
		case up_press:
			if(!buttonUp){
				state = up_released;
			}
			break;
		case down_press:
			if(!buttonDown){
				state = down_released;
			}
			break;
		case on_released:
			state = init;
			break;
		case up_released:
			state = init;
			break;
		case down_released:
			state = init;
			break;
		default:
			state = init;
			break;
	}
	switch(state){//state actions
		case init:
			break;
		case up_press:
		break;
		case down_press:
		break;
		case on_press:
		break;
		case on_released:
			if(power == 0x00){
				power = 0x01;
				i = 1; //to C
			}
			else if(power == 0x01){
				power = 0x00;
				i = 0; //to off
			}
			break;
		case up_released:
			if(power && i < 0x08){
				i = i + 0x01;
			}
			break;
		case down_released:
			if(power && i > 0x01){
				i = i - 0x01;
			}
			break;

	}
}

int main(void)
{
	DDRA = 0x00; PORTA = 0xFF;
	DDRB = 0x40; PORTB = 0x00;
	
	PWM_on();
	//TimerOn();
	//TimerSet(10);
	
	state = init;
	//scaling_state = scaling_init;
    /* Replace with your application code */
    while (1) 
    {
		//while(!TimerFlag){}
		//TimerFlag = 0;
		Tick();
		set_PWM(frequency[i]);
		//scaling_tick();
    }
	return 0;
}

