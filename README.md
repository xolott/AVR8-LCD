<a href="https://github.com/xolott/AVR8-LCD#libreria-de-lcd-para-microcontroladores-de-la-familia-avr8" title="Versión en Español!">Versión en Español!</a>
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
  
A difference with others library is the capability to show text in the correct line and position when the text pass the last position of the line.  

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
* `setPos(unsigned short x, unsigned short y)`: Like the `gotoxy` method but this is to use width the `<<` operator
* `align(bool a = LCD_LEFT_ALIGN)`: Align every text next to it when is used with the `setW` method. Options avaliable are `LCD_LEFT_ALIGN` and `LCD_RIGHT_ALIGN`
* `print(const char c)` or `print(const char c[])`: Send a char o char array to the actual LCD's position.
* `<<` operator: Use to format and print text in the LCD
  
    
TODO  
----  
  
In future versions I will add more overloads of `print` and `<<` operator methods to handle more data types like `int`, `long`, `float`, etc.  
  
Libreria de LCD para Microcontroladores de la familia AVR8
==========================================================  
  
Descripción
-----------

Libreia desarrollada en C++, usando el compilador AVR GCC, para LCD´s con controlador Hitachi con multuiples metodos.  
Usando los beneficios de sobrecarga de metodos en C++ es posible usar esta una instancia de la clase `LCD` como el `cout` de la libreria Estandar de C++ `iostream`.

Ejemplo:
  
```cpp  
    LCD cout = LCD(); //Crea una instancia de la clase LCD  
	cout.begin(16,4); //Inicia la configuracion para una LCD de 16x4  
	//Puedes usar metodos para manipular el formato del proximo texto a mostrar  
	cout<<cout.setPos(0,3)<<cout.setW(8)<<cout.align(LCD_LEFT_ALIGN)<<"Hola";  
	//O simplemente usar el operador para mostrar el texto en la posicion actual del LCD  
	cout<<"Mundo";  
```  
  
Una diferencia con respecto a la mayoria de las librerias para manejar una LCD, es la capacidad de mostrar el texto en la posicion y linea correcta a pesar de que sobrepase la posicion maxima de la linea actual.

Uso
-----

###	Hardware  
  
La libreria LCD para AVR8 usa la interfaz de 4 bits por lo que solo debes conectar los pines `DB7, DB6, DB5, DB4, EN` y `RS` a cualquier Pin de Proposito General o Multiplexado y el pin `RW` a Tierra (Ground o VSS)  
  
### Configuración  
  
En este ejemplo usare un ATMEGA328P.  
Primero, abre el archivo LCD.h y modifica `LCD_XX, LCD_XX_PORT` y `LCD_XX_DDR` con los correspondientes pines de tu hardware.  
  
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
  
Si usas pines Analogicos asegurate de configurarlos como Digitales antes de usar el metodo `begin`.
Si no realizas estos cambios se mostrara una advertencia al momento de compilar tu proyecto.  
  
### Metodos  
  
Accede a los metodos de la libreria a traves de instancias de la clase LCD. Los metodos disponibles son:  
  
* `begin(unsigned short col = 16, unsigned short row = 2)`: Inicializa la libreria LCD con el numero de columnas y filas pasado, y los pines asociados. Valores por defecto son `col=16` y `row=2`.
* `gotoxy(unsigned short x, unsigned short y)`: Mueve el cursor a la posicion asignada.
* `clear()`: Borra la pantalla LCD.
* `blink(bool b)`: Parpadea el caracter mostrado en la posicion actual del cursor.
* `cursor(bool c)`: Muestra o esconde el cursor.
* `setW(unsigned short w, bool f = true)`: Configura el ancho del proximo texto a mostrar, al igual que la funcion `setw()` de la libreria c++ estandar `iomanip`. Con la opcion de rellenar o no con espacios el espacio sobrante, si es posible.
* `setPos(unsigned short x, unsigned short y)`: Cumple la misma funcion del metodo `gotoxy` pero es usado junto al operador `<<`.
* `align(bool a = LCD_LEFT_ALIGN)`: Alinia cualquier texto mostrado luego de llamar este metodo. Es recomendable usarla junto al metodo `setW`. Las opciones disponibles son: `LCD_LEFT_ALIGN` y `LCD_RIGHT_ALIGN`.
* `print(const char c)` o `print(const char c[])`: Envia caracteres a la posicion actual del cursor de la LCD.
* Operador `<<`: Usado para dar formato y mostrar texto en la LCD.
  
    
TODO  
----  
  
En el futuro agregar mas sobrecarga del metodo `print` y el operador `<<` para aceptar mas tipos de datos, como `int`, `long`, `float`, etc.  
  