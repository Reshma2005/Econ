#define THREE 1
#include<stdlib.h>
#include<stdio.h>
int main()
{
#ifdef ONE
	int i = 0;
	int memory_alloc_fail = 0;
	char **dptr = (char**)malloc(5*sizeof(char*));
	if(!dptr)
		return 0;
	while(i < 5)
	{
		dptr[i] = NULL;
		dptr[i] = (char*)malloc(20*sizeof(char));
		if(!dptr[i])
		{
			memory_alloc_fail = 1;
			break;
		}
		*((int*)dptr[i]) = 0x00 | (0x41 + i*2) << 16 | (0x42 + i*2) << 8 | (0x43 + i*2);
		printf("i: %s \n",dptr[i]);
		i++;
	}

	if(!memory_alloc_fail)
	{
		printf("%c\n",**dptr);
		printf("%c\n",**dptr+3);
		printf("%c\n",*(*dptr)+1);
		printf("%c\n",(*(*dptr+1)));
		printf("%c\n",*dptr[2]);
		printf("%c\n",*dptr[1]+2);
		printf("%c\n",**(dptr+2));
	}

	i = 0;
	while(i < 5)
	{
		if(dptr[i])
		{
			free(dptr[i]);
			dptr[i++] = NULL;
		}

	}
	free(dptr);
#endif
#ifdef THREE
	int *i = (int*)calloc(2,sizeof(int));
	char *c = (char*)calloc(8,sizeof(char));

	*c = 1;
	i = (int*)c;
	printf("0x%x 0x%x 0x%x 0x%x\n",*i,*i+1,*c,*(c+1));

	*i = '1';
	c = (char*)i;
	printf("0x%x 0x%x 0x%x 0x%x\n",*i,*(i+1),*c,*c+1);

#endif
	return 0;
}
