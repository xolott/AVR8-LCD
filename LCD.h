/* 
* LCD.h
*
* Created: 05/08/2013 12:34:22 p.m.
* Author: José Truyol
*/


#ifndef __LCD_H__
#define __LCD_H__

#include <stdint.h>
#include <avr/io.h>
#define F_CPU 20000000UL
#include <util/delay.h>
#include "truyolMacros.h"

#define LCD_RS PORTB1
#define LCD_RS_DDR DDRB
#define LCD_RS_PORT PORTB

#define LCD_EN PORTB2
#define LCD_EN_DDR DDRB
#define LCD_EN_PORT PORTB

#define LCD_DB4 PORTB3
#define LCD_DB4_DDR DDRB
#define LCD_DB4_PORT PORTB

#define LCD_DB5 PORTB4
#define LCD_DB5_DDR DDRB
#define LCD_DB5_PORT PORTB

#define LCD_DB6 PORTB5
#define LCD_DB6_DDR DDRB
#define LCD_DB6_PORT PORTB

#define LCD_DB7 PORTC0
#define LCD_DB7_DDR DDRC
#define LCD_DB7_PORT PORTC

#if !defined(LCD_RS_DDR) | !defined(LCD_RS_PORT) | !defined(LCD_RS)
	#warning "LCD: RS no definido. Usando PIN por defecto."
	#define LCD_RS_DDR DDRB
	#define LCD_RS_PORT PORTB
	#define LCD_RS PORTB0
#endif
#if !defined(LCD_EN_DDR) | !defined(LCD_EN_PORT) | !defined(LCD_EN)
	#warning "LCD: EN no definido. Usando PIN por defecto."
	#define LCD_EN_DDR DDRB
	#define LCD_EN_PORT PORTB
	#define LCD_EN PORTB1
#endif
#if !defined(LCD_DB4_DDR) | !defined(LCD_DB4_PORT) | !defined(LCD_DB4)
	#warning "LCD: DB4 no definido. Usando PIN por defecto."
	#define LCD_DB4_DDR DDRB
	#define LCD_DB4_PORT PORTB
	#define LCD_DB4 PORTB0
#endif
#if !defined(LCD_DB5_DDR) | !defined(LCD_DB5_PORT) | !defined(LCD_DB5)
	#warning "LCD: DB5 no definido. Usando PIN por defecto."
	#define LCD_DB5_DDR DDRB
	#define LCD_DB5_PORT PORTB
	#define LCD_DB5 PORTB0
#endif
#if !defined(LCD_DB6_DDR) | !defined(LCD_DB6_PORT) | !defined(LCD_DB6)
	#warning "LCD: DB6 no definido. Usando PIN por defecto."
	#define LCD_DB6_DDR DDRB
	#define LCD_DB6_PORT PORTB
	#define LCD_DB6 PORTB0
#endif
#if !defined(LCD_DB7_DDR) | !defined(LCD_DB7_PORT) | !defined(LCD_DB7)
	#warning "LCD: DB7 no definido. Usando PIN por defecto."
	#define LCD_DB7_DDR DDRB
	#define LCD_DB7_PORT PORTB
	#define LCD_DB7 PORTB0
#endif

#define ON							1
#define OFF							0
#define LCD_8_BITS					1
#define LCD_4_BITS					0
#define LCD_EXECUTION_TIME			1520 //uS

#define LCD_CLEAR_DISPLAY			0x01

#define LCD_RETURN_HOME				0x02

#define LCD_ENTRY_MODE_SET			0x04
#define LCD_MOVE_RIGHT				0x02
#define LCD_MOVE_LEFT				0x00
#define LCD_SHIFT_DISPLAY			0x01
#define LCD_NOT_SHIFT_DISPLAY		0x00

#define LCD_DISPLAY_CONTROL			0x08
#define LCD_DISPLAY_ON				0x04
#define LCD_DISPLAY_OFF				0x00
#define LCD_CURSOR_ON				0x02
#define LCD_CURSOR_OFF				0x00
#define LCD_BLINK_CURSOR_ON			0x01
#define LCD_BLINK_CURSOR_OFF		0x00

#define LCD_CURSOR_OR_DISPLAY_SHIFT	0x10
#define LCD_DISPLAY_SHIFT			0x08
#define LCD_CURSOR_MOVE				0x00
#define LCD_SHIFT_RIGHT				0x04
#define LCD_SHIFT_LEFT				0x00

#define LCD_FUNCTION_SET			0x20
#define LCD_8_BITS_LENGTH			0x10
#define LCD_4_BITS_LENGTH			0x00
#define LCD_2_LINES					0x08
#define LCD_1_LINE					0x00
#define LCD_FONT_5x10				0x04
#define LCD_FONT_5x8				0x00

#define LCD_SET_CGRAM_ADDRESS		0x40
#define LCD_SET_DDRAM_ADDRESS		0x80

#define LCD_FILL					true
#define LCD_NO_FILL					false
#define LCD_LEFT_ALIGN				true
#define LCD_RIGHT_ALIGN				false
#define LCD_LEFT_SIDE				false
#define LCD_RIGHT_SIDE				true

class LCD
{
	//variables
	public:
	protected:
	private:
		unsigned short _width;
		bool _setWidth;
		bool _setWidthFill;
		unsigned short _row;
		unsigned short _col;
		unsigned short _x;
		unsigned short _y;
		unsigned short _displayControl;
		bool _align;
	//functions
	public:
		LCD();
		~LCD();
		void begin(unsigned short col = 16, unsigned short row = 2);
		void gotoXY(unsigned short x, unsigned short y);
		void print(char c);
		void print(const char c[]);
		void clear();
		void blink(unsigned short b);
		void cursor(unsigned short c);
		LCD setW(unsigned short w, bool f = true);
		LCD setPos(unsigned short x, unsigned short y);
		LCD align(bool a = LCD_LEFT_ALIGN);
		void send8bitCommand(unsigned short cmd){
			this->send(cmd,0,LCD_8_BITS);
		}
		void send4bitCommand(unsigned short cmd){
			this->send(cmd,0,LCD_4_BITS);
		}
		void sendData(unsigned short data){
			this->send(data,1,LCD_4_BITS);
		}
	protected:
	private:
		void runSetWidth(unsigned short len, bool side);
		void pulseEnable();
		void send(unsigned short cmd, unsigned short rs, unsigned short dataLength);
		//LCD( const LCD &c );
		//LCD& operator=( const LCD &c );

}; //LCD
LCD& operator <<(LCD& l, LCD w);
LCD& operator <<(LCD& l, const char *c);
LCD& operator<<(LCD& l, char c);
LCD& operator <<(LCD& l, char *c);
#endif //__LCD_H__
