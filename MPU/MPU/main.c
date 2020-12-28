/*
* MPU.c
* Created: 21.09.2020 14:01:39
* Author : Administrator
*/
#define F_CPU 8000000UL

#define true 1
#define false 0

#define not !
#define and &&
#define or  ||

#define set_bit(var, bit) ((var) |= (1 << (bit)))
#define clear_bit(var, bit) ((var) &= (unsigned)~(1 << (bit)))
#define bit_is_set(var, bit) ((var) & (1 << (bit)))
#define bit_is_clear(var, bit) !bit_is_set(var, bit)

#include <avr/io.h>
#include <string.h>
#include <util/delay.h>

// save memory by using a struct for booleans
struct sysVars
{
	unsigned int shift	: 1;
	unsigned int alt	: 1;
	unsigned int inMenu : 1;
	unsigned int base	: 2; 
	/*	base 10 = 0
		base 2	= 1
		base 8	= 2
		base 16 = 3  */
};

double numbers[32] = {0};

char buffer[64] = {'\0'};

char kpd[6] = {0, 0, 0, 0, 0, 0};

/*	
	imagine the structure like this:
	the index corresponds to the kpd columns,
	and the bits of each array item are the rows.
	the result : a grid consisting of 6*8 = 42 bools
*/

char ops[8][6][2] =	{	{"SH", "AL", "CL", "CU", "+", "-"},
						{"MN", "VC", "CD", "CR", "*", "/"},
						{"Pi", "ln", "\0", "\0", "\0", "DC"},
						{"^2", "\0", "FR", "(", ")", "\0"},
						{"Sq", "\0", "7", "8", "9", "\0"},
						{"\0", "\0", "4", "5", "6", "\0"},
						{"\0", "\0", "1", "2", "3", "\0"},
						{"\0", "\0", ".", "0", "an", "EQ"}};

// FUNCTION DEFS

void get_buttons(void)
{
	for (int c = 0; c < 6; c++)
	{
		set_bit(PORTB, c);
		for (int r = 0; r < 8; r++)
		{
			if (bit_is_set(PINE, r)) set_bit(kpd[c], r);
			else clear_bit(kpd[c], r);
		}
		clear_bit(PORTB, c);
	}
}



// -----------------------------------------------------------

int main(void) 
{
	/* initialize kpd pins */
	DDRB = 0x3F;
	DDRE = 0x00;
	while (1)
	{	
		
	}
}