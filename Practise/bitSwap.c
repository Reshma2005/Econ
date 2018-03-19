#include<stdio.h>
#define MAX 32
void decimal_to_binary(int,int[]);
void swap(int* number1,int*);
int binary_to_decimal(int[]);
int main()
{
        int binary[MAX]={0};
	int iterate,decimal,quit,position1,position2;
        while(1)
	{
		printf("Enter the decimal:\n");
                scanf("%d",&decimal);
		decimal_to_binary(decimal,&binary[0]);
      		printf("\nEnter the positions to be swapped:\n");
		scanf("%d %d",&position1,&position2);
		swap(&binary[position1],&binary[position2]);
		for(iterate=0;iterate<MAX;iterate++)
                {
                        printf("%d",binary[iterate]);
                }

		printf("\nThe swapped decimal: %d\n",binary_to_decimal(&binary[0]));
		printf("\nExit? Yes:1 No:0\n");
        	scanf("%d",&quit);
        	if(quit == 1)
        	{
        	        break;
        	}
	}
	return 0;
}

void decimal_to_binary(int decimal,int* binary)
{
		int iterate = MAX-1;
        	for(iterate=0;iterate<MAX;iterate++)
                {
                        binary[iterate] = 0;
                }
                iterate = MAX-1;
                do
                {
                        binary[iterate--] = decimal%2;
                        decimal = decimal/2;
                }while(decimal > 0);
                for(iterate=0;iterate<MAX;iterate++)
                {
                        printf("%d",binary[iterate]);
                }
}

void swap(int* number1,int* number2)
{
	int temp = *number1;
	*number1 = *number2;
	*number2 = temp;
}

int binary_to_decimal(int* binary)
{
	int decimal=0,two = 1,iterate=MAX-1;
	for(iterate = MAX-1;iterate>=0;iterate--)
	{
		decimal += (binary[iterate]*two);
		two *= 2;
	}
	return decimal;
}
