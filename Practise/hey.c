#include<stdio.h>
#include<stdlib.h>
#include"stringManipulation.c"
int string_length(char* str);
int main()
{
	char *str = (char*)malloc(50);
	scanf("%[^\n]s",str);
	printf("%d\n",string_length(str));
	printf("%s\n",str);
	return 0;
}
