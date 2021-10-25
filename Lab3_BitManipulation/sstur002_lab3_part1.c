/*	Author: sstur002
 *  Partner(s) Name: Raajitha Rajkumar
 *	Lab Section:21
 *	Assignment: Lab #3  Exercise #1
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

int main(void) {
    /* Insert DDR and PORT initializations */
	DDRA = 0x00; PORTA = 0xFF; //input
	DDRB = 0x00; PORTB = 0xFF; //input
	
	DDRC = 0xFF; PORTC = 0x00; //output
	
	unsigned char inputA = 0x00;
	unsigned char inputB = 0x00;
	
	
	
    /* Insert your solution below */
    while (1) {
		
		unsigned char whileRun = 0;
		unsigned char counter = 0;
		
		inputA = PINA;
		inputB = PINB;
		
		while(whileRun < 8){
			if((inputA & 0x01) == 0x01){ //if the last bit is = 1
				counter++;
			}
			if((inputB & 0x01) == 0x01){
				counter++;
			}
			inputA = inputA >> 1;
			inputB = inputB >> 1;
			
			whileRun++;
		}
		
		/*
		while(whileRunA < 8){
			if((inputA & 0x01) == 0x01){
				counter = counter + 1;
			}
			inputA = inputA >> 1;
			whileRunA = whileRunA + 1;
		}
		while(whileRunB < 8){
			if((inputB & 0x01) == 0x01){
				counter = counter + 1;
			}
			inputB = inputB >> 1;
			whileRunB = whileRunB + 1;
		}*/
		
		PORTC = counter;
		
    }
    return 0;
}
