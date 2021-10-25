/*	Author: sstur002
 *  Partner(s) Name: Raajitha Rajkumar
 *	Lab Section:
 *	Assignment: Lab #4  Exercise #4
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

enum States{init, lock, button_pound, button_y, unlock} state;
unsigned char output = 0x00;

void Tick(){
    unsigned char pound = PINA & 0x04;
    unsigned char y = PINA & 0x02;
    unsigned char x = (PINA & 0x01);
    unsigned char inside = (PINA & 0x80);
    switch(state){ //transitions
        case init:
            state = lock;
            break;
        case lock:
            if(x || y || inside){
                state = lock;
            }
            else if(pound && !x && !y && !inside){
                state = button_pound;
            }
            break;
        case button_pound:
            if(y && !output){
                state = button_y;
            }
            else if(x || inside){
                state = lock;
            }
            else if(y && output){
                state = lock;
            }
            break;
        case button_y:
            if(x || inside){
                state = lock;
            }
            else{
                state = unlock;
            }
            break;
        case unlock:
            if(!inside){
                state = unlock;
            }
            else if(inside){
                state = lock;
            }
            else if(pound){
                state = button_pound;
            }
        default:
            state = init;
            break;
    }
    switch(state){//actions
        case init:
            break;
        case lock:
            output = 0x00;
            break;
        case button_pound:
            break;
        case button_y:
            break;
        case unlock:
            output = 0x01;
            break;
    }
    PORTB = output;
}

int main(void){
    DDRA = 0x00; PORTA = 0xFF;
    DDRB = 0xFF; PORTB = 0x00;
    
    state = init;
    
    while(1){
        Tick();
    }
    return 0;
}
