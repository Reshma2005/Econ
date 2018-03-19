#include<stdio.h>
#include<stdlib.h>
#define TWO 2
#define LENGTH 100
//#define COMMENTS 1
int string_length(char* str) //Calculates the length of the string
{
	int length = 0;
	while(str[length] != '\0')
	{
		length++;
	}
	return length;
}


int string_to_number(char* str) //Converts a string into a number
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
	if(*str == '-' || *str == '+')
	{
		index = 1;
		if(*str == '-')
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

void get_coefficents(char* str,char var[TWO],int coef[TWO],int* constant) //Seperates the coefficients and variables
{

	char *str1 = (char*)malloc(20);
	int i=0,j=0;
	char flag = 0;
	*constant = 0;
	for(i=0;i<=string_length(str);i++)
	{
	if(*(str+i) == '=')
	{
		flag = 1;
	}

		if((*(str+i) >= '0' && *(str+i) <= '9') || (*(str+i) == '+') || (*(str+i) =='-'))
		{
			if(((*(str+i) == '+') || (*(str+i) =='-')) && (*(str+i-1) >= '0' && *(str+i-1) <= '9'))
			{
				str1[j] = '\0';
                                *constant = string_to_number(str1);
                                j = 0;
				*constant *= -1;
			}
			*(str1+j) = *(str+i);
			j++;
#ifdef COMMENTS
	printf("%c\n",*(str1+i));
#endif
		}
		else if(*(str+i) >= 'a' && *(str+i) <= 'z')
		{
			if(!var[0])
			{
				var[0] = *(str+i);
                                *(str1+j) = '\0';
                                j = 0;
				coef[0] = string_to_number(str1);
				if(flag)
				{
					coef[0] *= -1;
				}
#ifdef COMMENTS
	printf("str1:%s, var1:%c, coef1:%d, \n",str1,var[0],coef[0]);
#endif
			}
			else
			{
				var[1] = *(str+i);
				*(str1+j) = '\0';
				j = 0;
				coef[1] = string_to_number(str1);
				if(flag)
				{
					coef[1] *= -1;
				}
#ifdef COMMENTS
	printf("str1:%s, var2:%c, coef2:%d, \n",str1,var[1],coef[1]);
#endif
			}

		}
		else if(*constant == 0)
		{
			if((!(*(str+i-1) >= 'a' && *(str+i-1) <= 'z') && *(str+i) == '=') || (*(str+i) == '\0'))
			{
#ifdef COMMENTS
	printf("str[i]: %c, str1:%s\n",*(str+i),str1);
#endif
				*(str1+j) = '\0';
				*constant = string_to_number(str1);
                        	j = 0;
#ifdef COMMENTS
        printf("constant:%d,\n",*constant);
#endif

				if(flag == 0)
				{
					*constant *= -1;
				}
#ifdef COMMENTS
	printf("constant:%d,\n",*constant);
#endif
			}
		}
	}
	free(str1);
	str1 = NULL;
#ifdef COMMENTS
	printf("\nvar1:%c, var2:%c, coef1:%d, coef2:%d, constant:%d\n",var[0],var[1],coef[0],coef[1],*constant);
#endif
}

void char_swap(char* a,char* b)
{
	char temp = *a;
	*a = *b;
	*b = temp;
}

void int_swap(int* a, int* b)
{
        int temp = *a;
        *a = *b;
        *b = temp;

}

int check_constraints(int coef1[TWO],int coef2[TWO],char var1[TWO],char var2[TWO]) //Checks if variables match
{
	if((var1[0] == var2[1]) || (var1[1] == var2[0]))
	{
		int_swap(&coef1[0],&coef1[1]);
		char_swap(&var1[0],&var1[1]);
	}
	if(((var1[0] == var2[0]) || var1[0] == 0 || var2[0] == 0) && ((var1[1] == var2[1]) || var1[1] == 0 || var2[1] == 0))
	{
		return 1;
	}
	else
	{
		return 0;
	}


}

int solve(int coefficient1[TWO],int coefficient2[TWO],int* constant,double* x_value,double* y_value)//Solves the linear eqn frm given var & const
{

	if(((coefficient2[0]*coefficient1[1])-(coefficient1[0]*coefficient2[1])) == 0 || ((coefficient2[1]*coefficient1[0])-(coefficient1[1]*coefficient2[0])) == 0)
	{
	return 0;
	}

	*y_value =(double) ((coefficient2[0]*constant[0])-(coefficient1[0]*constant[1]))/((coefficient2[0]*coefficient1[1])-(coefficient1[0]*coefficient2[1]));
	*x_value = (double)((coefficient2[1]*constant[0])-(coefficient1[1]*constant[1]))/((coefficient2[1]*coefficient1[0])-(coefficient1[1]*coefficient2[0]));
	printf("\nx:%f y:%f\n",*x_value,*y_value);
	return 1;
}

int main()
{
	int coef1[TWO]={0},coef2[TWO]={0},constant[TWO]={0};
	char *equation1;
	char*equation2;
	char var1[2]={0},var2[2]={0};
	double x_value,y_value;
	equation1 = (char*)malloc(LENGTH);
	equation2 = (char*)malloc(LENGTH);
	printf("Enter Equation1:\n");
	scanf("%[^\n]s",equation1);
	char *temp = (char*)realloc(equation1,(string_length(equation1)));
	if(!temp)
	{
		equation1 = temp;
		temp = NULL;
	}
	printf("Enter Equation2:\n");
	getchar();
	scanf("%[^\n]s",equation2);
	temp = (char*)realloc(equation1,(string_length(equation2)));
	if(!temp)
	{
		equation2 = temp;
	}
	get_coefficents(equation1,var1,coef1,&constant[0]);//Getting coef and const of eq1
	get_coefficents(equation2,var2,coef2,&constant[1]);//Getting coef and const of eq2
	if(check_constraints(coef1,coef2,var1,var2))
	{
		if(solve(coef1,coef2,constant,&x_value,&y_value))
		{
			printf("\nThe value of the unknowns are %c:%.2f and %c:%.2f\n",var1[0],x_value,var1[1],y_value);
			return 0;
		}
	}
	if(!check_constraints(coef1,coef2,var1,var2))
	{
		printf("\nThe variables do not match\n");
		return 0;
	}
	if(!solve(coef1,coef2,constant,&x_value,&y_value))
	{
		printf("\nThe values cannot be determined");
		return 0;
	}
	free(equation1);
	free(equation2);
	equation1 = NULL;
	equation2 = NULL;
	return 0;

}
