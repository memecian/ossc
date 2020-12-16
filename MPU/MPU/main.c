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
#include <string.h>
#include <util/delay.h>

// save memory by using a struct for booleans
struct sysBools
{
	unsigned int shift : 1;
	unsigned int alt : 1;
};

char expression[64] = {0};

// FUNCTION DEFS

void append(char* s, char c) {
	int len = strlen(s);
	s[len] = c;
	s[len+1] = '\0';
}

void getButtons() {
	
}
// -----------------------------------------------------------

int main(void)
{
	// initialize keypad pins
	DDRF = 0x00;
	DDRA = 0x3F;
	while (1)
	{	
		
	}
}