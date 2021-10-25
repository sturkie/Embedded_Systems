/*	Author: sstur002
 *	Lab Section:
 *	Assignment: Lab #4  Exercise #1
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

//#define A0 (PINA & 0x01)

enum States{LED_One, LED_Two} state;

//unsigned char input = (PINA & 0x01);
unsigned char button = 0x00;
//unsigned char output = 0x00;

void Tick(){
    button = PINA & 0x01;
    switch(state){ //transitions
        case LED_One:
            if(button){
                state = LED_Two;
            }
            else{
                state = LED_One;
            }
            break;
        case LED_Two:
            if(button){
                state = LED_One;
            }
            else
            {
                state = LED_Two;
            }
            break;
        default:
            state = LED_One;
            break;
    }
    switch(state){//state actions
        case LED_One:
            PORTB = 0x01;
            break;
        case LED_Two:
            PORTB = 0x02;
            break;
    }
    //PORTB = output;
}

int main(void) {
    /* Insert DDR and PORT initializations */
    DDRA = 0x00; PORTA = 0xFF; //input
    DDRB = 0xFF; PORTB = 0x00; //output

    //unsigned char input = (PINA & 0x01); //only looking at A0
    state = -1;
    /* Insert your solution below */
    while (1) {
        Tick();
        //PORTB = output;
    }
    return 1;
}
