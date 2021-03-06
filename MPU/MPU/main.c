/*
* MPU.c
* Created: 21.09.2020 14:01:39
* Author : Administrator
*/
#define F_CPU 8000000UL
#define true 1
#define false 0

#define set_bit(var, bit) ((var) |= (1 << (bit)))
#define clear_bit(var, bit) ((var) &= (unsigned)~(1 << (bit)))
#define bit_is_set(var, bit) ((var) & (1 << (bit)))
#define bit_is_clear(var, bit) !bit_is_set(var, bit)

#include <avr/io.h>
#include <util/delay.h>

// save memory by using a struct for booleans
struct sysBools
{
	unsigned int shift : 1;
	unsigned int alt : 1;
};

char received[6] = {0};
char receivedLast[6] = {0};
char expression[64] = {0};

// FUNCTION DEFS

void append(char* s, char c) {
	int len = strlen(s);
	s[len] = c;
	s[len+1] = '\0';
}

char button(int x, int y)
{
	if (bit_is_set(received[x], y))
	{return true;}
	else
	{return false;}
}

void uartInit(void)
{
	set_bit(UCSR0B, RXEN0);		// Enable UART receiver mode
	set_bit(UCSR0C, UMSEL00);	// Register select
	set_bit(UCSR0C, UCSZ00);
	set_bit(UCSR0C, UCSZ01);	// Select 8-bit packet mode
	UBRR0L = 51;				// Set baud rate (9600)
}

char uartReceiveC(void)
{
	while(bit_is_clear(UCSR0A, RXC0));
	return UDR0;
}

void uartReceiveS(char *buffer)
{
	do
	{
		*(buffer++) = uartReceiveC();
	} while ((buffer-1)!='\r');		// Waiting for carriage return
	*buffer = '\0';					// Standard C string termination symbol
}

// -----------------------------------------------------------

int main(void)
{
	uartInit();
	while (1)
	{	
		
		//Processing basic commands (0-9, plus, minus, all that jazz)
		
		if (button(2,4)) {append(expression, '7');}
		if (button(3,4)) {append(expression, '8');}
		if (button(5,4)) {append(expression, '7');}	
		
		
		if (button(2,5)) {append(expression, '4');}
		if (button(3,5)) {append(expression, '5');}
		if (button(5,5)) {append(expression, '6');}
		
		
		if (button(2,6)) {append(expression, '1');}
		if (button(3,6)) {append(expression, '2');}
		if (button(5,6)) {append(expression, '3');}	
		
		
		if (button(2,7)) {append(expression, ',');}
		if (button(3,7)) {append(expression, '0');}
		if (button(5,7)) {append(expression, '-');}
			
		
		if (button(4,0)) {append(expression, '+');}
		if (button(5,0)) {append(expression, '-');}
		if (button(4,1)) {append(expression, '*');}
		if (button(5,1)) {append(expression, '/');}
			
			
		for (int i = 0; i > 6; i++)
		{
			receivedLast[i] = received[i];
		}
	}
}