/*	Author: sstur002
 *  Partner(s) Name: Raaj
 *	Lab Section:
 *	Assignment: Lab #  Exercise #
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

unsigned char buttonOne = 0x00;
unsigned char buttonTwo = 0x00;
unsigned char bothPress = 0x00;
unsigned char output = 0x00;

enum States{Start, Init, Inc, Dec, Wait} state;
    
void Tick() { //transitions
    buttonOne = ~PINA & 0x01;
    buttonTwo = ~PINA & 0x02;
    bothPress = ~PINA;
        switch(state){
            case Start:
                state = Init;
                break;
            case Init:
                if(bothPress == 0x03){
                    state = Init;
                }
                else if(buttonTwo){
                    state = Dec;
                }
                else if(buttonOne)
                {
                    state = Inc;
                }
                break;
            case Inc:
                if(bothPress == 0x03){
                    
                    state = Init;
                }
                else if(buttonTwo){
                    state = Dec;
                }
                else if(buttonOne)
                {
                    state = Inc;
                }
                state = Wait;
                break;
            case Dec:
                if(bothPress == 0x03){
                    state = Init;
                }
                else if(buttonTwo){
                    state = Dec;
                }
                else if(buttonOne)
                {
                    state = Inc;
                }
                state = Wait;
                break;
            case Wait:
                if(bothPress == 0x03){
                    state = Init;
                }
                else if(buttonTwo){
                    state = Dec;
                }
                else if(buttonOne)
                {
                    state = Inc;
                }
                break;
        }
        switch(state){ //state
            case Start:
                break;
            case Init:
                output = 0x00;
                break;
            case Inc:
                if(output < 0x09){
                    output += 0x01;
                }
                break;
            case Dec:
                if(output > 0x00){
                    output -= 0x01;
                }
                break;
            case Wait:
                break;
        
        }
    PORTB = output;
}

int main(void){

    DDRA = 0x00; PORTA = 0xFF; //input
    DDRB = 0xFF; PORTB = 0x00; //B output?


    state = Start;

    
    while(1) {
        Tick();
    }


    return 0;
}
