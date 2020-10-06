/*
 * MPU.c
 * Created: 21.09.2020 14:01:39
 * Author : Administrator
 */ 
#define F_CPU 8000000UL

#define set_bit(var, bit) ((var) |= (1 << (bit)))
#define clear_bit(var, bit) ((var) &= (unsigned)~(1 << (bit)))
#define bit_is_set(var, bit) ((var) & (1 << (bit)))
#define bit_is_clear(var, bit) !bit_is_set(var, bit)

#define byte uint8_t

#define F_CPU 8000000UL

#define set_bit(var, bit) ((var) |= (1 << (bit)))
#define clear_bit(var, bit) ((var) &= (unsigned)~(1 << (bit)))
#define bit_is_set(var, bit) ((var) & (1 << (bit)))
#define bit_is_clear(var, bit) !bit_is_set(var, bit)

#include <avr/io.h>
#include <util/delay.h>

<<<<<<< Updated upstream
void uartInit(void)
{
	set_bit(UCSR0B, RXEN0);	// Enable UART transmitter mode
	set_bit(UCSR0C, UMSEL00);	// Register select
	set_bit(UCSR0C, UCSZ00);
	set_bit(UCSR0C, UCSZ01);	// Select 8-bit packet mode
	UBRR0L = 51;				// Set baud rate (9600)
}

void uartTransmit(char *p)
{
	while(*p)
	{
		UDR0 = (*(p++));
		while(bit_is_set(UCSR0A, TXC0));
	}
}
=======
char[6] received = {0};
char[6] receivedLast = {0};
>>>>>>> Stashed changes

int main(void)
{
    
    while (1) 
    {
    }
}
