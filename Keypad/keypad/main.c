/*
	Alexander "Memecian" Malinin presents...

	keypad.c
	------------------
	A simple program to collect button presses on a 6x8 matrix and to send them 
	to the main processing unit (MPU) using USART. 
 */ 

#include <avr/io.h>

#define byte uint8_t

// Redefining pin numbers to make code more readable

// ROWS
#define r0 PIND3
#define r1 PIND4
#define r2 PINB6
#define r3 PINB7
#define r4 PIND5
#define r5 PIND6
#define r6 PIND7
#define r7 PINB0

// COLUMNS
#define c0 PORTB1 
#define c1 PORTB2
#define c2 PORTB3
#define c3 PORTB4
#define c4 PORTC0
#define c5 PORTC1

//Yes, it looks confusing and random, but it will make sense on the PCB later. Trust me.

byte[6] dataToMPU = {0};

int main(void)
{
	 /* 
	Setting the Data Direction Registers (DDRx)
	0 - Input, 1 - Output
	*/

	DDRB = 0b00011110;
	DDRC = 0b00000011;
	DDRD = 0b00000010;

    while (1) 
    {
		//This code is bloated
    }
}

