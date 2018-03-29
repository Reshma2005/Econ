#include<avr/io.h>
#include<stdio.h>
#include<avr/interrupt.h>
ISR(TIMER0_COMP_vect)   // This function is called whenever timer0 compare interupt bit is set
{
        PORTD ^= (1<<0);   //Toggle 0th bit
}
int main()
{
	char count = 0;
        DDRD=0xff;   //Setting portd as output
        TCCR0 = TCCR0 | 0x05;  //prescale as 1024
        PORTD = 0xfe;
        TCNT0=0x00;    //start count
        OCR0 = 255;
	while(1)
        	{
                	while ((TIFR & 0x02) == 0);
			SREG &= 0x7f;
                 	TCNT0 = 0x00;
                 	TIFR=0x02;
                 	count++;
			TIMSK = (1<<1);
                 	if (count>=6)
                 	{
                 	       count=0;
                 	       SREG |= (1<<7);
                 	}

        	}

}
