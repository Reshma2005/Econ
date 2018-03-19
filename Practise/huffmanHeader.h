#pragma once
#include"stringManipulation.c"

struct binaryTree
{
	char *c;
	int frequency;
	struct binaryTree *left;
	struct binaryTree *right;
};

typedef struct binaryTree BT;

BT* createBTNode(char *c,int frequency);
void deleteBtree(BT* root);
BT* createBinaryTree(BT* left,BT* right);
void printBtree(BT* root);
void deleteBtree(BT* root);








struct heap
{
	BT* root;
	struct heap* next;
	struct heap* prev;
};

typedef struct heap HEAP;


void addInHeap(char ch,HEAP** head,HEAP** tail);
HEAP* createHeapNode(char ch);
BT* selectTwoMin(HEAP **head,HEAP** tail);
void printHeap(HEAP* head);
void deleteHeap(HEAP* head);
