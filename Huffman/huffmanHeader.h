#pragma once
#include<stdio.h>
#include<stdlib.h>
#include"stringManipulation.c"
#define CODELENGTH 50
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
int checkBtreeNode(char *str,char ch);
char* encodeHuffman(BT* root,char ch,char* code,int* codeLength,int* codeStringLength);
char* decodeHuffman(BT* root,char* code);




char toSpecialCharacters(char ch);
char fromSpecialCharacters(char ch);



struct heap
{
	BT* root;
	struct heap* next;
	struct heap* prev;
};

typedef struct heap HEAP;


void addInHeap(char ch,HEAP** head,HEAP** tail);
HEAP* createHeapNode(char ch);
BT* createHuffmanTree(HEAP **head,HEAP** tail);
void printHeap(HEAP* head);
void deleteHeap(HEAP* head);
