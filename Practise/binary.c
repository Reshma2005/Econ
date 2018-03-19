#include<stdio.h>
int main()
{
	int binary[16]={0},n=0,i=0,decimal,count = 0;
	while(1)
{
	n=0;
	i=0;
	count = 0;
	for(i=0;i<16;i++)
	{
		binary[i] = 0;
	}
	printf("Enter the decimal:\n");
	scanf("%d",&decimal);
	do
	{
		binary[n++] = decimal%2;
		decimal = decimal/2;
	}while(decimal > 0);
	for(i=1;i<n;i++)
	{
		if(binary[i] != binary[i-1])
		{
			count++;
		}
	}
	for(i=n-1;i>=0;i--)
	{
		printf("%d",binary[i]);
	}
	printf("\nCount : %d",count);
	printf("\nExit? Yes:1 No:0\n");
	scanf("%d",&i);
	if(i == 1)
	{
		break;
	}
}
	return 0;
}
