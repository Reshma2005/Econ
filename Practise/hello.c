#include<stdio.h>

int main()
{
	void *ptr;
	int str[10];
	ptr = &(str[0]);
	printf("%x %x %x\n",ptr,ptr+1,ptr+2);

	return 0;
}
