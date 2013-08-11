LCD Library for AVR8 Family
===========================

Description
-----------

C++ Library for Hitachi LCD with multiple methods. Using C++ Overload benefics is possible to use this library like `cout` from the Standard `iostream` library.

Example:
  
```cpp  
    LCD cout = LCD(); //Create a LCD class instance  
	cout.begin(16,4); //Begin configuration of a 16x4 LCD  
	//You can use methods to manipulate the output format of the next text  
	cout<<cout.setPos(0,3)<<cout.setW(8)<<cout.align(LCD_LEFT_ALIGN)<<"HELLO";  
	cout<<"World"; //Or simply use it to print a string in the actual LCD's position  
```  

Usage
-----

###	Hardware  
  
The AVR8 LCD Library use a 4bit interface. Connect only the `DB7, DB6, DB5, DB4, EN` and `RS` to any AVR8 General Purpose o Multiplexed Pin and the `RW` pin to Ground (VSS)  
  
### Configuration  
  
In this example I will use a ATMEGA328P.  
First, open the LCD.h file and change the `LCD_XX, LCD_XX_PORT` and `LCD_XX_DDR` to the correspondind PIN in your hardware.  
  
```cpp  
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
```  

If you don't make this change a warning will be show to you when compile the project.
  
### Methods  
  
Access library methods through the LCD instance. Methods avaliable are:  
  
* `begin(unsigned short col = 16, unsigned short row = 2)`: Initialise the LCD Library and Port directions for every PIN with the number of columns and rows passed. Default values are `col=16` and `row=2`.
* `gotoxy(unsigned short x, unsigned short y)`: Set the cursor position.
* `clear()`: Clear the LCD
* `blink(bool b)`: Blink the chracter in the cursor position.
* `cursor(bool c)`: Show or hide the cursor.
* `setW(unsigned short w, bool f = true)`: Set the width of the next string, like the standard C++ `iomanip` library, `setw()` function. With the option to Fill or not with space the remanent space if is possible.
* `setPos(unsigned short x, unsigned short y)`: Like the `gotoxy` method but this is to use width the `<<` operant
* `align(bool a = LCD_LEFT_ALIGN)`: Align every text next to it when is used with the `setW` method. Options avaliable are `LCD_LEFT_ALIGN` and `LCD_RIGHT_ALIGN`
* 'print(const char c)` or `print(const char c[])`: Send a char o char array to the actual LCD's position.
* `<<` operator: Use to format and print text in the LCD
  
    
TODO  
----  
  
In future versions I will add more overloads of `print` and `<<` operator methods to handle more data types like `int`, `long`, `float`, etc.