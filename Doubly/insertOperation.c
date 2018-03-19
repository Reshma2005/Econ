#include<string.h>
#include<stdlib.h>
#include<stdio.h>
#include"myHeader.h"
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
