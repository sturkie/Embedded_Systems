/*	Author: sstur002
 *  Partner(s) Name: Raajitha Rajkumar
 *	Lab Section:
 *	Assignment: Lab #4  Exercise #2
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

enum States{init, wait, inc, dec, zero} state;

unsigned char value = 0x07;

void Tick(){
    unsigned char buttonOne = (PINA & 0x01);
    unsigned char buttonTwo = ((PINA & 0x02) >> 1);
    
            switch(state){
                case init:
                    state = wait;
                    break;
                case wait:
                    if(buttonOne && (value < 0x09) && !buttonTwo){
                        state = inc;
                    }
                    else if(buttonTwo && (value > 0x00) && !buttonOne){
                        state = dec;
                    }
                    else if(buttonOne && buttonTwo){
                        state = zero;
                    }
                    break;
                case inc:
                    state = wait;
                       break;
                case dec:
                    state = wait;
                    break;
                case zero:
                    state = wait;
                    break;
                default:
                    state = wait;
                    break;
            }
               switch(state){
                        case init:
                            break;
                        case wait:
                            break;
                        case inc:
                            value++;
                            break;
                        case dec:
                            value = value - 1;
                            break;
                        case zero:
                            value = 0x00;
                            break;
            }
    
    PORTB = value;
    
}

int main(void) {
    
                        DDRA = 0x00; PORTA = 0xFF;
                        DDRB = 0xFF; PORTB = 0x00;
                        
                        //value = 0x07;
                        state = init;
                        
    while (1) {
        Tick();
    }
    return 0;
}
