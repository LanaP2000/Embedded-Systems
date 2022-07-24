#define F_CPU 16000000UL //16 MHz clock

#include <avr/io.h>
#include <util/delay.h>

void dot()
{
	DDRB |= (1 << DDRB5); //Setting port DDRB5 to OUTPUT
	PORTB |= (1 << PORTB5); //Turning LED on
	_delay_ms(200); //200 ms.
	PORTB &= ~(1 << PORTB5); //Turning LED off
	_delay_ms(200); //200 ms.
}

void dash()
{
	DDRB |= (1 << DDRB5); //Setting port DDRB5 to OUTPUT
	PORTB |= (1 << PORTB5); //Turning LED on
	_delay_ms(600); //600 ms.
	PORTB &= ~(1 << PORTB5); //Turning LED off
	_delay_ms(200); //200 ms.
}

void space()
{
	DDRB |= (1 << DDRB5); //Setting port DDRB5 to OUTPUT
	PORTB &= ~(1 << PORTB5); //Turning LED off
	_delay_ms(600); //600 ms. --- letter space
}

int main(void)
{
	char s[] = "Lana 823358842";
	
	while (1)
	{
		for (int i = 0; i < sizeof(s); i++)
		{
			if (s[i] == 'A' || s[i] == 'a')
			{
				dot(); dash(); space();
			}
			if (s[i] == 'B' || s[i] == 'b')
			{
				dash(); dot(); dot(); dot(); space();
			}
			if (s[i] == 'C' || s[i] == 'c')
			{
				dash(); dot(); dash(); dot(); space();
			}
			if (s[i] == 'D' || s[i] == 'd')
			{
				dash(); dot(); dot(); space();
			}
			if (s[i] == 'E' || s[i] == 'e')
			{
				dot(); space();
			}
			if (s[i] == 'F' || s[i] == 'f')
			{
				dot(); dot(); dash(); dot(); space();
			}
			if (s[i] == 'G' || s[i] == 'g')
			{
				dash(); dash(); dot(); space();
			}
			if (s[i] == 'H' || s[i] == 'h')
			{
				dot(); dot(); dot(); dot(); space();
			}
			if (s[i] == 'I' || s[i] == 'i')
			{
				dot(); dot(); space();
			}
			if (s[i] == 'J' || s[i] == 'J')
			{
				dot(); dash(); dash(); dash(); space();
			}
			if (s[i] == 'K' || s[i] == 'k')
			{
				dash(); dot(); dash(); space();
			}
			if (s[i] == 'L' || s[i] == 'l')
			{
				dot(); dash(); dot(); dot(); space();
			}
			if (s[i] == 'M' || s[i] == 'm')
			{
				dash(); dash(); space();
			}
			if (s[i] == 'N' || s[i] == 'n')
			{
				dash(); dot(); space();
			}
			if (s[i] == 'O' || s[i] == 'o')
			{
				dash(); dash(); dash(); space();
			}
			if (s[i] == 'P' || s[i] == 'p')
			{
				dot(); dash(); dash(); dot(); space();
			}
			if (s[i] == 'Q' || s[i] == 'q')
			{
				dash(); dash(); dot(); dash(); space();
			}
			if (s[i] == 'R' || s[i] == 'r')
			{
				dot(); dash(); dot(); space();
			}
			if (s[i] == 'S' || s[i] == 's')
			{
				dot(); dot(); dot(); space();
			}
			if (s[i] == 'T' || s[i] == 't')
			{
				dash(); space();
			}
			if (s[i] == 'U' || s[i] == 'u')
			{
				dot(); dot(); dash(); space();
			}
			if (s[i] == 'V' || s[i] == 'v')
			{
				dot(); dot(); dot(); dash(); space();
			}
			if (s[i] == 'W' || s[i] == 'w')
			{
				dot(); dash(); dash(); space();
			}
			if (s[i] == 'X' || s[i] == 'x')
			{
				dash(); dot(); dot(); dash(); space();
			}
			if (s[i] == 'Y' || s[i] == 'y')
			{
				dash(); dot(); dash(); dash(); space();
			}
			if (s[i] == 'Z' || s[i] == 'z')
			{
				dash(); dash(); dot(); dot(); space();
			}
			if (s[i] == '1')
			{
				dot(); dash(); dash(); dash(); dash(); space();
			}
			if (s[i] == '2')
			{
				dot(); dot(); dash(); dash(); dash(); space();
			}
			if (s[i] == '3')
			{
				dot(); dot(); dot(); dash(); dash(); space();
			}
			if (s[i] == '4')
			{
				dot(); dot(); dot(); dot(); dash(); space();
			}
			if (s[i] == '5')
			{
				dot(); dot(); dot(); dot(); dot(); space();
			}
			if (s[i] == '6')
			{
				dash(); dot(); dot(); dot(); dot(); space();
			}
			if (s[i] == '7')
			{
				dash(); dash(); dot(); dot(); dot(); space();
			}
			if (s[i] == '8')
			{
				dash(); dash(); dash(); dot(); dot(); space();
			}
			if (s[i] == '9')
			{
				dash(); dash(); dash(); dash(); dot(); space();
			}
			if (s[i] == '0')
			{
				dash(); dash(); dash(); dash(); dash(); space();
			}
			if (s[i] == ' ')
			{
				_delay_ms(1400); //1400 ms. --- word space
			}
		}
	}
	
}

