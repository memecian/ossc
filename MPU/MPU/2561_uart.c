#define set_bit(var, bit) ((var) |= (1 << (bit)))
#define clear_bit(var, bit) ((var) &= (unsigned)~(1 << (bit)))
#define bit_is_set(var, bit) ((var) & (1 << (bit)))
#define bit_is_clear(var, bit) !bit_is_set(var, bit)

#ifndef F_CPU 
#pragma message "F_CPU undefined, using 8Mhz."
#define F_CPU 8000000UL
#endif

#ifndef BAUD
#pragma message "Baudrate undefined, using 9600."
#define BAUD 9600
#endif

//calculations
#define UBRR_VAL ((F_CPU + BAUD * 8) / (BAUD * 16) -1)
#define BAUD_ACT (F_CPU / (16 * (UBBR_VAL + 1)))
#define BAUD_ERR ((BAUD_ACT * 1000) / BAUD) //1000 = no errors

#if ((BAUD_ERR < 990) || (BAUD_ERR > 1010))
#error "Baudrate error exceeds 1% margin, cancelling compiling process."
#endif

uint8_t uart_init(uint8_t uart) {
	if (uart == 0) {
		UBRR0 = UBRR_VAL;
		return 1;
	}
	else if (uart == 1) {	
		UBRR1 = UBRR_VAL;
		return 1;
	}
	else return 0;
}