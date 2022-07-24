
#define F_CPU 16000000UL

#include <avr/io.h>
#include <avr/interrupt.h>

void adc_init(void)
{
	ADMUX |= (1 << REFS0) | (1 << MUX2); //VCC, from datasheet
	ADCSRA |= (1 << ADEN) | (1 << ADATE) | (1 << ADIE) | (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0); //Enable ADC Auto Trigger & Conversion Complete Interrupt
	ADCSRB |= (1 << ADTS1) | (1 << ADTS0); //Compare Match
}

void timer_0 ()
{
	TCCR0A |= (1 << WGM01); //CTC mode
	OCR0A = 139; //Max value for duty cycle period
	TCCR0B |= (1 << CS02); //9 ms -> prescaler = 1024
	TIMSK0 |= (1 << OCIE0A); //Enabling compare match A Interrupt
}

void timer_2 ()
{
	TCCR2A |= 1 << WGM21; //CTC mode
	OCR2A = 207; //Max value for duty cycle period
	TCCR2B |= (1 < CS22); //3.33ms -> prescaler = 256
	TIMSK2 |= (1 << OCIE2A) | (1 << OCIE2B); //Enabling compare match A & B Interrupts
}

ISR(ADC_vect)
{
	uint16_t variable = ADC;
	OCR2B = ((variable) / 1024.0) * 207; //passed to OCR1B
}

ISR (TIMER2_COMPA_vect)
{
	if (OCR2B > 0)
	PORTB |= (1 << 5);
}

ISR (TIMER2_COMPB_vect)
{
	PORTB &= ~(1 << 5);
}

int main(void)
{ 
	DDRC &= ~(1 << PINC4);
	DDRB |= (1 << DDB5);
	
	cli();
	
	adc_init();
	timer_0();
	timer_2();
	sei();
	
    while (1) 
    {
    }
}

