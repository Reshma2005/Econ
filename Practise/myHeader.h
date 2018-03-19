
#define NAME 49
#define ROLL 50
#define MARK 51


#define NAMESIZE 50
#pragma once
#include<stdio.h>
struct node
{
	char *name;
	int roll,mark;
	struct node* prev;
	struct node* next;
};


struct stackNode
{
	char *data;
	struct stackNode *next;
};
typedef struct stackNode STACK;

typedef struct node NODE;

//Doubly Linked List Declarations
NODE* createNode(char* name,int roll,int mark);                                  //Creates a node and assigns value
void insertHead(NODE** head,NODE** tail,char* name,int roll,int mark);           //insert data at head
void append(NODE** head,NODE** tail,char* name,int roll,int mark);		 //inserts data at tail
void insertAt(NODE** head,NODE** tail,char* name,int roll,int mark,int position);//Inserts data at given position
void deleteFirst(NODE** head,NODE** tail);					 //Deletes the first node
void deleteLast(NODE** head,NODE** tail);					 //Deletes the last node
void deleteAt(NODE** head,NODE** tail,int k);					 //Deletes node at given position
void searchList(NODE** head,NODE** tail);					 //Searches for the given data in list
void sort(NODE** head,NODE** tail);                                              //Sorts the list
void swapNode(NODE** head,NODE** tail,NODE** node1,NODE** node2);                //Swaps two nodes
void printList(NODE** head,NODE** tail);					 //Prints the Entire List
void deleteList(NODE** head,NODE** tail) ;                                       //Deletes the entire list
void printNode(NODE* node);                                                      //Prints the data in the node
void getInputNode(char** name,int *roll,int *mark);                              //Gets input from user to pass into insert functions



//Declarations of String Functions
char toUpper(char ch);
int string_length(char* str);
void stringCopy(char* str1,char* str2);
void toUpperCase(char* str);
int string_to_number(char* str);
int stringCompare(char *str1,char* str2);
void stringReverse(char* str);
void numberToString(int num,char* str);
int stringCompareCase(char *str1,char * str2);
//char* append(char* des,char* src);

//Stack File Deaclarations
STACK* createStackNode(char* data);
void push(STACK** top,char* data);
void pop(STACK** top);
void printStack(STACK** top);
int countStack(STACK** top);
void deleteStack(STACK** top);


//File Operation Funtions Declarations
int xmlFileRead(NODE** head,NODE** tail);
void xmlFileWrite(NODE** head,NODE** tail);
int getDataAndTag(char* ch1,char *str,int data,FILE* f);
