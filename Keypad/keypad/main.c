/*
	Alexander "Memecian" Malinin presents...

	keypad.c
	------------------
	A simple program to collect button presses on a 6x8 matrix and to send them 
	to the main processing unit (MPU) using USART. 
 */ 

#include <avr/io.h>
//#include <>

#define byte uint8_t

// Redefining pin numbers to make code more readable

// ROWS
#define ROW0 PIND3
#define ROW1 PIND4
#define ROW2 PINB6
#define ROW3 PINB7
#define ROW4 PIND5
#define ROW5 PIND6
#define ROW6 PIND7
#define ROW7 PINB0

// COLUMNS
#define COL0 PORTB1 
#define COL1 PORTB2
#define COL2 PORTB3
#define COL3 PORTB4
#define COL4 PORTC0
#define COL5 PORTC1
//	Yes, it looks confusing and random, but it will make sense on the PCB later. Trust me.

byte dataToMPU[6] = {0}; //This array holds the button data, which will be sent to the MPU later.

	
void getButtons(int colNum)
{
	void getRows(void)
	{
		if (ROW0 == 1)
		{
			dataToMPU[colNum] |= (1<<0);
		}
		if (ROW1 == 1)
		{
			dataToMPU[colNum] |= (1<<1);
		}
		if (ROW2 == 1)
		{
			dataToMPU[colNum] |= (1<<2);
		}
		if (ROW3 == 1)
		{
			dataToMPU[colNum] |= (1<<3);
		}
		if (ROW4 == 1)
		{
			dataToMPU[colNum] |= (1<<4);
		}
		if (ROW5 == 1)
		{
			dataToMPU[colNum] |= (1<<5);
		}
		if (ROW6 == 1)
		{
			dataToMPU[colNum] |= (1<<6);
		}
		if (ROW7 == 1)
		{
			dataToMPU[colNum] |= (1<<7);
		}
		// Is it pretty? No. Does it work? Yes.
	}
	
	switch (colNum)
	{
	case 0 :
		COL0 = 1;
		getRows();
		COL0 = 0;
		break;
	case 1 :
		COL1 = 1;
		getRows();
		COL1 = 0;	
		break;
	case 2 :
		COL2 = 1;
		getRows();
		COL2 = 0;
		break;	
	case 3 :
		COL3 = 1;
		getRows();
		COL3 = 0;
		break;
	case 4 :
		COL4 = 1;
		getRows();
		COL4 = 0;
		break;
	case 5 :
		COL5 = 1;
		getRows();
		COL5 = 0;
		break;
	}
}
//FIXME: For some reason, the names I've defined don't work here. Why?
int main(void)
{


/*	Setting the Data Direction Registers (DDRx)
	0 - Input, 1 - Output					*/
	
	DDRB = 0b00011110;
	DDRC = 0b00000011;
	DDRD = 0b00000010;
	
    while (1) 
    {
		for (int i; i < 6; i++)
		{
			getButtons(i);
		}
		
		//FIXME: USART GOES HERE
		
		for (int i; i < 6; i++)
		{
			dataToMPU[i] = 0;
		}
	}
}