#include<stdio.h>
//#define COMMENT 1
//#define MAIN 1
#define CASE 32
#include<stdlib.h>
//Declarations
char toUpper(char ch);
int string_length(char* str);
void stringCopy(char* str1,char* str2);
void toUpperCase(char* str);
int string_to_number(char* str);
int stringCompare(char *str1,char* str2);
void stringReverse(char* str);
void numberToString(int num,char* str);
//char* append(char* des,char* src);
//Definitions
char toUpper(char ch)
{
	if(ch >= 'a' && ch <= 'z')
	{
		ch = ch - CASE;
	}
	return ch;
}
int string_length(char* str)
{
	int length = 0;
	while(str[length] != '\0')
	{
		length++;
	}
	return length;
}

void stringCopy(char* str1,char* str2)
{
#ifdef COMMENT
	printf("\nBefore Copy: %s %s\n",str1,str2);
#endif
	int i=0;
	do
	{
		str2[i] = str1[i];
	}while(str1[i++] != '\0');

#ifdef COMMENT
	printf("\nString Copy:%s %s\n",str1,str2);
#endif


}
void toUpperCase(char* str)
{
#ifdef COMMENT
	printf("\nBefore Upper:%s\n",str);
#endif
	int i,strlength = string_length(str);
        for(i=0;i<strlength;i++)
	{
		if(*(str+i) >= 'a' && *(str+i) <= 'z')
		{
			*(str+i) = *(str+i) - CASE;
		}
	}
#ifdef COMMENT
	printf("\nAfter Upper:%s\n",str);
#endif
}


int string_to_number(char* str)
{
	if(string_length(str) == 0)
	{
	return 1;
	}
	if(string_length(str) == 1)
	{
		if(*(str) == '+')
		{
			return 1;
		}
		else if(*(str) == '-')
		{
			return -1;
		}
	}
	int index = 0,number = 0,flag = 0;
	if(*(str) == '-' || *(str) == '+')
	{
		index = 1;
		if(*(str) == '-')
		{
			flag = 1;
		}
	}

	while(*(str+index) !='\0')
	{
		number = (number*10) + (*(str+index)-48);
		index++;
	}

	if(flag)
	{
		number *= -1;
	}

	return number;

}

int stringCompare(char *str1,char* str2)
{
	int index,minlength,s1length = string_length(str1),s2length = string_length(str2);
	char *s1,*s2;
	s1 = (char*)malloc(s1length);
	s2 = (char*)malloc(s2length);
	stringCopy(str1,s1);
	stringCopy(str2,s2);
	toUpperCase(s1);
	toUpperCase(s2);
	if(!(s1length == s2length))
	{
		if(s1length>s2length)
		{
			minlength = s2length;
		}
		else
		{
			minlength = s1length;
		}
	}
	else
	{
		minlength = s1length;
	}
	for(index = 0;index <= minlength;index++)
	{
		if(*(s1+index) > *(s2+index))
		{
			free(s1);
			s1 = NULL;
			free(s2);
			s2 = NULL;
			return 1;
		}
		if(*(s1+index) < *(s2+index))
		{
		       	free(s1);
			s1 = NULL;
                        free(s2);
			s2 = NULL;
			return -1;
		}
	}
	free(s1);
	free(s2);
	s1 = NULL;
	s2 = NULL;

	return 0;
}

void stringReverse(char* str)
{
	int i = 0,n = string_length(str);
	char ch;
	while(i < (n/2))
	{
		ch = *(str+i);
		*(str+i) = *(str-i-1+n);
		*(str-i-1+n) = ch;
		i++;
	}
}

void numberToString(int num,char* str)
{
	int rem,i=0;
	do
	{
		rem = num % 10;
		*(str+i) = (char)(rem +48);
#ifdef COMMENT
		printf("%c",(rem+48));
#endif
		i++;
		num = num/10;
	}while(num != 0);
	*(str+i) = '\0';
#ifdef COMMENT
	printf("\nNTS:%s\n",str);
#endif
	stringReverse(str);
}
#ifdef MAIN
char* append(char* des,char* src)
{
	int i,n1 = string_length(des),n2 = string_length(src);
	char *temp = (char*)realloc(des,(n1+n2));
	if(!temp)
	{
		des = temp;
	}
	for(i = n1;i<(n1+n2);i++)
	{
		*(des+i) = *(src+i-n1);
	}
	*(des+i) = '\0';
	return des;
	temp = NULL;
}


int main()
{
	int a = 8567856;
	char *me,*dad;
	me = (char*)malloc(7);
	dad = (char*)malloc(11);
//	printf("%s\n",s);
//	numberToString(a,s);
	scanf("%s %s",me,dad);
	printf("me:%s dad:%s\n",me,dad);
	append(me,dad);


	printf("me:%s\n",me);
	return 0;

}


#endif
