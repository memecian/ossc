/*
 * alko_glcd.c
 *
 * Created: 19.10.2020 11:52:54
 * Author : Administrator
 */ 

#include <avr/io.h>
#include <util/delay.h>


uint8_t digitalByte = 0;
uint8_t commandByte = 0;
/* Replace with your library code */
static void glcdClearVars(void)
{
	PORTA, PORTC = 0;
}

void glcdInit(void)
{
	DDRC = 0xff;
	DDRA = 0x07;
	
	PORTA = 0b00000010;
	PORTC = 0b10101110;
	_delay_us(100);
	glcdClearVars();
}

/*
void glcdClear()
{
	
}
*/