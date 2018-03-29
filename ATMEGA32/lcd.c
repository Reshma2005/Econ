#include"lcd.h"
//#define MAIN 1

void lcdInit()
{
	PORTD &= ~(1 << RW);
        lcdCommand(bit8line2);
        lcdCommand(disONcurON);
        lcdCommand(CLEAR);
        lcdCommand(entrymode);

}


void lcdCommand(char cmd)      //Write command to lcd
{
	PORTA = cmd;
	PORTD &= ~(1<<RS);//Command mode
	PORTD |= (1 << EN);//Enable high
	_delay_us(10);
	PORTD &= ~(1<<EN);//Enable low
	_delay_ms(2);

}

void lcdData(char data)   //Write Data to lcd
{
	PORTA = data;
        PORTD |= (1 << RS);//Data mode
        PORTD |= (1 << EN);//Enable high
        _delay_us(10);
        PORTD &= ~(1<<EN);//Enable low
        _delay_ms(2);
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
	if(PORTD & (1 << PD1) != 0)
	{
		break;
	}

}
}

void scrollRight(char *str)    //scroll right
{
	//lcdWriteString(str);
	unsigned char n = DISPLAYSIZE;
	while(n)
	{
		_delay_ms(500);
		lcdCommand(right);
		n--;
	}
while(1)
{
	n = DDRAMSIZE - DISPLAYSIZE - strlen(str);
	while(n)
	{
		lcdCommand(right);
		n--;
	}
	n = DISPLAYSIZE + strlen(str);
	while(n)
	{
		_delay_ms(500);
		lcdCommand(right);
		n--;
	}
	if(PORTD & (1 << PD0) != 0)
	{
		break;
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
void lcdWriteString(char *str)
{
	int i = 0;
	while(str[i] != '\0')
	{
		lcdData(str[i++]);
//		_delay_ms(1000);
	}
}


#ifdef MAIN
int main()
{

	DDRA = 0xff;
	DDRD |= (1<<PD7) | (1<<PD6) | (1<<PD5);//pins for EN RS RW

	DDRD &= ~(1 << PD0);
	DDRD &= ~(1 << PD1);
	PORTD &= ~(1 << RW);  //Write mode
	char flag = 0;
	lcdCommand(bit8line2);
	lcdCommand(disONcurON);
	lcdCommand(CLEAR);
	lcdCommand(entrymode);
	lcdWriteString("Hello World!");
	while(1)
	{
		if(!((PIND & (1 << PD0)) == (1 << PD0)))
		{

			if(flag)
			{
			lcdCommand(CLEAR);
			firstLine();
			lcdWriteString("Hello World!");
			}
			flag = 0;
		}
		if(!((PIND & (1 << PD1)) == (1 << PD1)))
		{
			if(flag == 0)
			{
			lcdCommand(CLEAR);
			secondLine();
			lcdWriteString("Hello World!");
			}
			flag = 1;
		}
	}

}
#endif
