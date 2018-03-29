
#include"uartLCD.c"
void USARTInit(uint16_t ubrr_value)
{

   //Set Baud rate

   UBRRL = ubrr_value;
   UBRRH = (ubrr_value>>8);

   /*Set Frame Format


   >> Asynchronous mode
   >> No Parity
   >> 2 StopBit

   >> char size 8

   */

   UCSRC=(1<<URSEL)|(3<<UCSZ0)|(1<<USBS);


   //Enable The receiver and transmitter

   UCSRB=(1<<RXEN)|(1<<TXEN);


}


//This function is used to read the available data
//from USART. This function will wait untill data is
//available.
char USARTReadChar()
{
   //Wait untill a data is available

   while(!(UCSRA & (1<<RXC)))
   {
      //Do nothing
   }

   //Now USART has got data from host
   //and is available is buffer

   return UDR;
}


//This fuction writes the given "data" to
//the USART which then transmit it via TX line
void USARTWriteChar(char data)
{
   //Wait untill the transmitter is ready

   while(!(UCSRA & (1<<UDRE)))
   {
      //Do nothing
   }

   //Now write the data to USART buffer

   UDR=data;
}

void main()
{
   //This DEMO program will demonstrate the use of simple

   //function for using the USART for data communication

   //Varriable Declaration
   char data;

   /*First Initialize the USART with baud rate = 19200bps
   
   for Baud rate = 1bps

   UBRR value = 6

   */

   USARTInit(6);    //UBRR = 6

   //Loop forever

   while(1)
   {
      //Read data
      data=USARTReadChar();
      USARTWriteChar(data);

   }
}
