#include<string.h>
#include<stdlib.h>
#include<stdio.h>
#include"myHeader.h"
#include"stringManipulation.c"

//#define COMMENT 1

#define MAIN 1


#ifdef MAIN
int main()
{
	NODE *head = NULL,*tail=NULL;
	char *name;
	int position,roll ,mark;
	char ch = '0';
	while(1)
	{
		printf("\nEnter an option:\n1.Insert at Head\n2.Append\n3.Insert at a given position\n4.Delete at Head\n5.Delete at Tail\n");
		printf("6.Delete at given Position\n7.Search\n8.Print the list\n9.Sort\nA.Delete Entire List\n0.Exit\n");
		ch = getchar();
		switch(ch)
		{
			case '1':
				getInputNode(&name,&roll,&mark);
				insertHead(&head,&tail,name,roll,mark);
				free(name);
				break;
			case '2':
				getInputNode(&name,&roll,&mark);
				append(&head,&tail,name,roll,mark);
				free(name);
				break;
			case '3':
				getInputNode(&name,&roll,&mark);
				printf("Position:\n");
				scanf("%d",&position);
				insertAt(&head,&tail,name,roll,mark,position);
				free(name);
				break;
			case '4':
				deleteFirst(&head,&tail);
				break;
			case '6':
				printf("Enter the position to be deleted:\n");
				scanf("%d",&position);
				deleteAt(&head,&tail,position);
				break;
			case '5':
				deleteLast(&head,&tail);
				break;
			case '7':
				searchList(&head,&tail);
				break;
			case '8':
				printList(&head,&tail);
				break;
			case '9':
				sort(&head,&tail);
				break;
			case 'a':
			case 'A':
				deleteList(&head,&tail);
				break;
			case '0':
				deleteList(&head,&tail);
				return 0;
			default:
				printf("Enter the correct option\n");
				break;
		}
		getchar();

	}
	return 0;
}
#endif


