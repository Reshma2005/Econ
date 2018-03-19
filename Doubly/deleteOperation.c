#include<string.h>
#include<stdlib.h>
#include<stdio.h>
#include"myHeader.h"
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

