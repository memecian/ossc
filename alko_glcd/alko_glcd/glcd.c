/*
 * Alexander "Memecian" Komyakov presents...
 * a library for HDG12864f-3 GLCD. (alko_glcd.a)
 */ 

#include <avr/io.h>

#define DIGITAL PORTC
#define COMMAND PORTA

#define set_bit(var, bit) ((var) |= (1 << (bit)))
#define clear_bit(var, bit) ((var) &= (unsigned)~(1 << (bit)))
#define bit_is_set(var, bit) ((var) & (1 << (bit)))
#define bit_is_clear(var, bit) !bit_is_set(var, bit)

static void ClearVars(void)
{
	PORTA, PORTC = 0;
}

void glcdInit(void)
{
	// Set data direction
	DDRC = 0xff; 
	DDRA = 0x07;
	
	COMMAND = 0b00000010;
	DIGITAL = 0b10101111; // Display : ON
	//Start ln :01XXXXXX 
	DIGITAL = 0b01000011;
	ClearVars();
}

void glcdRESET(void)
{
	COMMAND = 0b00000010;
	DIGITAL = 0b11100010;
	COMMAND, DIGITAL = 0;
}

int glcdRead(void)
{
	DDRA = 0;
	COMMAND = 0b00000101;
	return DIGITAL;
	DDRA = 0xff;
	COMMAND = 0;
}

void glcdWrite()
{
	COMMAND = 0b00000110;
	COMMAND = 0;
}

void glcdPixel(uint8_t page, uint8_t col)
{
	// Only the least significant 4 bits are needed for page address
	int pageTemp = 0b10110000;
	int upperCol = 0b00010000;
	int lowerCol = 0b00000000;
	
	// Set page address
	for (int i = 0; i < 4; i++)
	{
		if (bit_is_set(page, i))
		{
			set_bit(pageTemp, i);
		}
	}
	
	// Set upper column bit
	for (int i = 4; i < 8; i++)
	{
		if (bit_is_set(col, i))
		{
			set_bit(upperCol, i - 4);
		}
	}
	// Set lower column bit
	for (int i = 0; i < 4; i++)
	{
		if (bit_is_set(col, i))
		{
			set_bit(lowerCol, i);
		}
	}
		
	COMMAND = 0b00000010;
	DIGITAL = pageTemp;
	DIGITAL = upperCol;
	DIGITAL = lowerCol;
	DIGITAL, COMMAND = 0;
	glcdWrite();
}

void _glcdDebugFill(void)
{
	for (int i = 0; i < 16; i++)
	{
		for (int j = 0; j < 256; j++)
		{
			glcdPixel(i,j);
		}
	}
}

void _glcdManualCommand(int cmd, int dig)
{
	COMMAND = cmd;
	DIGITAL = dig;
	COMMAND, DIGITAL = 0;
}

