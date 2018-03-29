#define F_CPU 1000000U
#include"uartLCD.c"
/***************************************************************************************************************************************************

UART Program
Get data in UART and display in LCD
Pin Configuration: 
PD0: UART RXD
PB5: LCD EN
PB6: LCD RW
PB7: LCD RS
PINA: LCD D0..7



***************************************************************************************************************************************************/


void uartInit(uint16_t baud)
{
	/* Set baud rate */
	UBRRH = (baud>>8);
	UBRRL = baud;
	/* Enable receiver*/
	UCSRA = (1<<U2X);
	UCSRB = (1<<RXEN) | (1 << TXEN);
	/* Set frame format: 8data, 1 stop bit */
	UCSRC = (1<<URSEL)|(1<<UCSZ0)|(1<<UCSZ1);
}

char uartReceive()
{
	/* Wait for data to be received */
//	lcdWriteString("uartRecieve()");
	while (!(UCSRA & (1<<RXC)));
	/* Get and return received data from buffer */
//	lcdInit();
	if((UCSRA & (1<<FE)))
		lcdData('F');

	if((UCSRA & (1<<DOR)))
		lcdData('D');

	if((UCSRA & (1<<PE)))
		lcdData('P');
	return UDR;
}

void uartTransmit(char data)
{
   //Wait untill the transmitter is ready

   while(!(UCSRA & (1<<UDRE)));

   //Now write the data to USART buffer

   UDR=data;
}

#ifdef MAIN
int main()
{
	DDRA = 0xff;
	DDRB |= (1 << PB5) | (1 << PB6) | (1 << PB7);
	DDRD &= ~(1 << PD0);
	DDRD |= (1 << PD1);
	char ch;
	uartInit(25);
	lcdInit();
	char flag = 1;
	uartChoice(flag);
	while(1)
	{
		ch = uartReceive();
		uartTransmit(ch);
		switch(ch)
		{
			case 'a':
			case 'A':
				if(flag != 1)
				{
					flag = 1;
					uartChoice(flag);
				}
				break;
			case 'b':
			case 'B':
				if(flag != 0)
                                {
                                        flag = 0; 
                                        uartChoice(flag); 
                                }
				break;
		}
	}

}
#endif
