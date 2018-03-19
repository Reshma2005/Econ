#include<stdio.h>
#include<stdlib.h>
#include"myHeader.h"
STACK* createStackNode(char* data)
{
	STACK *temp = (STACK*)malloc(sizeof(STACK));
	if(!temp)
	{
		printf("ERROR:Memory for stack node cannot be created\n");
		return NULL;
	}
	temp->data = (char*)malloc(string_length(data));
	if(!temp->data)
	{
		printf("ERROR:Memory for data in node cannot be created\n");
		free(temp);
		return NULL;
	}
	stringCopy(data,temp->data);
	temp->next = NULL;
	return temp;
}


void push(STACK** top,char* data)
{
	STACK* temp = createStackNode(data);
	if(!temp)
	{
		return;
	}
	if(*top == NULL)
	{
		*top = temp;
		return;
	}
	temp->next = *top;
	*top = temp;
}

void pop(STACK** top)
{
	if(*top == NULL)
	{
		printf("ERROR:Empty Stack\n");
		return;
	}
	STACK *temp = *top;
	*top = (*top)->next;
	free(temp);
	temp = NULL;
}

void deleteStack(STACK** top)
{
	if(!(*top))
	{
		printf("Stack Empty\n");
		return;
	}
	STACK* temp;
	temp = *top;
	while(temp)
	{
		*top = (*top)->next;
		free(temp);
		temp = *top;
	}
	printf("\nStack Deleted Successfully\n");
}

void printStack(STACK** top)
{
	if(!(*top))
	{
		printf("Stack Empty\n");
		return;
	}
	STACK* temp = *top;
	printf("\nSTACK\n");
	while(temp)
	{
		printf("%s\n",temp->data);
		temp = temp->next;
	}
	printf("\nStack Ends\n");
}

int countStack(STACK** top)
{

	int count = 0;
	STACK* temp = *top;
	while(temp)
	{
		count++;
		temp = temp->next;
	}
	return count;
}

