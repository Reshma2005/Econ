#include"huffmanHeader.h"


void addInHeap(char ch,HEAP** head,HEAP** tail)
{
	HEAP *curr;
	if(*head == NULL)
	{
		curr = createHeapNode(ch);
		if(!curr)
		{
			return;
		}
		*head = curr;
		*tail = curr;
	}

	curr = *head;
	while(curr!=NULL)
	{
		if(*(curr->root->c) == ch)
		{
			curr->root->frequency++;
			return;
		}
		curr = curr->next;
	}
	curr = createHeapNode(ch);
	(*tail)->next = curr;
	curr->prev = *tail;
	*tail = curr;
}


HEAP* createHeapNode(char ch)
{
	HEAP* HeapCurr = (HEAP*)malloc(sizeof(HEAP));
	if(!HeapCurr)
	{
		printf("Error in Memory Allocation for Heap\n");
		return HeapCurr;
	}
	char *str = (char*)malloc(2);
	*str = ch;
	*(str+1) = '\0';
	HeapCurr->root = createBTNode(str,1);
	if(!HeapCurr->root)
	{
		free(HeapCurr);
		return NULL;
	}
	HeapCurr->next = NULL;
	HeapCurr->prev = NULL;
	return HeapCurr;
}

BT* createHuffmanTree(HEAP** head,HEAP** tail)
{
	HEAP* min1 = NULL;
	HEAP* min2 = NULL;
	unsigned int minFreq1=0x0fffffff,minFreq2=0x0fffffff;
	if(*head == NULL)
	{
		printf("Heap Empty\n");
		return NULL;
	}
	HEAP *curr;
	while(*head != *tail)
	{
		curr = *head;
		min1 = NULL;
		min2 = NULL;
		while(curr != NULL)
		{
			if(curr->root->frequency < minFreq1 && curr->root->frequency < minFreq2)
			{
				minFreq2 = minFreq1;
				min2 = min1;
				minFreq1 = curr->root->frequency;
                                //printf("min1: %d\n",minFreq1);
				min1 = curr;
			}
			else if(curr->root->frequency < minFreq2)
			{
				minFreq2 = curr->root->frequency;
                                //printf("min2: %d\n",minFreq2);
				min2 = curr;
			}
			curr = curr->next;
		}
		//printf("minFreq1: %d minFreq2: %d\n",minFreq1,minFreq2);
		minFreq1=0x0fffffff;
		minFreq2=0x0fffffff;

		if(*head == min2)
		{
			min2->next->prev = NULL;
			*head = min2->next;
		}
		else
		{
			min2->prev->next = min2->next;
		}
		if(*tail == min2)
		{
			min2->prev->next = NULL;
			*tail = min2->prev;
		}
		else
		{
			min2->next->prev = min2->prev;
		}
		//printf("Change of head and tail\n");
		min1->root = createBinaryTree(min1->root,min2->root);
		//printf("\nmin1->root:\n");
		//printBtree(min1->root);
		free(min2);
		if(!min1->root)
		{
			deleteHeap(*head);
			return NULL;
		}

	}

	return (*head)->root;

}


void printHeap(HEAP* head)
{
	if(!head)
	{
		printf("Heap Empty\n");
		return;
	}
	printf("Heap Elements\n");
	while(head != NULL)
	{
		printf("%s %d\n",head->root->c,head->root->frequency);
		head = head->next;
	}
}

void deleteHeap(HEAP* head)
{
	if(!head)
	{
		printf("Heap Empty\n");
                return;
	}
	HEAP *temp = head;
	while(head != NULL)
        {
		head = temp->next;
		deleteBtree(temp->root);
		free(temp);
		temp = head;
	}

}


