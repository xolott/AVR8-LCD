LCD Library for AVR8 Family
===========================

Description
-----------

C++ Library for Hitachi LCD with multiple configuration. Using C++ Overload benefics is possible to use this library like [cout] from the Standard [iostream] library.

Example:

'''cpp
LCD cout = LCD(); //Create a LCD class instance
cout.begin(16,4); //Begin configuration of a 16x4 LCD
cout<<cout.setPos(0,3)<<cout.setW(8)<<cout.align(LCD_LEFT_ALIGN)<<"HELLO"; //You can use method to manipulate the output format of the next text
cout<<"World"; //Or simply use it to print a string in the actual position
'''