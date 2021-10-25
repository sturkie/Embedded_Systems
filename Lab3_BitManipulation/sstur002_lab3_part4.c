/*	Author: sstur002
 *  Partner(s) Name: Raajitha Rajkumar
 *	Lab Section: 21
 *	Assignment: Lab #3  Exercise #4
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

    DDRA = 0x00; PORTA = 0xFF; //input
    DDRB = 0xFF; PORTB = 0x00; //output
    DDRB = 0xFF; PORTC = 0x00; //output
    
    while(1){
      
        unsigned char input = PINA;
        unsigned char outputB = 0x00;
        unsigned char outputC = 0x00;
        
        outputB = ((input & 0xF0) >> 4);
        outputC = ((input & 0x0F) << 4);
        
        PORTB = outputB;
        PORTC = outputC;
    
        
    }


    return 0;
}
