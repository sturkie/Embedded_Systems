# Intermediate Embedded Systems Lab
This is a repo for intermediate embedded systems lab projects

## Lab 2
### Introduction to AVR
This is a basic introduction to C for programming AVR microcontrollers
#### Part 1
We mask our PINA input with 3 to only check the last 2 bits. If the input is 0x01 (or A0 = 1 and A1 = 0) then we output 0x01 on our output, PORTB.
#### Part 2
We mask our PINA input with 0x0F to only check the last 4 bits. We create a ```counter``` variable and set it to 0. We enter a for-loop for 4 loops. If the last bit of input (A0) is 0, we increment ```counter``` and shift the entire input to the right by 1. PORTB updates with the value of ```counter```.
#### Part 3
Part 3 is set up the same as Part 2. If ```counter``` is greater than 0, PORTB updates with the value of ```counter```. If ```counter``` is NOT greater than 0, PORTB updates with the value of 0x80.
## Lab 3
### Bit Manipulation
## Lab 4
### State Machines
## Lab 5
### Introduction to Hardware
## Lab 6
### Synchronized State Machines
## Lab 7
### LCD
## Lab 8
### ADC
## Lab 9
### PWM
## Lab 10
### Concurrent State Machines
## Lab 11
### Scheduler
