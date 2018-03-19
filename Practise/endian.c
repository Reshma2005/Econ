#include<stdio.h>
int main()
{
	int number = 0x41424344;
	char* char_pointer = (char*)(&number);
	int i = 0;
	/*for(i=0;i<4;i++)
	{
		printf("%d\n",char_pointer[i]);
	}*/
	if(char_pointer[0] < char_pointer[3])
	{
		printf("The compiler is Big Endian\n");
	}
	else
	{
		printf("The compiler is Little Endian\n");
	}
	return 0;
}
