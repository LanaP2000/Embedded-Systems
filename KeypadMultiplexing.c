/*
 * Lab4.c
 *
 * Created: 11/16/2020 1:08:40 PM
 * Author : Admin
 */ 

#define F_CPU 16000000UL //16 MHz clock
#define BAUD 9600 // Baud 9600
#define BAUDRATE ((F_CPU) / (BAUD * 16UL) - 1) //Baud rate

#include <avr/io.h>
#include <util/delay.h>

void uart_init(void) //UART initialization
{
	UBRR0H = (BAUDRATE >> 8);  //Shift register to the right by 8 bits
	UBRR0L = BAUDRATE; //Set Baud rate
	UCSR0B |= (1 << TXEN0); //Enable receiver and transmitter
	UCSR0C |= (1 << UCSZ00) | (1 << UCSZ01); //8-bit data
}

void uart_Tx (unsigned char data) //UART TX
{
	while (!(UCSR0A & (1 << UDRE0))); //While data register is empty
	UDR0 = data; //Load data into the register
} 

void keypadScan (void) //Scan keypad
{
	const char keyChar[4][4] = {{'1', '2', '3', 'A'}, {'4', '5', '6', 'B'}, {'7', '8', '9', 'C'}, {'*', '0', '#', 'D'}}; //Keypad matrix
	for (int i = 4; i < 8; i++) //Scan through rows
	{
		PORTD &= ~(1 << (i));
		for (int j = 0; j < 4; j++) //Scan through columns
		{
			if (!(PINB & (1 << (j))))
			{
				uart_Tx(keyChar[i - 4][j]);
				_delay_ms(500);
			}
		}
		PORTD |= (1 << (i));
	}
}

int main(void)
{
    uart_init();
	
	DDRD |= (1 << DDD4) | (1 << DDD5) | (1 << DDD6) | (1 << DDD7); //Rows as output, specifically PDx
	DDRB &= ~(1 << DDB0) & ~(1 << DDB1) & ~(1 << DDB2) & ~(1 << DDB3); //Columns as inputs, specifically PBx
	PORTB |= (1 << PORTB0) | (1 << PORTB1) | (1 << PORTB2) | (1 << PORTB3); //Enable pull-up resistors in columns
	PORTD |= (1 << 4 | 1 << 5 | 1 << 6 | 1 << 7); //Rows high
	
    while (1) 
    {
		keypadScan();
    }
}