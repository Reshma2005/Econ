//#define COMMENT 0
#define ZERO 48
#define NINE 57
#define REVZERO -128
#define REVNINE -119
#define VALUE 80
#include<stdio.h>
#define RLELENGTH 50
void append(char* des,char* src);
void numberToString(int num,char* str);
int string_length(char* str);
#include<stdlib.h>
#include"stringManipulation.c"
void isNumber(char* ch);
void changeToNumber(char *ch);
char* runLengthEncoding(char* str);
char* runLengthDecoding(char* rle);


int main()
{
        FILE* fptr = fopen("/home/econsys4/Documents/letusc-yashwantkanetkar.pdf","r");
        if(!fptr)
        {
                printf("No such file or directory\n");
                return 0;
	}
        fseek(fptr,0L,SEEK_END);
        int strlen = ftell(fptr);
        rewind(fptr);
        printf("%d\n",strlen);
        char *str = (char*)malloc(strlen+1);
        fread(str,1,strlen,fptr);
        *(str+strlen) = '\0';
	printf("Successfully text read from file: %s\n",str);
	
	char* rle = runLengthEncoding(str);
	free(str);
	strlen = string_length(rle);
	FILE* fptr1 = fopen("/home/econsys4/Reshma/Files/file2.txt","w");
	fwrite(rle,1,strlen,fptr1);
	printf("Successfully written into the file: %s\n",rle);
	fclose(fptr1);
	str = runLengthDecoding(rle);
	printf("Decoded Text: %s\n",str);
	fptr1 = fopen("/home/econsys4/Reshma/Files/file.txt","w");
	fwrite(str,1,strlen,fptr1);
	free(str);
	free(rle);
	str = NULL;
	rle = NULL;
	fclose(fptr);
	fclose(fptr1);
	return 0;
}


char* runLengthEncoding(char* str)
{
	char *tmp,*temp,*rle;
	unsigned char c1,c2,ch;
	rle = (char*)malloc(RLELENGTH);
	*(rle) = '\0';
	temp = (char*)malloc(RLELENGTH);
	*temp = '\0';
	int strlen = string_length(str);
	int i,rleLength = RLELENGTH,count = 1;
	ch = *(str);
	isNumber(&ch);
	for(i=1;i<strlen;i++)
	{
		c1 = *(str+i);
		c2 = *(str+i-1);
		isNumber(&c1);
		isNumber(&c2);
		if(c1 != c2)
		{
			numberToString(count,temp);
			if(string_length(rle) > rleLength-2)
			{
				rleLength = rleLength + RLELENGTH;
				tmp = (char*)realloc(rle,rleLength);
				if(tmp == NULL)
				{
					printf("Realloc Error for Run Length Encoding String\n");
					free(rle);
					return NULL;
				}
				rle = tmp;
			}
			append(rle,temp);
			*(temp) = ch;
			*(temp+1) = '\0';
			append(rle,temp);
			ch = c1;
			count = 1;
		}
		else
		{
			count++;
		}
	}
	return rle;	
}



char* runLengthDecoding(char* rle)
{
	int rlelen = string_length(rle),i,j=0,strlen,strMemLength = RLELENGTH,count;
	char* temp = (char*)malloc(RLELENGTH);
	char* str = (char*)malloc(RLELENGTH);
	char ch,*tmp;
	*(str) = '\0';
	*(temp) = '\0';
	for(i=0;i<rlelen;i++)
	{
		if(*(rle+i) >= '0' && *(rle+i) <= '9')
		{
			*(temp+j++) = *(rle+i);
			*(temp+j) = '\0';
			
		}
		else
		{
			ch = *(rle+i);
			changeToNumber(&ch);
			count = string_to_number(temp);
			strlen = string_length(str);
			if(strlen+count > strMemLength-2)
			{
				strMemLength += RLELENGTH;
				tmp = (char*)realloc(str,strMemLength);
				if(tmp == NULL)
				{
					printf("Realloc Memory error for Decode String\n");
					free(temp);
					free(str);
					return NULL;
				}
				str = tmp;
			}
			
			for(j=0;j<count;j++)
			{
				*(str+j+strlen) = ch;
			}
			*(str+count+strlen) = '\0';
			j = 0;
		}
	}
	return str;
}





void isNumber(char* ch)
{
	if(*ch >= ZERO && *ch <= NINE)
	{
		*ch += VALUE;
	}
}


void changeToNumber(char *ch)
{
	if(*ch >= REVZERO && *ch <= REVNINE)
	{
		*ch -= VALUE;
	}
}
