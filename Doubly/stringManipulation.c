#include<stdio.h>
//#define COMMENT 1
//#define MAIN 1
#define CASE 32
#include<stdlib.h>
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
	if(!str)
	{
		printf("NULL Pointer Error!!\n");
		return -1;
	}
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

	if(!str1 || !str2)
	{
		printf("NULL Pointer Error!!\n");
		return;
	}
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
	if(!str)
	{
		printf("NULL Pointer Error!!\n");
		return;
	}
	int i,strlength = string_length(str);
        for(i=0;i<strlength;i++)
	{
		if(str[i] >= 'a' && str[i] <= 'z')
		{
			str[i] = str[i] - CASE;
		}
	}
#ifdef COMMENT
	printf("\nAfter Upper:%s\n",str);
#endif
}


int string_to_number(char* str)
{
	if(!str)
	{
		printf("NULL Pointer Error!!\n");
		return 0;
	}
	if(string_length(str) == 0)
	{
	return 1;
	}
	if(string_length(str) == 1)
	{
		if(str[0] == '+')
		{
			return 1;
		}
		else if(str[0] == '-')
		{
			return -1;
		}
	}
	int index = 0,number = 0,flag = 0;
	if(str[0] == '-' || str[0] == '+')
	{
		index = 1;
		if(str[0] == '-')
		{
			flag = 1;
		}
	}

	while(str[index] !='\0')
	{
		number = (number*10) + (str[index]-48);
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
	if(!str1 || !str2)
	{
		printf("NULL Pointer Error!!\n");
		return -1;
	}
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
		if(s1[index] > s2[index])
		{
			free(s1);
			s1 = NULL;
			free(s2);
			s2 = NULL;
			return 1;
		}
		if(s1[index] < s2[index])
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



#ifdef MAIN
int main()
{
	char str1[10] = "Reshma",str2[15] = "Reshma Nanda";
//	str1 = "Reshma";
//	str2 = "REeshma";
	printf("%d\n",stringCompare(str1,str2));
//	printf("%d %d\n",'a','A');
	return 0;

}

#endif

