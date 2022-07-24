#define F_CPU 16000000UL //16 MHz clock

#include <avr/io.h>

void pressed(void)
{
	PORTB |= (1 << 5); //LED on
	while (!(TIFR0 & (1 << OCF0B))); //Setting flag register
	TIFR0 |= (1 << OCF0B); //Reseting B flag register
	PORTB &= ~(1 << 5); //LED off
	while (!(TIFR0 & (1 << OCF0A)));
	TIFR0 |= (1 << OCF0A); //Reseting A flag register
}

int main(void)
{ 
	DDRB |= (1 << PORTB5); //Output LED
	DDRB &= ~(1 << PORTB7); //SW0 - input
	PORTB |= (1 << 7); //B7 - pull-up resistor
	TCCR0A |= (1 << WGM01); //Timer CTC mode
	OCR0A = 155; //Upper limit
	OCR0B = 0; //Toggle
	TCCR0B |= (1 << CS00) | (1 << CS02); //Prescaler
	
    while (1) 
    {
		while (!(PINB & (1 << 7))) //Button pressed
		{
			pressed();
			if (OCR0B < 155) //Until the maximum limit
			OCR0B++; //Increasing B
		}

		while (PINB & (1 << PINB7)) //Button released
		{
			if (OCR0B == 0)
		    break;
			
			else
			{
				pressed();
				OCR0B--;
			}	
		}
    }
}

