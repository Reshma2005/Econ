#include"uart.c"
#define slaveWrite 0xa0
#define slaveRead 0xa1
#include"24c64.c"



void i2cInit()
{
    TWSR=0x00; //set presca1er bits to zero
    TWBR=5; //SCL frequency is 10K
    TWCR=0x04; //enab1e TWI module
}


void i2cStart()
{
	TWCR = ((1<<TWINT) | (1<<TWSTA) | (1<<TWEN));
	while (!(TWCR & (1<<TWINT)));
	_delay_us(10);

}

void i2cStop(void)
{
	TWCR = ((1<< TWINT) | (1<<TWEN) | (1<<TWSTO));
	_delay_us(100); //wait for a short time
}

void i2cWrite(char byte)
{
	TWDR = byte;
	TWCR = ((1<< TWINT) | (1<<TWEN));
	while (!(TWCR & (1 <<TWINT)));
}

char i2cRead()
{

	TWCR = ((1<< TWINT) | (1<<TWEN) | (1<<TWEA));
	while ( !(TWCR & (1 <<TWINT)));
	return TWDR;
}

void i2cEEpromWrite(char data,char RegisterAddress)
{
	i2cStart();
	i2cWrite(slaveWrite);
	i2cWrite(RegisterAddress);
	i2cWrite(data);
	i2cStop();
}

char i2cEEpromRead(char registerAddress)
{
	char data;
	i2cStart();
	i2cWrite(slaveWrite);
	i2cWrite(registerAddress);
	i2cStart();
	i2cWrite(slaveRead);
	data = i2cRead();
	i2cStop();
	return data;
}

int main()
{
        DDRA = 0xff;//LCD data input pins
        DDRB |= (1 << PB5) | (1 << PB6) | (1 << PB7);//LCD EN RS RW
        DDRD &= ~(1 << PD0);//UART Receiver
        DDRD |= (1 << PD1);//UART Transmitter
	DDRC |= (1 << PC0) | (1 << PC1);//I2C SCL and SDA
	char ch;
        uartInit(12);
        lcdInit();
//	i2cInit();
	EEOpen();
        while(1)
        {
                ch = uartReceive();
                uartTransmit(ch);
		firstLine();
		lcdData(ch);
		i2cEEpromWrite(ch,0x00);
		ch = i2cEEpromRead(0x00);
		secondLine();
		lcdData(ch);
	}
}
