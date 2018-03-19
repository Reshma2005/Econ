#include<stdio.h>
#define MAX 32
void decimal_to_binary(int,unsigned int[]);

void decimal_to_binary(int decimal,unsigned int* binary)
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
                        printf("%u",binary[iterate]);
                }
		printf("\n");
}




void binary(int x)
{
int i,eg,k;
for(i=31;i>=0;i--)
{
eg=1<<i;
k=x&eg;
k==0?printf("0 "):printf("1 ");
}
printf("\n");
}
struct check
{
int bit1 : 1;
int bit2 : 4;
int bit3 : 5;
}st={1,15,31};
int main()
{
unsigned int bin[MAX];
printf("%d %d %d\n",st.bit1,st.bit2,st.bit3);
decimal_to_binary(st.bit1,bin);
decimal_to_binary(st.bit2,bin);
decimal_to_binary(st.bit3,bin);

//printf("\nbinary\n");
//binary(st.bit1);
//binary(st.bit2);
//binary(st.bit3);
printf("%d\n",sizeof(st));
}
