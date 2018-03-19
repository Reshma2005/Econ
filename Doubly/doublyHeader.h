#pragma once
#define NAMESIZE 50
#pragma once
struct node
{
	char name[NAMESIZE];
	int roll,mark;
	struct node* prev;
	struct node* next;
};

typedef struct node NODE;
//Declarations of Linked List functions
NODE* createNode(char* name,int roll,int mark);                                  //Creates a node and assigns value
void insertHead(NODE** head,NODE** tail,char* name,int roll,int mark);           //insert data at head
void append(NODE** head,NODE** tail,char* name,int roll,int mark);		 //inserts data at tail
void insertAt(NODE** head,NODE** tail,char* name,int roll,int mark,int position);//Inserts data at given position
void deleteFirst(NODE** head,NODE** tail);					 //Deletes the first node
void deleteLast(NODE** head,NODE** tail);					 //Deletes the last node
void deleteAt(NODE** head,NODE** tail,int k);					 //Deletes node at given position
void searchList(NODE** head,NODE** tail);					 //Searches for the given data in list
void sort(NODE** head,NODE** tail);
void swapNode(NODE** head,NODE** tail,NODE** node1,NODE** node2);
void printList(NODE** head,NODE** tail);					 //Prints the Entire List
void deleteList(NODE** head,NODE** tail) ;                                       //Deletes the entire list
//Declarations of String Functions
char toUpper(char ch);
int string_length(char* str);
void stringCopy(char* str1,char* str2);
void toUpperCase(char* str);
int string_to_number(char* str);
int stringCompare(char *str1,char* str2);
void stringReverse(char* str);
void numberToString(int num,char* str);
//char* append(char* des,char* src);
