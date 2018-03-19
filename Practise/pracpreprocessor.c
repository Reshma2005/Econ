#include<stdlib.h>
#include<stdio.h>
int string_to_number(char*);
#pragma pack(1)
struct st
{
	char a[2];
	int b;
	char c;
};

int main(int argc,char* argv[])
{

	int* a = (int*)malloc((argc-1)*sizeof(int));
	int i;
	for(i=1;i<argc;i++)
	{
		a[i-1] = string_to_number(argv[i]);
		printf("%d \n",a[i-1]);
	}


	return 0;
}
