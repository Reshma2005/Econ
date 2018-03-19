//#include COMMENT 0
#include<stdio.h>
//#define USERINPUT 0
#define FILEINPUT 1
char* append(char* des,char* src);
void numberToString(int num,char* str);
int string_length(char* str);
#include<stdlib.h>



int main()
{
#ifdef FILEINPUT
	int i = 0,count = 1;
	char ch;
        FILE* fptr = fopen("/home/econsys4/Intern/Files/file.txt","r");
        if(!fptr)
        {
                printf("No such file or directory\n");
                return 0;
	}
        fseek(fptr,0L,SEEK_END);
        int strlen = ftell(fptr);
        rewind(fptr);
        char *str = (char*)malloc(strlen+1);
        fread(str,1,strlen,fptr);
#ifdef COMMENT
        printf("No of char: %d,n:%d\n",i,strlen);
#endif
        *(str+strlen) = '\0';
	printf("Successfully text read from file: %s\n",str);

        char *rle = (char*)malloc(1);
        *(rle) = '\0';
        char *temp = (char*)malloc(10);

#endif
#ifdef USERINPUT
	int strlen,i=0,count = 1;
	char ch,*str,*tmp;
	str = (char*)malloc(1);
	char *rle = (char*)malloc(1);
	*(rle) = '\0';
	printf("Enter the string\n");
	char *temp = (char*)malloc(10);
	ch = getchar();
	while(ch != '\n')
	{
		tmp = (char*)realloc(str,(2+i));
		if(tmp != NULL)
		{
			str = tmp;
		}
		*(str+i) = ch;
		i++;
		ch = getchar();
	}
	tmp = NULL;
	*(str+i) = '\0';
	strlen = i+1;
#endif
	ch = *(str);
	for(i=1;i<strlen;i++)
	{
		if(*(str+i) != *(str+i-1))
		{

			numberToString(count,temp);
			rle = append(rle,temp);
			*(temp) = ch;
			*(temp+1) = '\0';
			rle = append(rle,temp);
			ch = *(str+i);
			count = 1;
		}
		else
		{
			count++;
		}
	}
	int strlen1 = string_length(rle);
	FILE* fptr1 = fopen("/home/econsys4/Intern/Files/file2.txt","w");
	fwrite(rle,1,strlen1,fptr1);
	printf("Successfully written into the file: %s\n",rle);
	free(str);
	free(rle);
	free(temp);
	str = NULL;
	rle = NULL;
	temp = NULL;
	fclose(fptr);
	fclose(fptr1);
	return 0;
}
