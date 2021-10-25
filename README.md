# Intermediate Embedded Systems Lab
This is a repo for intermediate embedded systems lab projects

## Lab 2
### Introduction to AVR
This is a basic introduction to C for programming AVR microcontrollers
#### Part 1
We mask our PINA input with 3 to only check the last 2 bits. If the input is 0x01 (or A0 = 1 and A1 = 0) then we output 0x01 on our output, PORTB.
#### Part 2
We mask our PINA input with 0x0F to only check the last 4 bits. We create a counter variable and set it to 0. We enter a for-loop for 4 loops. If the last bit of input (A0) is 0, we increment counter and shift the entire input to the right by 1. PORTB updates with the value of counter.
#### Part 3
Part 3 is set up the same as Part 2. If counter is greater than 0, PORTB updates with the value of counter. If counter is NOT greater than 0, PORTB updates with the value of 0x80.
## Lab 3
### Bit Manipulation
#### Part 1
This exercise will count all the 1s in two inputs. Using PINA and PINB as inputs, we check if the last bit of each output is equal to 0x01 in a while-loop for 8 repetitions. If true, a counter variable increments. After the check, regardless of a pass or not, the inputs shift right by 1. PORTC updates with the total value of counter.
#### Part 2
This exercise is meant to mimick a fuel tank amount, ideally output on LED lights for instance. The upper 4 bits (A7:4) indicate if the tank is low. The lower 4 bits (A3:0) represent the tank above the low threshold (above input 0x06). We use PINA as our input. If the input is 0x01 or 0x02, bit A6 on PORTC will light indicating low fuel and P5 for the amount. If the input is 0x03 or 0x04, we output 0x70 (01110000) where A6 still indicates low fuel.  If the output is 0x05 or 0x06, A6 no longer lights and our output is now 0x38. When the tank is full (or input is greater than 0x0C), our output is 0x3F (00111111). We then write output to PORTC.
#### Part 3
Part 3 runs similar to part 2. Here we have a variable named indicator that looks at the first 4 bits of our input. If our indicator is equal to 0x03, then we set the first bit of output (A7) to 1 regardless of the rest of its value. We do this by or-ing (bitwise operator |) output with 0x80. We then write output to PORTC.
#### Part 4
This exercise features two outputs, PORTB and PORTC. PORTB outputs the input masked with 0xF0 and shifts it 4 to the right. PORTC outputs the input masked with 0x0F and shifts it 4 to the left.
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
