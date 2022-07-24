
#define F_CPU 16000000UL //16 MHz clock

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>


volatile uint8_t dutyCycle = 0;

void timer_0 ()
{
	TCCR0A |= (1 << WGM01); //CTC mode
	OCR0A = 139; //Max value for duty cycle period 
	TCCR0B |= (1 << CS02) | (1 << CS00); //9 ms -> prescaler = 1024
	TIMSK0 |= (1 << OCIE0A); //Enabling compare match A Interrupt
}

void timer_2 ()
{
	TCCR2A |= 1 << WGM21; //CTC mode
	OCR2A = 207; //Max value for duty cycle period 
	TCCR2B |= (1 < CS22); //3.33ms -> prescaler = 256
	TIMSK2 |= (1 << OCIE2A) | (1 << OCIE2B); //Enabling compare match A & B Interrupts
}

ISR (TIMER0_COMPA_vect) //Scan keypad
{
 char keyChar[4][4] = {{'1', '2', '3', 'A'}, {'4', '5', '6', 'B'}, {'7', '8', '9', 'B'}, {'*', '0', '#', 'D'}}; //Keypad matrix
	for (int i = 0; i < 4; i++) //Scan through rows
	{
		PORTD &= ~(1 << (i + 4));
		for (int j = 0; j < 4; j++) //Scan through columns
		{
			if (!(PINB & (1 << (j))))
			dutyCycle = (keyChar[i][j]);
		}
		PORTD |= (1 << (i + 4));
	}
}

ISR (TIMER2_COMPA_vect)
{
	PORTB |= (1 << 5);
}

ISR (TIMER2_COMPB_vect)
{
	PORTB &= ~(1 << 5);
}

int main(void)
{	
	DDRD |= (1 << DDD4) | (1 << DDD5) | (1 << DDD6) | (1 << DDD7); //Rows as output, specifically PDx
	DDRB &= ~(1 << DDB0) & ~(1 << DDB1) & ~(1 << DDB2) & ~(1 << DDB3); //Columns as inputs, specifically PBx
	PORTB |= (1 << PORTB0) | (1 << PORTB1) | (1 << PORTB2) | (1 << PORTB3); //Enable pull-up resistors in columns
	PORTD |= (1 << 4 | 1 << 5 | 1 << 6 | 1 << 7); //Rows high
	DDRB |= (1 << PORTB5); //Output
	
	timer_0();
	timer_2();
	sei();
	
    while (1) 
    {
		OCR2B = (dutyCycle / 10.0) * OCR2A;	
    }
}

