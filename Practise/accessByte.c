#include<stdio.h>

#ifdef COMMENTS
struct s
        {
                int a[4] : 8;
//                int b : 8;
//                int c : 8;
//                int d : 8;
        }s1;


int main()
{
	printf("%lu\n",sizeof(s1));
	return 0;
}



union integer
{
	int a;
	char b[4];
}i;
#endif
#define MAX 8
void decimal_to_binary(char decimal)
{
		int iterate = MAX-1,binary[MAX] = {0};
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



union integer
{
	int a1;
	struct s
	{
		int a : 8;
		int b : 8;
		int c : 8;
		int d : 8;
	}s1;
}i;

int main()
{
	int j;
	printf("Enter the integer:");
	scanf("%d",&i.a1);
	printf("\nEnter the byte to be accessed:");
	scanf("%d",&j);
	if(j == 1)
	{
		decimal_to_binary(i.s1.a);
	}
	if(j == 2)
        {
                decimal_to_binary(i.s1.b);
        }
	if(j == 3)
        {
                decimal_to_binary(i.s1.c);
        }
	if(j == 4)
        {
                decimal_to_binary(i.s1.d);
        }

	return 0;
}
