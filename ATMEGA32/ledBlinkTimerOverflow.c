#include<avr/io.h>
#include<stdio.h>
#include<avr/interrupt.h>

/*
Blinking LED using Timer overflow interrupt
*/

ISR(TIMER0_OVF_vect)// This function is called whenever timer0 overflow interupt bit is set
{
        PORTD ^= (1<<0);//Toggle 0th bit
        TCNT0=0x00;//restart count
}
int main()
{
        DDRD=0xff;
        TCCR0 = TCCR0 | 0x05;//set prescale value 1024
        PORTD = 0xfe;
        TCNT0=0x00;//start count
        TIMSK = (1<<0);//set timer0 overflow interupt bit
        SREG |= 0x80;//enable global interrupt flag
        while(1)
        {
        }
}

