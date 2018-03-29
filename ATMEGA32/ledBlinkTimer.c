#include<avr/io.h>

int main()
{
	char count=0;
	DDRD=0xff;
	TCNT0=0x00;
	TCCR0 |= 0x05;
	while(1)
	{
		 while ((TIFR & 0x01) == 0);
		 TCNT0 = 0x00;
		 TIFR=0x01;
		 count++;
		 if (count>=3)
		 {
			count=0;
			PORTD ^= (0x01 << 4);
		 }
	}
}

