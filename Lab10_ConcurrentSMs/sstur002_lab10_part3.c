/*    Author: sstur002
*  Partner(s) Name: Raajitha Rajkumar
*    Lab Section: 21
*    Assignment: Lab #10  Exercise #3
*    Exercise Description: [optional - include for your own benefit]
*
*    I acknowledge all content contained herein, excluding template or example
*    code, is my own original work.
*/

// Connect LEDs to PB0, PB1, PB2, and PB3.
// In one state machine (ThreeLEDsSM), output to a shared variable (threeLEDs)
//  the following behavior: set only bit 0 to 1, then only bit 1, then only bit 2 in sequence for 1 second each.
//  
// In a second state machine (BlinkingLEDSM), output to a shared variable (blinkingLED) 
// the following behavior: set bit 3 to 1 for 1 second, then 0 for 1 second.
// 
// In a third state machine (CombineLEDsSM), combine both shared variables and output to the PORTB.
// Note: only one SM is writing to outputs. Do this for the rest of the quarter.


#include <avr/io.h>

#include <avr/interrupt.h>
#include "timer.h"

//TL = threeLED
//works
enum TL_States{TL_init, TL_light} TL_state;
unsigned char TL_output = 0x01;
void TL_tick(){
	switch(TL_state){//transitions
		case TL_init:
			TL_state = TL_light;
			break;
		case TL_light:
			break;
	}
	switch(TL_state){//state actions
		case TL_init:
			break;
		case TL_light:
			if(TL_output == 0x01){
				TL_output = 0x02;
			}
			else if(TL_output == 0x02){
				TL_output = 0x04;
			}
			else if(TL_output == 0x04){
				TL_output = 0x01;
			}
			break;
	}
	
}

//BL = blinking led
enum BL_states{BL_init, BL_blink} BL_state;
unsigned char BL_output = 0x00;
void BL_tick(){
	switch(BL_state){//transitions
		case BL_init:
			BL_state = BL_blink;
			break;
		case BL_blink:
			break;
		default:
			BL_state = BL_blink;
			break;
	}
	switch(BL_state){//state actions
		case BL_init:
			break;
		case BL_blink:
			if(BL_output == 0x00){
				BL_output = 0x08;
			}
			else if(BL_output == 0x08){
				BL_output = 0x00;
			}
			break;	
	}
}


enum speaker_states{speaker_toggle} speaker_state;

unsigned char speaker_power = 0x00;

void speaker_tick(){
	switch(speaker_state){
		case speaker_toggle:
			break;
	}
	switch(speaker_state){
		case speaker_toggle:
			if(speaker_power == 0x00){
				speaker_power = 0x10;
			}
			else if(speaker_power == 0x10){
				speaker_power = 0x00;
			}
			break;
	}
}

//CL = combine LED (and all)
enum CL_states{CL_combine} CL_state;
unsigned char CL_output = 0x00;
void CL_tick(){
	switch(CL_state){
		case CL_combine:
			break;
		default:
			CL_state = CL_combine;
			break;
	}
	switch(CL_state){
		case CL_combine:
			CL_output = (TL_output | BL_output);
			break;
	}
}

// Modify the above example so the threeLEDs light for 300 ms,
// while blinkingLED’s LED still blinks 1 second on and 1 second off.

// To the previous exercise's implementation, connect your speaker's red wire to PB4 and black wire to ground.
//  Add a third task that toggles PB4 on for 2 ms and off for 2 ms as long as a switch on PA2 is in the on position.
//   Don’t use the PWM for this task.

int main(void)
{
	DDRA = 0x00; PORTA = 0xFF;
	DDRB = 0xFF; PORTB = 0x00;
	
	BL_state = BL_init;
	TL_state = TL_init;
	CL_state = CL_combine;

	
	const unsigned long time_period = 1; //1ms
	unsigned long TL_elapsedTime = 300; //3ms
	unsigned long BL_elapsedTime = 1000; //1s
	unsigned long speaker_elapsedTime = 2; //2ms
	//unsigned long CL_elapsedTime = 1000;
	
	TimerOn();
	TimerSet(time_period);
	
	
    /* Replace with your application code */
    while (1) 
    {
		unsigned char on_switch = (~PINA & 0x01);
		if(TL_elapsedTime >= 300){
			TL_tick();
			TL_elapsedTime = 0;
		}
		if(BL_elapsedTime >= 1000){
			BL_tick();
			BL_elapsedTime = 0;
		}
		if(on_switch){
			speaker_state = speaker_toggle;
			if(speaker_elapsedTime >= 2){
				speaker_tick();
				speaker_elapsedTime = 0;
			}
		}
		else if(!on_switch){
			speaker_power = 0x00;	
		}
			CL_tick();
			PORTB = (CL_output) | (speaker_power);
			//CL_elapsedTime = 0;
// 		BL_tick();
// 		CL_tick();
		while(!TimerFlag);
		TimerFlag = 0;
		
		TL_elapsedTime += time_period;
		BL_elapsedTime += time_period;
		speaker_elapsedTime += time_period;
		//CL_elapsedTime += time_period;
		
    }
}

