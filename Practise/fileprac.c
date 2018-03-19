#include<stdio.h>
#include<string.h>
#include<stdlib.h>
char* append(char* des,char* src);
int main()
{
	char c;
	int i = 1,j=1;
	FILE* fptr = fopen("/home/econsys4/Intern/Files/xmlPractise.txt","r");
	if(!fptr)
	{
		printf("No such file or directory\n");
		return 0;
	}
	fseek(fptr,0L,SEEK_END);
	int n = ftell(fptr);
	rewind(fptr);
	char *str = (char*)malloc(n);
	i = fread(str,1,n,fptr);
	printf("No of char: %d,n:%d\n",i,n);
	*(str+n) = '\0';
	printf("%s",str);




/*
	char *ch = &c;
	char *tmp;
	char *str = (char*)malloc(2);
	*(str) = '\0';
	i = fread(ch,1,1,fptr);
	while(i == 1)
	{
		printf("%d %s\n",j,str);
		str = append(str,ch);
		*(str+j) = '\0';
		j++;
		i = fread(ch,1,1,fptr);
	}

	*(str) = *(ch);
	while(*ch != EOF)
        {
                tmp = (char*)realloc(str,(2+i));
                if(tmp != NULL)
                {
                        str = tmp;
                }
		fread(ch,1,1,fptr);
                *(str+i) = *ch;
                i++;
        }


	while(ftell(fptr) != SEEK_END)
	{
		printf("\nInside while\n");
		str = (char*)realloc(str,(2+i));
		fread((str+i),1,1,fptr);
		i++;
	}
*/
//	*(str+i) = '\0';
//	printf("Final:%s\n",str);
	fclose(fptr);
	fptr = fopen("/home/econsys4/Intern/Files/xmlParsed.txt","w");
	fwrite(str,1,strlen(str),fptr);
	free(str);
	fclose(fptr);
	return 0;
}
