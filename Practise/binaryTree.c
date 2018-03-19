#include<stdio.h>
#include"huffmanHeader.h"
#include<stdio.h>
#include<stdlib.h>
//#include"stringManipulation.c"

BT* createBTNode(char *c,int frequency)
{
	BT* temp = (BT*)malloc(sizeof(BT));
	if(!temp)
	{
		printf("Memory error in creating a BS node\n");
		temp = NULL;
		return temp;
	}
	temp->c = (char*)malloc(string_length(c)+1);
	if(!temp->c)
	{
		printf("Memory Error for character");
		free(temp);
		temp = NULL;
		return temp;
	}

	stringCopy(c,temp->c);
	temp->frequency = frequency;
	temp->left = NULL;
	temp->right = NULL;
	return temp;
}


BT* createBinaryTree(BT* left,BT* right)
{
	BT* temp = NULL;
	char *str = (char*)malloc(string_length(left->c)+string_length(right->c)+1);
	stringCopy(left->c,str);
	stringCopy(right->c,(str+string_length(left->c)));
	temp = createBTNode(str,left->frequency+right->frequency);
	if(temp == NULL)
	{
		return temp;
	}
	
	temp->left = left;
	temp->right = right;
	return temp;
}


void deleteBtree(BT* root)
{
	if(!root)
	{
		printf("Tree Empty\n");
		return;
	}
	if(root->left)
	{
		deleteBtree(root->left);
	}
	if(root->right)
	{
		deleteBtree(root->right);
	}
	free(root->c);
	root->c = NULL;
	free(root);
	root = NULL;
}

void printBtree(BT* root)
{
        if(!root)
        {
                printf("Tree Empty\n");
                return;
        }
        if(root->left)
        {
		printBtree(root->left);
        }
        if(root->right)
        {
                printBtree(root->right);
        }
	printf("%s %d\n",root->c,root->frequency);
}
void printBtreeNode(BT* root)
{
	if(root)
	{
		printf("%s %d\n",root->c,root->frequency);
	}
}
