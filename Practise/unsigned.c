#include<stdio.h>
int main()
{
	int i = 0;
	unsigned char ch = 0;
	for(i=0;i<256;i++)
	{
		printf("%x ",ch);
		ch++;
	}
	printf("\n");
}
