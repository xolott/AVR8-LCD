/* 
* LCD.cpp
*
* Created: 05/08/2013 12:34:21 p.m.
* Author: José Truyol
*/


#include "LCD.h"
#include <string.h>
// default constructor
LCD::LCD()
{
	this->_setWidth = false;
	this->_col = 16;
	this->_row = 2;
	this->_x = 0;
	this->_y = 0;
	this->_align = LCD_LEFT_ALIGN;
	OUTPUT_PIN(LCD_RS_DDR,LCD_RS);
	OUTPUT_PIN(LCD_EN_DDR, LCD_EN);
	OUTPUT_PIN(LCD_DB4_DDR, LCD_DB4);
	OUTPUT_PIN(LCD_DB5_DDR, LCD_DB5);
	OUTPUT_PIN(LCD_DB6_DDR, LCD_DB6);
	OUTPUT_PIN(LCD_DB7_DDR, LCD_DB7); 
} //LCD

// default destructor
LCD::~LCD()
{
	/*INPUT_PIN(LCD_RS_DDR,LCD_RS);
	INPUT_PIN(LCD_EN_DDR, LCD_EN);
	INPUT_PIN(LCD_DB4_DDR, LCD_DB4);
	INPUT_PIN(LCD_DB5_DDR, LCD_DB5);
	INPUT_PIN(LCD_DB6_DDR, LCD_DB6);
	INPUT_PIN(LCD_DB7_DDR, LCD_DB7);*/
} //~LCD

void LCD::begin(unsigned short col /* = 16 */, unsigned short row /* = 2 */){
	this->_col = col;
	this->_row = row;
	this->_x = 0;
	this->_y = 0;
	this->_displayControl = LCD_DISPLAY_CONTROL | LCD_DISPLAY_ON | LCD_CURSOR_OFF |LCD_BLINK_CURSOR_OFF;
	// INICIANDO CONFIGURACION
	//Esperando estabilizacion de voltaje
	Delay_ms(40);
	//8 bits Length
	this->send8bitCommand(LCD_FUNCTION_SET | LCD_8_BITS_LENGTH);
	Delay_us(5000);
	this->send8bitCommand(LCD_FUNCTION_SET | LCD_8_BITS_LENGTH);
	Delay_us(100);
	this->send8bitCommand(LCD_FUNCTION_SET | LCD_8_BITS_LENGTH);
	this->send8bitCommand(LCD_FUNCTION_SET | LCD_4_BITS_LENGTH);/*(this->_row < 2)?LCD_1_LINE:*/
	this->send4bitCommand(LCD_FUNCTION_SET | LCD_4_BITS_LENGTH | (this->_row < 2)?LCD_1_LINE:LCD_2_LINES | LCD_FONT_5x8);
	this->send4bitCommand(this->_displayControl);
	this->send4bitCommand(LCD_CLEAR_DISPLAY);
	Delay_us(2000);
	this->send4bitCommand(LCD_ENTRY_MODE_SET | LCD_MOVE_RIGHT | LCD_NOT_SHIFT_DISPLAY);
}
void LCD::send(unsigned short cmd, unsigned short rs, unsigned short dataLength){
	PIN_WRITE(LCD_RS_PORT, LCD_RS, rs);
	PIN_WRITE(LCD_DB4_PORT, LCD_DB4, CHECK(cmd,4));
	PIN_WRITE(LCD_DB5_PORT, LCD_DB5, CHECK(cmd,5));
	PIN_WRITE(LCD_DB6_PORT, LCD_DB6, CHECK(cmd,6));
	PIN_WRITE(LCD_DB7_PORT, LCD_DB7, CHECK(cmd,7));
	this->pulseEnable();
	if(dataLength == LCD_4_BITS){
		PIN_WRITE(LCD_DB4_PORT, LCD_DB4, CHECK(cmd,0));
		PIN_WRITE(LCD_DB5_PORT, LCD_DB5, CHECK(cmd,1));
		PIN_WRITE(LCD_DB6_PORT, LCD_DB6, CHECK(cmd,2));
		PIN_WRITE(LCD_DB7_PORT, LCD_DB7, CHECK(cmd,3));
		this->pulseEnable();
	}
}
void LCD::pulseEnable(){
	PIN_WRITE(LCD_EN_PORT,LCD_EN,0);
	Delay_us(1);
	PIN_WRITE(LCD_EN_PORT,LCD_EN,1);
	Delay_us(1);    // enable pulse must be >450ns
	PIN_WRITE(LCD_EN_PORT,LCD_EN,0);
	Delay_us(100);   // commands need > 37us to settle
	//Delay_ms(5000);
}
void LCD::gotoXY(unsigned short x, unsigned short y){
	unsigned short data = 0;
	while(x > this->_col-1){
		x-=this->_col;
		y++;
	}
	if(y > this->_row - 1)
		y = 0;
	this->_x = x;
	this->_y = y;
	if (y%2)
		data = 0x40;
	while (y > 1){
		y -= 2;
		data += this->_col;
	}
	data += x;
	this->send4bitCommand(LCD_SET_DDRAM_ADDRESS | data);
}

void LCD::print(char c){
	if(this->_x > this->_col - 1){
		this->_x = 0;
		this->_y++;
		if(this->_y > this->_row - 1)
			this->_y = 0;
		this->gotoXY(this->_x, this->_y);
	}
	this->_x++;
	this->sendData(c);
	Delay_ms(100);
}
void LCD::print(const char c[]){
	unsigned short i;
	this->runSetWidth(strlen(c), LCD_LEFT_SIDE);
	for(i=0; c[i] != '\0'; i++)
		this->print(c[i]);
	this->runSetWidth(strlen(c), LCD_RIGHT_SIDE);
}

void LCD::clear(){
	this->send4bitCommand(LCD_CLEAR_DISPLAY);
	Delay_ms(2);
}

void LCD::blink(unsigned short b){
	BIT_WRITE(this->_displayControl,0,b);
	this->send4bitCommand(this->_displayControl);
}

void LCD::cursor(unsigned short c){
	BIT_WRITE(this->_displayControl,1,c);
	this->send4bitCommand(this->_displayControl);
}

LCD LCD::setW( unsigned short w, bool f )
{
	this->_setWidth = true;
	this->_setWidthFill = f;
	this->_width = w;
	return LCD();
}


LCD LCD::align( bool a /*= LCD_LEFT_ALIGN*/ )
{
	this->_align = a;
	return LCD();
}

void LCD::runSetWidth(unsigned short len, bool side)
{
	unsigned short i;
	if(this->_setWidth && side == this->_align){
		this->_setWidth = false;
		if(len < this->_width){
			this->_setWidth = false;
			if (this->_setWidthFill)
				for(i = 0; i< this->_width - len; i++)
					this->print(' ');
			else
				this->gotoXY(this->_x + this->_width - len, this->_y);
		}
	}
}

LCD LCD::setPos( unsigned short x, unsigned short y )
{
	this->gotoXY(x,y);
	return LCD();
}

LCD& operator <<(LCD& l, char c){
	l.print(c);
	return l;
}
LCD& operator <<(LCD& l, const char c[]){
	l.print(c);
	return l;
	unsigned short i;
	for(i=0; c[i] != '\0'; i++)
		l.print(c[i]);
	return l;
}
LCD& operator <<(LCD& l, char c[]){
	unsigned short i;
	for(i=0; c[i] != '\0'; i++)
		l.print(c[i]);
	return l;
}

LCD& operator<<( LCD& l, LCD w )
{
	return l;
}
