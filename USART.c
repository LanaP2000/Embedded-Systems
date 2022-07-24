
#define F_CPU 16000000 //16Mhz frequency is set.
#define BAUD 9600 //Baud 9600
#define BAUDRATE ((F_CPU)/(BAUD*16UL)-1) //baud rate is set

#include <avr/io.h>
#include <util/delay.h>

void uart_init(void) //UART initialization function
{
	UBRR0H = (BAUDRATE >> 8); //Shifting the register to the right, 8 bits
	UBRR0L = BAUDRATE; //Setting baud rate
	UCSR0B |= (1 << TXEN0) | (1 << RXEN0); //Enabling receiver and transmitter
	UCSR0C |= (1 << UCSZ00) | (1 << UCSZ01); //8-bit data
}

uart_send (unsigned char data)
{
	while (!(UCSR0A & (1 << UDRE0))); //while data register is empty
	UDR0 = data; //load data in the register
}

int main(void)
{
	uart_init();
    unsigned char s[] = "823358842\r\n";
	
    while (1) 
    {
		for (int i = 0; i < sizeof(s); i++)
		{
			uart_send(s[i]);
		}
		_delay_ms(500);
    }
}
