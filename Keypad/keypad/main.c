/*
	Alexander "Memecian" Komyakov presents...

	keypad.c
	------------------
	A simple program to collect button presses on a 6x8 matrix and to send them 
	to the main processing unit (MPU) using USART. 
 */ 

#define F_CPU 8000000UL

#define set_bit(var, bit) ((var) |= (1 << (bit)))
#define clear_bit(var, bit) ((var) &= (unsigned)~(1 << (bit)))
#define bit_is_set(var, bit) ((var) & (1 << (bit)))
#define bit_is_clear(var, bit) !bit_is_set(var, bit)

#define byte uint8_t

#include <avr/io.h>
#include <util/delay.h>

/*Rows and columns designated pins
ROW0 PIND2
ROW1 PIND3
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
unsigned char dataToMPU[6] = {0}; //This array holds the button data, which will be sent to the MPU later.

void getButtons(int colNum)
{
	void getRowData(void)
	{
		//row-wise logging of data
		if (bit_is_set(PIND, 2)) //ROW0
		{
			dataToMPU[colNum] |= (1<<0);
		}
		if (bit_is_set(PIND, 3)) //ROW1
		{
			dataToMPU[colNum] |= (1<<1);
		}
		if (bit_is_set(PINB, 6)) //ROW2
		{
			dataToMPU[colNum] |= (1<<2);
		}
		if (bit_is_set(PINB, 7)) //ROW3
		{
			dataToMPU[colNum] |= (1<<3);
		}
		if (bit_is_set(PIND, 5)) //ROW4
		{
			dataToMPU[colNum] |= (1<<4);
		}
		if (bit_is_set(PIND, 6)) //ROW5
		{
			dataToMPU[colNum] |= (1<<5);
		}
		if (bit_is_set(PIND, 7)) //ROW6
		{
			dataToMPU[colNum] |= (1<<6);
		}
		if (bit_is_set(PINB, 0)) //ROW7
		{
			dataToMPU[colNum] |= (1<<8);
		}	
	}
	switch (colNum)
	{
		case 0:
			set_bit(PORTB, 1);
			getRowData();
			clear_bit(PORTB, 1);
			break;
		case 1:
			set_bit(PORTB, 2);
			getRowData();
			clear_bit(PORTB, 2);
			break;
		case 2:
			set_bit(PORTB, 3);
			getRowData();
			clear_bit(PORTB, 3);
			break;
		case 3:
			set_bit(PORTB, 4);
			getRowData();
			clear_bit(PORTB, 4);
		case 4:
			set_bit(PORTC, 0);
			getRowData();
			clear_bit(PORTC, 0);
			break;
		case 5:
			set_bit(PORTC, 1);
			getRowData();
			clear_bit(PORTC, 1);
			break;
	}
}

void uartInit(void) 
{
	set_bit(UCSRB, TXEN);	// Enable UART transmitter mode
	set_bit(UCSRC, URSEL);	// Register select
	set_bit(UCSRC, UCSZ0);	
	set_bit(UCSRC, UCSZ1);	// Select 8-bit packet mode
	UBRRL = 51;				// Set baud rate (9600)
}

void uartTransmitC(unsigned char data)
{
	UDR = data;							// Putting data into *U*ART *D*ata *R*egister
	while (bit_is_clear(UCSRA, UDRE));	// Wait until all data is transmitted.
}

void uartTransmitS(char *p)
{
	while(*p)
	{
		uartTransmitC(*(p++));
		_delay_us(100);
	}
}

int main(void)
{
	uartInit();
/*	Setting the Data Direction Registers (DDRx)
	0 - Input, 1 - Output					*/
	
	DDRB = 0b00011110;
	DDRC = 0b00000011;
	DDRD = 0b00000010;
    while (1) 
    {
		start:
		for (int i = 0; i < 6; i++)
		{
			getButtons(i);
		}
		
		for (int i = 0; i < 6; i++)
		{
			uartTransmitS(dataToMPU[i]);
		}
		uartTransmitC('\r');
		for (int i = 0; i < 6; i++)
		{
			dataToMPU[i] = 0x00;
		}
	}
	//Shouldn't be called, but just in case
	uartTransmitS("KC_ERR_LP_BRK" + '\r');
	goto start;
}