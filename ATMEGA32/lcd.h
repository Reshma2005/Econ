#include<avr/io.h>
#include<avr/interrupt.h>
#define F_CPU 1000000U
#include<util/delay.h>
#include<string.h>
#define EN 7
#define RW 6
#define RS 5
#define DDRAMSIZE 40
#define DISPLAYSIZE 16

#define CLEAR 0x01
#define bit8line2 0x38
#define entrymode 0x06
#define disONcurON 0x0e
#define right 0x1c
#define left 0x18
#define line1 0x80
#define line2 0xc0

void lcdCommand(char cmd);
void lcdData(char data);
void scrollLeft(char* str);
void scrollRight(char *str);
void firstLine();
void secondLine();
void lcdWriteString(char *str);
