/*
 * LCD328P.cpp
 *
 * Created: 05/08/2013 12:30:04 p.m.
 *  Author: José Truyol
 */ 

#define F_CPU 20000000UL

#include <avr/io.h>
#include <util/delay.h>
#include "truyolMacros.h"
#include "LCD.h"


int main(void)
{
	unsigned short m = 0x10;
	SET(DDRB, DDB0);
	OUTPUT_PIN(DDRB, DDB1);
	SET(PORTB, PORTB0);
	LCD cout = LCD();
	cout.begin(16,4);
	//lcd.clear();
	cout.cursor(ON);
	cout.blink(ON);
	cout<<cout.setPos(0,0)<<cout.align(LCD_RIGHT_ALIGN)<<cout.setW(13)<<"Voltaje: "<<"1 V";
	cout<<cout.setPos(0,1)<<cout.setW(13)<<"Corriente: "<<"2 A";
	cout<<cout.setPos(0,2)<<cout.setW(13)<<"Potencia: "<<"3 W";
	cout<<cout.setPos(0,3)<<cout.setW(13)<<"Resistencia: "<<"4 O";
	
	//cout.clear();
    while(1)
    {
		//lcd.send4bitCommand(LCD_SET_DDRAM_ADDRESS | 0x40);
		//lcd.sendData('H');
		PIN_WRITE(PORTB,PORTB0,CHECK(m,4));
		Delay_ms(100);
		PIN_WRITE(PORTB,PORTB0,CHECK(m,0));
		Delay_ms(1000);
    }
}