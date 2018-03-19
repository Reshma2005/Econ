#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define MAX 3
int solve(int*,int*,double*,double*); //Solves the linear equation
int string_length(char*); //Give the string Length
void get_coefficients(char*, int*,char*,char*); //Gives the constant and coefficient of the eqn str
int string_to_number(char*); // converts a string to number
int main()
{
	int coefficient1[MAX],coefficient2[MAX];
	double x_value,y_value;
	char equation1[50],equation2[50],var_x1=0,var_y1=0,var_x2=0,var_y2=0;
	printf("Enter The two equations in the form: Ax+By=C\n");
	scanf("%s",equation1);
	scanf("%s",equation2);
	get_coefficients(equation1,coefficient1,&var_x1,&var_y1);
	get_coefficients(equation2,coefficient2,&var_x2,&var_y2);

	if(solve(coefficient1,coefficient2,&x_value,&y_value))
	{
		printf("The value of x and y cannot be determined\n");
		return 0;
	}
	printf("The value of the unknowns are %c:%.2f and %c:%.2\n",var_x1,x_value,var_y1,y_value);
	return 0;
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

int string_to_number(char* str)
{
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


void get_coefficients(char* equation,int* coefficient,char* var_x,char*var_y)
{
//	printf("1\n");
//	char str[] = "-2x-3y=-10";
	int index1 = 1,index2 = 0;
	char str1[9];
//	printf("1\n");
	while(equation[index1] != '=')
	{
		index++;
	}
	equation[index1] = '\0';
	index1++;

	while(equation[index1] != '\0')
        {
                str1[index2++] = equation[index1++]; 
        }
        str1[index2] = '\0';
        printf("constant:%s\n",str1);

//        coefficient[2] = string_to_number(str1);

//        printf("c:%d\n",coefficient[2]);

	index1 = 1;
	while(equation[index1] != '+' && equation[index1] != '-')
	{

		if(equation[index1] == '\0')
		{
			*no_of_var = 1;
			var_name = equation[index1-1];
			str1[index2] = '\0';
			coefficient1[0] = string_to_number(str1);
			coefficient1[1] = 0;
			printf("Single coefficient\n");
			return 0;
		}
//		printf("1\n");
		str1[index2++] = equation[index1-1];
		index1++;
	}

	printf("%s\n",str1);
	*var_x = equation[index1-1];
	str1[index2] = '\0';
	printf("x:%s\n",str1);
	coefficient[0] = string_to_number(str1);


	printf("a:%d\n",coefficient[0]);

	index1++;
	index2 = 0;
	while(equation[index1] != '=')
	{
		str1[index2++] = equation[index1-1];
		index1++;
	}
	
	label: *var_y = equation[index1-1];
//	printf("hey!    ,%c,   ,%c,\n",x,y);
	str1[index2] = '\0';

	printf("y:%s\n",str1);

	coefficient[1] = string_to_number(str1);

	printf("b:%d\n",coefficient[1]);

	index1++;
	index2 = 0;
	while(equation[index1] != '\0')
	{
		str1[index2++] = equation[index1++]; 
	}
	str1[index2] = '\0';
	printf("constant:%s\n",str1);

	coefficient[2] = string_to_number(str1);

	printf("c:%d\n",coefficient[2]);

}

int solve(int* coefficient1,int* coefficient2,double* x_value,double* y_value)
{

	if(((coefficient2[0]*coefficient1[1])-(coefficient1[0]*coefficient2[1])) == 0 || ((coefficient2[1]*coefficient1[0])-(coefficient1[1]*coefficient2[0])) == 0)
	{
	return 1
	}

	*y_value = ((coefficient2[0]*coefficient1[2])-(coefficient1[0]*coefficient2[2]))/((coefficient2[0]*coefficient1[1])-(coefficient1[0]*coefficient2[1]));
	*x_value = ((coefficient2[1]*coefficient1[2])-(coefficient1[1]*coefficient2[2]))/((coefficient2[1]*coefficient1[0])-(coefficient1[1]*coefficient2[0]));
//	print
	return 0;
}
