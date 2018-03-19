#include<stdlib.h>
#include<stdio.h>
#include"doublyHeader.h"
NODE* createNode(char* name,int roll,int mark)
{
	NODE* temp;
	temp = (NODE*)malloc(sizeof(NODE));
	if(temp != NULL)
	{
		stringCopy(temp->name,name);
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
        char name[NAMESIZE] = {0};
	printf("\nSearch Using:\n1.Name\n2.Roll\n3.mark\n");
	char ch = getchar();
	switch(ch)
	{
		case '1':
				printf("\nEnter Search Name:");
				scanf("%s",name);
				break;
		case '2':
				printf("\nEnter Search Roll Number:");
				scanf("%d",&roll);
				break;
		case '3':
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
			printf("\nThe searched element is in position %d\nName:%s\nRoll:%d\nmark:%d\n",position,curr->name,curr->roll,curr->mark);
			return;
		}
		position++;
		curr = curr->next;
	}
	if(curr == NULL)
	{
		printf("\nThe search node is not found!!\n");

	}
	position = 0;
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

void swapNode(NODE** head,NODE** tail,NODE* node1,NODE* node2)
{
        if(*head == NULL)
        {
                printf("\nERROR: The list is not found!\n");
                return;
        }
	char *name = (char*)malloc(50);
#ifdef COMMENT
	printf("\nNODE1:%s %d %d\n",node1->name,node1->roll,node1->mark);
        printf("\nNODE2:%s %d %d\n",node2->name,node2->roll,node2->mark);
#endif
	int roll = node1->roll,mark = node1->mark;
	stringCopy(node1->name,name);
	stringCopy(node2->name,node1->name);
	stringCopy(name,node2->name);
	node1->roll = node2->roll;
	node2->roll = roll;
	node1->mark = node2->mark;
	node2->mark = mark;
#ifdef COMMENT
        printf("\nNODE1:%s %d %d\n",node1->name,node1->roll,node1->mark);
        printf("\nNODE2:%s %d %d\n",node2->name,node2->roll,node2->mark);
#endif
	free(name);
	name = NULL;
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
		case '1':{
			while(nextt!=NULL)
			{
				previous = *head;
				while(previous != nextt)
				{
					if(stringCompare(previous->name,nextt->name) == 1)
					{
#ifdef COMMENT
	printf("\nName Swap\n");
#endif
						swapNode(head,tail,previous,nextt);
					}
				previous = previous->next;
				}
			nextt = nextt->next;
			}
			break;
			}
		case '2':
			while(nextt != NULL)
			{
				previous = *head;
				while(previous != nextt)
				{
					if(previous->roll > nextt->roll)
					{
#ifdef COMMENT
        printf("\nRoll Swap Swap\n");
#endif

						swapNode(head,tail,previous,nextt);

					}
				previous = previous->next;
				}
			nextt = nextt->next;
			}
			break;
		case '3':
			while(nextt != NULL)
			{
				previous = *head;
				while(previous != nextt)
				{
					if(previous->mark > nextt->mark)
					{

#ifdef COMMENT
        printf("\nMark Swap\n");
#endif
						swapNode(head,tail,previous,nextt);
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
