
#ifndef __TRUYOLMACROS_H__
#define __TRUYOLMACROS_H__
	#define SET(byte, bit) {byte |= 1 << bit;}
	#define CLEAR(byte, bit) {byte &= ~(1 << bit);}
	#define TOGGLE(byte, bit) {byte ^= 1 << bit;}
	#define CHECK(byte, bit) ((byte>>bit) & 0x01)?1:0

	#define OUTPUT	1
	#define INPUT	0

	#define OUTPUT_PIN(byte,bit) SET(byte,bit)
	#define INPUT_PIN(byte,bit) CLEAR(byte,bit)

	#define Delay_ms(d) _delay_ms(d)
	#define Delay_us(d) _delay_us(d)
	
	static inline void PIN_WRITE(volatile uint8_t &byte, unsigned short bit, unsigned short da){
		if(da){
			SET(byte,bit);
		}
		else
		CLEAR(byte,bit);
	}
	static inline void BIT_WRITE(unsigned short &byte, unsigned short bit, unsigned short da){
		if(da){
			SET(byte,bit);
		}
		else
		CLEAR(byte,bit);
	}
#endif