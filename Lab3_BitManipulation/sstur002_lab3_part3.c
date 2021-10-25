/*	Author: sstur002
 *  Partner(s) Name: Raajitha Rajkumar
 *	Lab Section: 21
 *	Assignment: Lab #3  Exercise #3
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

int main(void){

    DDRA = 0x00; PORTA = 0xFF;
    DDRC = 0xFF; PORTC = 0x00;
    
    while(1){
      
        unsigned char input = PINA & 0x0F;
        unsigned char indicator = (PINA & 0xF0) >> 4;
        unsigned char output = 0x00;
        if(input == 0x01 || input == 0x02){
            output = 0x60; //PC5 Lights, so does PC6
        }
        else if(input == 0x03 || input == 0x04){
            output = 0x70; //PC4 and PC5, and PC6 for low fuel
        }
        else if(input == 0x05 || input == 0x06){
            output = 0x38;
        }
        else if(input == 0x07 || input == 0x08 || input == 0x09){
            output = 0x3C;
        }
        else if(input == 0x0A || input == 0x0B || input == 0x0C){
            output = 0x3E;
        }
        else if(input > 0x0C){
            output = 0x3F;
        }
        if(indicator == 0x03){
            output = (output | 0x80);
        }
        
        PORTC = output;
        
    }


    return 0;
}
