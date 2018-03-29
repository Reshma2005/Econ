#include<avr/io.h>
#include<avr/interrupt.h>

/*
Blinking LED using Timer compare interrupt
*/

ISR(TIMER0_COMP_vect)   // This function is called whenever timer0 compare interupt bit is set
{
	PORTD ^= (1<<0);   //Toggle 0th bit
	TCNT0=0x00;    //restart count
}
int main()
{
	DDRD=0xff;   //Setting portd as output
        TCCR0 = TCCR0 | 0x05;  //prescale as 1024
	PORTD = 0xfe;
	TCNT0=0x00;    //start count
	OCR0 = 196;
	TIMSK = (1<<1);   //set timer0 compare interupt bit
	SREG |= 0x80;    //enable global interrupt flag
	while(1)
	{
	}
}
