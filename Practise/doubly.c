#include<string.h>
#include<stdlib.h>
#include<stdio.h>
#include"myHeader.h"
//#include"stringManipulation.c"

//#define COMMENT 1

//#define MAIN 1


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


void getInputNode(char** name,int *roll,int *mark)
{
	*name = (char*)malloc(NAMESIZE);
	char ch,*temp;
	int i =0,stringSize = NAMESIZE,memAlloc = 2;
	printf("\nName:\n");
	ch = getchar();
	ch = getchar();
	while(ch != '\n')
	{
		if(i == stringSize)
                {
                        temp = (char*)malloc(memAlloc*NAMESIZE);
                        memAlloc++;
                        if(!temp)
                        {
                                printf("\nMemory error for name\n");
                                free(*name);
                                return;
                        }
                        *name = temp;
                }

		*((*name)+i) = ch;
		ch = getchar();
		i++;
	}
	*((*name)+i) = '\0';
	printf("Roll:\n");
	scanf("%d",roll);
	printf("Mark:\n");
	scanf("%d",mark);
	
}


NODE* createNode(char* name,int roll,int mark)
{
	NODE* temp;
	char *strtemp;
	temp = (NODE*)malloc(sizeof(NODE));
	if(temp != NULL)
	{
		int n = string_length(name);
		temp->name = (char*)malloc(n);
		if(temp->name == NULL)
		{
			printf("\nERROR:Memory for name cannot be allocated\n");
			return NULL;
		}
		stringCopy(name,temp->name);
		temp->roll = roll;
		temp->mark = mark;
		temp->prev = NULL;
		temp->next = NULL;
	}

	else
	{
		printf("\nERROR:Memory for node cannot be allocated\n");
		return NULL;
	}

	return temp;
}
void insertHead(NODE** head,NODE** tail,char* name,int roll,int mark)
{
	NODE* temp = createNode(name,roll,mark);
        if(!temp)
        {
                return;
        }

	if((*head) == NULL)
	{
		*head = temp;
		*tail = temp;
		return;
	}
	temp->next = *head;
	(*head)->prev = temp;
	*head = temp;
}

void append(NODE** head,NODE** tail,char* name,int roll,int mark)
{
	NODE* temp = createNode(name,roll,mark);
	if(!temp)
	{
		return;
	}
	if((*head) == NULL)
	{
		*head = temp;
		*tail = temp;
		return;
	}
	(*tail)->next = temp;
	temp->prev = *tail;
	*tail = temp;
}

void insertAt(NODE** head,NODE** tail,char* name,int roll,int mark,int position)
{
	NODE *curr,*temp;
	int i;
	if(position == 1)
	{
		insertHead(head,tail,name,roll,mark);
		return;
	}
	i = 2;
	curr = *head;
	while(i < position && curr->next != NULL)
	{
		curr = curr->next;
		i++;
	}
	if(i == position && curr != NULL)
	{
		if(curr->next == NULL)
		{
			append(head,tail,name,roll,mark);
			return;
		}
		temp = createNode(name,roll,mark);
		if(!temp)
		{
			return;
		}
		temp->prev = curr->next;
		temp->next = curr->next;
		curr->next = temp;
	}
	else
	{
		printf("\nERROR: The position is greater than the size of list!\n");
	}


}
void deleteFirst(NODE** head,NODE** tail)
{
	NODE* temp;
	if((*head) == NULL)
	{
		printf("\nERROR: There is no list\n");
		return;
	}
	temp = *head;
	if(((temp)->next) == NULL)
	{
		*head = NULL;
		*tail = NULL;
	}
	else
	{
		temp->next->prev = NULL;
		*head = temp->next;
	}
	free(temp);
	temp = NULL;

}

void deleteLast(NODE** head,NODE** tail)
{
	NODE* temp;
	if((*tail) == NULL)
	{
		printf("\nERROR: There is no list\n");
		return;
	}
	temp = *tail;
	if(!(temp->prev))
	{
		*tail = NULL;
		*head = NULL;
	}
	else
	{
		temp->prev->next = NULL;
		*tail = temp->prev;
	}
	free(temp);
	temp = NULL;
}


void deleteAt(NODE** head,NODE** tail,int position)
{
	int i;
	NODE* curr;
	if((*head) == NULL)
	{
		printf("\nERROR: No list found\n");
		return;
	}
	if(position==1)
	{
		deleteFirst(head,tail);
		return;
	}
	i = 2;
	curr = (*head)->next;
	while(i < position && curr->next != NULL)
	{
		curr = curr->next;
		i++;
	}
	if(i == position)
	{
		if(curr->next == NULL)
		{
			deleteLast(head,tail);
			return;
		}
		curr->prev->next = curr->next;
		curr->next->prev = curr->prev;
		free(curr);
		curr = NULL;
	}
	else
	{
		printf("\nERROR: The position is greater than the size of list!\n");
	}
}

void searchList(NODE** head,NODE** tail)
{
	getchar();
	if(*head == NULL)
	{
		printf("\nERROR: The list is not found!\n");
		return;
	}
        NODE* curr = *head;
        int position=0,roll = -1,mark = -1;
        char *name = (char*)malloc(NAMESIZE);
	char* temp;
	char flag = 1;
	printf("\nSearch Using:\n1.Name\n2.Roll\n3.mark\n");
	char ch = getchar();
	switch(ch)
	{
		case NAME:
				printf("\nEnter Search Name:");
				scanf("%s",name);
                                temp = (char*)realloc(name,string_length(name));
                                if(temp == NULL)
                                {
                                        printf("MEMORY ERROR for Name!!!\n");
                                        return;
                                }
                                name = temp;
				break;
		case ROLL:
				printf("\nEnter Search Roll Number:");
				scanf("%d",&roll);
				break;
		case MARK:
				printf("\nEnter Search mark:");
				scanf("%d",&mark);
				break;
		default:
				printf("\nEntered the wrong option\n");
				return;

	}
	position = 0;
	while(curr!= NULL)
	{
#ifdef COMMENT
		printf("\n%d\n",position);
#endif
		if((roll == curr->roll) || (mark == curr->mark) || (stringCompare(name,curr->name) == 0))
		{
			flag = 0;
			printf("\nThe searched element is in position %d\nName:%s\nRoll:%d\nmark:%d\n",position,curr->name,curr->roll,curr->mark);
		}
		position++;
		curr = curr->next;
	}
	if(curr == NULL && flag == 1)
	{
		printf("\nThe search node is not found!!\n");

	}
	position = 0;
	free(name);
	name = NULL;
}


void printList(NODE** head,NODE** tail)
{
	NODE* curr;
	if((*head) == NULL)
	{
		printf("\nThe list is EMPTY!!\n");
		return;
	}
	curr = *head;
	while(curr != NULL)
	{
	printf("\nName:%s\nRoll:%d\nmark:%d\n",curr->name,curr->roll,curr->mark);
	curr = curr->next;
	}
	return;

}

void swapNode(NODE** head,NODE** tail,NODE** node1,NODE** node2)
{
        NODE** node;
        NODE* temp;
        char flag=1;
        
        if(*head == NULL)
        {
        	printf("\nERROR: List not found\n");
        	return;
        }
        
        //SWAPPING NODES
        //SWAPPING NEXT AND PREVIOUS POINTER
        
        
        if((*node1)->next == *node2)                           //IF THEY ARE ADJACENT NODES
        {
        	if((*node1)->prev != NULL)
        		(*node1)->prev->next = (*node2);
        	if((*node2)->next != NULL)
        		(*node2)->next->prev = (*node1);
        	temp = (*node2)->next;
        	(*node2)->next = *node1;
        	(*node1)->next = temp;
        	
        	temp = (*node1)->prev;
        	(*node1)->prev = *node2;
        	(*node2)->prev = temp;
        	flag = 0;
        }
        else if((*node2)->next == *node1)
        {
        	if((*node2)->prev != NULL)
        		(*node2)->prev->next = (*node1);
        	if((*node1)->next != NULL)
        		(*node1)->next->prev = (*node2);
        	temp = (*node1)->next;
        	(*node1)->next = *node2;
        	(*node2)->next = temp;
        	
        	temp = (*node2)->prev;
        	(*node2)->prev = *node1;
        	(*node1)->prev = temp;
        	flag = 0;
        }
#ifdef COMMENTS
	printf("\nAdjacent nodes swapped\n");
#endif	
             
        if(flag == 1)                                        //IF NODES ARE NOT ADJACENT
        {
	        if((*node1)->prev != NULL)
	        {
	        	(*node1)->prev->next = (*node2);
	        }
	        if((*node2)->prev != NULL)
	        {
	        	(*node2)->prev->next = (*node1);
	        }
	        if((*node1)->next != NULL)
	        {
	        	(*node1)->next->prev = (*node2);
	        }
	        if((*node2)->next != NULL)
	        {
	        	(*node2)->next->prev = (*node1);
	        }
	          
        	temp = (*node1)->next;
        	(*node1)->next = (*node2)->next;
        	(*node2)->next = temp;
        	
        	temp = (*node1)->prev;
        	(*node1)->prev = (*node2)->prev;
        	(*node2)->prev = temp;
        }
        
#ifdef COMMENTS
	printf("\nNON Adjacent nodes swapped\n");
#endif	
                

	//SWAPPING HEAD
        if(*head == *node1)
        {
        	*head = *node2;
        }
        else if(*head == *node2)
        {
        	*head = *node1;
        }
#ifdef COMMENTS
	printf("\nHead\n");
#endif	
        
        
        //SWAPPING TAIL
        if(*tail == *node1)
        {
        	*tail = *node2;
        }
        else if(*tail == *node2)
        {
        	*tail = *node1;
        }
#ifdef COMMENTS
	printf("\nTail\n");
#endif	
                
                
        temp = *node1;
        *node1 = *node2;
        *node2 = temp;

        
}



void sort(NODE** head,NODE** tail)
{
	NODE *previous,*nextt;
        getchar();
        if(*head == NULL)
        {
                printf("\nERROR: The list is not found!\n");
                return;
        }
	previous = *head;
	nextt = (*head)->next;
	printf("\nSORT BY:\n1.Name\n2.Roll Number\nMark\n");
	char ch = getchar();
	switch(ch)
	{
		case NAME:{
			while(nextt!=NULL)
			{
				previous = *head;
				while(previous != nextt)
				{
					if(stringCompare(previous->name,nextt->name) == 1)
					{
#ifdef COMMENTS
	printf("\nName Swap\n");
#endif
						swapNode(head,tail,&previous,&nextt);
					}
				previous = previous->next;
				}
			nextt = nextt->next;
			}
			break;
			}
		case ROLL:
			while(nextt != NULL)
			{
				previous = *head;
				while(previous != nextt)
				{
					if(previous->roll > nextt->roll)
					{
#ifdef COMMENTS
	printf("\nBefore Swap");
	printNode(previous->prev);
        printNode(previous);
        printNode(previous->next);
        printNode(nextt->prev);
        printNode(nextt);
        printNode(nextt->next);
#endif

						swapNode(head,tail,&previous,&nextt);
#ifdef COMMENTS
	printf("\nAfter Swap");
	printNode(previous->prev);
        printNode(previous);
        printNode(previous->next);
        printNode(nextt->prev);
        printNode(nextt);
        printNode(nextt->next);
#endif

					}
				previous = previous->next;
				}
			nextt = nextt->next;
			}
			break;
		case MARK :
			while(nextt != NULL)
			{
				previous = *head;
				while(previous != nextt)
				{
					if(previous->mark > nextt->mark)
					{

#ifdef COMMENTS
        printf("\nMark Swap\n");
#endif
						swapNode(head,tail,&previous,&nextt);
					}
				previous = previous->next;
				}
			nextt = nextt->next;
			}
			break;
		default:
			printf("You have entered the wrong Option\n");
			return;
	}
	printList(head,tail);
	return;
}

void deleteList(NODE** head,NODE** tail)
{
        if(*head == NULL)
        {
                return;
        }
	NODE* curr = *head;
	NODE* temp;
	while(curr != NULL)
	{
		temp = curr;
		curr = curr->next;
		free(temp);
	}
	temp = NULL;
	curr = NULL;
	*head = NULL;
	*tail = NULL;
	printf("\nList Deleted Successfully\n");

}

void printNode(NODE* node)
{
	if(node == NULL)
	{
		printf("\nNode NULL\n");
		return;
	}
	printf("\nName:%s\nRoll:%d\nMark:%d\n",node->name,node->roll,node->mark);
}
