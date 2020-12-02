/*
 * GLCD_test.c
 * Created: 19.10.2020 11:51:02
 * Author : Administrator
 */ 

#include <avr/io.h>
#include "../../alko_glcd/alko_glcd/glcd.c"

int main(void)
{
    while (1) 
    {
		_glcdDebugFill();
	}
}