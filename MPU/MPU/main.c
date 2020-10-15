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

uint8_t sysBools = 0;
/*
BIT 0 - shift
BIT 1 - alt
BIT 2 - 
BIT 3 - 
BIT 4 - 
BIT 5 - 
BIT 6 - 
BIT 7 -
*/
char received[6] = {0};
char receivedLast[6] = {0};
char lcdisplay[64] = {0};

void setBool (uint8_t bit, uint8_t val)
{
	if (val == 1)
	{set_bit(sysBools, bit);}
	else
	{clear_bit(sysBools, bit);}
}

char getButtons (int x, int y)
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
		*(buffer++) = uartReceiveC;
	} while ((buffer-1)!='\r');		// Waiting for carriage return
	*buffer = '\0';					// Standard C string termination symbol
}

int main(void)
{
	uartInit();
    while (1) 
    {
		if (getButtons(0, 0))
		{
			set_bit(sysBools, 1);
		}
    }
}
