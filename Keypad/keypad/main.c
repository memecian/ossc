/*
	Alexander "Memecian" Malinin presents...

	keypad.c
	------------------
	A simple program to collect button presses on a 6x8 matrix and to send them 
	to the main processing unit (MPU) using USART. 
 */ 

#include <avr/io.h>

#define byte uint8_t

/*Rows and columns designated pins
ROW0 PIND3
ROW1 PIND4
ROW2 PINB6
ROW3 PINB7
ROW4 PIND5
ROW5 PIND6
ROW6 PIND7
ROW7 PINB0

COL0 PORTB1
COL1 PORTB2
COL2 PORTB3
COL3 PORTB4
COL4 PORTC0
COL5 PORTC1

Yes, it looks confusing and random, but it will make sense on the PCB later. Trust me.
*/
byte dataToMPU[6] = {0}; //This array holds the button data, which will be sent to the MPU later.

void getButtons(int colNum)
{
	void getRowData(void)
	{
		//row-wise logging of data
		if (PIND |= (1 << 3)) //ROW0
		{
			dataToMPU[colNum] |= (1<<0);
		}
		if (PIND |= (1 << 4)) //ROW1
		{
			dataToMPU[colNum] |= (1<<1);
		}
		if (PINB |= (1 << 6)) //ROW2
		{
			dataToMPU[colNum] |= (1<<2);
		}
		if (PINB |= (1 << 7)) //ROW3
		{
			dataToMPU[colNum] |= (1<<3);
		}
		if (PIND |= (1 << 5)) //ROW4
		{
			dataToMPU[colNum] |= (1<<4);
		}
		if (PIND |= (1 << 6)) //ROW5
		{
			dataToMPU[colNum] |= (1<<5);
		}
		if (PIND |= (1 << 7)) //ROW6
		{
			dataToMPU[colNum] |= (1<<6);
		}
		if (PINB |= (1 << 0)) //ROW7
		{
			dataToMPU[colNum] |= (1<<0);
		}	
	}
	switch (colNum)
	{
		case 0:
			PORTB |= (1<<0);
			getRowData();
			PORTB |= (0<<0);
		case 1:
			PORTB |= (1<<2);
			getRowData();
			PORTB |= (0<<2);
		case 2:
			PORTB |= (1<<3);
			getRowData();
			PORTB |= (0<<3);
		case 3:
			PORTB |= (1<<4);
			getRowData();
			PORTB |= (0<<4);
		case 4:
			PORTC |= (1<<0);
			getRowData();
			PORTC |= (0<<0);
		case 5:
			PORTC |= (1<<1);
			getRowData();
			PORTC |= (0<<1);
	}
}

int main(void)
{

/*	Setting the Data Direction Registers (DDRx)
	0 - Input, 1 - Output					*/
	
	DDRB = 0b00011110;
	DDRC = 0b00000011;
	DDRD = 0b00000010;
	
    while (1) 
    {
		for (int i = 0; i < 6; i++)
		{
			getButtons(i);
		}
		
		//FIXME: USART GOES HERE
		
		for (int i = 0; i < 6; i++)
		{
			dataToMPU[i] = 0;
		}
	}
}