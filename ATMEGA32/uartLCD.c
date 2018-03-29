#include"uart.h"
void lcdInit()
{
	PORTB &= ~(1 << RW);
        lcdCommand(bit8line2);
        lcdCommand(disONcurON);
        lcdCommand(CLEAR);
        lcdCommand(entrymode);

}


void lcdCommand(char cmd)      //Write command to lcd
{
	PORTA = cmd;
	PORTB &= ~(1<<RS);//Command mode
	PORTB |= (1 << EN);//Enable high
	_delay_us(10);
	PORTB &= ~(1<<EN);//Enable low
	_delay_ms(2);

}

void lcdData(char data)   //Write Data to lcd
{
	PORTA = data;
        PORTB |= (1 << RS);//Data mode
        PORTB |= (1 << EN);//Enable high
        _delay_us(10);
        PORTB &= ~(1<<EN);//Enable low
        _delay_ms(2);
}

void lcdWriteString(char *str)
{
        int i = 0;
        while(str[i] != '\0')
        {
                lcdData(str[i++]);
//              _delay_ms(1000);
        }
}

void scrollLeft(char* str)    // Scroll left
{
	//lcdWriteString(str);
	unsigned char n = strlen(str);
	while(n)
	{
		_delay_ms(500);
		lcdCommand(left);
		n--;
	}
while(1)
{
	n = DDRAMSIZE - strlen(str) - DISPLAYSIZE;
	while(n)
	{
		lcdCommand(left);
		n--;
	}
	n = DISPLAYSIZE + strlen(str);
	while(n)
	{
		_delay_ms(500);
		lcdCommand(left);
		n--;
	}

}
}

void firstLine()
{
	lcdCommand(line1);
}

void secondLine()
{
	lcdCommand(line2);
}

uartChoice(char flag)
{
	lcdInit();
	if(flag)
	firstLine();
	else
	secondLine();
	lcdWriteString("Hello World");

}

