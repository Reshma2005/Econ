#include<stdio.h>

int main() {
struct value
{
int bit1 : 1;
int bit3 : 4;
int bit4 : 5;
}bit={1, 2, 13};
printf(“%d, %d, %d\n”, bit.bit1, bit.bit3, bit.bit4);
printf("%lu\n",sizeof(bit));
return 0;
}
/*



//void hi();

struct Test {
char a;
int b;
};
void func(struct Test* t){
t->a=5;
t->b=100;
}


struct s
{
	char x;
//	char *a;
//	int b[2];
//	char c;
	int d;
//	int *e;
};
union Tmest{
int four_char;
struct structure_test{
char first_char;
char second_char;
char third_char;
}ut;
}test;

union TTest{
int four_char;
char first_char;
char second_char;
char third_char;
};

union z
{
//	char r;
	int s;
	char r[4];
};
typedef union z Z;
typedef struct s S;

//int main()
//{
//		extern int x;
//printf("%d\n",x);
//hi();
//x++;
//printf("%d\n",x);

//	int a[10]={0};
//	printf("%d",a[0]);
//	int *b = (int*)malloc(sizeof(int));
//int *a;
//printf("%d\n",*a);

//int a = '9' + 0;
//printf("%d\n",a);
//	S a1;
//	Z i;
//	i.s = 0x41424344;
//	printf("%x %c %c %c %c\n",i.s,i.r[0],i.r[1],i.r[2],i.r[3]);
//	int *ptr;
//	printf("struct:%lu  %x %x\n",sizeof(a1),&a1.x,&a1.d);

//	printf("%lu\n",sizeof(a1));

//	unsigned int a = 1758122968;
//	printf("%.2f\n",a);

//enum boolean {wrong=-1,correct};
//enum boolean b1;
//printf("%lu %lu \n",sizeof(correct),sizeof(b1));

//struct Test test;
//func(&test);
//printf("%d\n",test.b);

//test.four_char=0x41424344;
//printf("%c %c %c \n",test.first_char,test.second_char,test.third_char);
//test.four_char=0x41424344;
//printf("%c %c %c \n",test.ut.first_char,test.ut.second_char,test.ut.third_char);



*/
