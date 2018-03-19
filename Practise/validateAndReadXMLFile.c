#include"stringManipulation.c"
#include"doubly.c"
#include"stack.c"
#include"myHeader.h"
#include<stdio.h>
#include<stdlib.h>


int getDataAndTag(char* ch1,char *str,int data,FILE* f)
{
	int stringIndex = 0,fileMarker=0;
	if(data == 0)
	{
                while(*ch1 != '<')
                {
                        *(str+stringIndex) = *ch1;
                        stringIndex++;
                	fileMarker += fread(ch1,1,1,f);
                	//printf("%c",*ch1);
                }
                *(str+stringIndex) = '\0';
                //printf("DATA:%s\n",str);
                return fileMarker;
         }
         else
         {
         	if(*ch1 == '/')
         	{
         		fileMarker += fread(ch1,1,1,f);
         		//printf("%c",*ch1);
         	}
         	while(*ch1 != '>')
                {
                        *(str+stringIndex) = *ch1;
                        stringIndex++;
                	fileMarker += fread(ch1,1,1,f);
                	//printf("%c",*ch1);
                }
                *(str+stringIndex) = '\0';
                //printf("TAG:%s\n",str);
                return fileMarker;
         } 
}


int xmlFileRead(NODE** head,NODE** tail)
{
	char *name;
        int roll,mark,data=1,studentCount = 1;
        int iterator=-1,stringIndex,fileMarker = 0;
        char ch,ch1,choice;
    	char *str = (char*)malloc(50);
	STACK *top = NULL;
        FILE* f = fopen("/home/econsys4/Intern/Files/xmlPractise.txt","r");
        fseek(f,0L,SEEK_END);
        int fileSize = ftell(f);
        rewind(f);

        if(f == NULL)
        {
                printf("File not found\n");
                return 0;
        }
        fileMarker += fread(&ch,1,1,f);
        //printf("%c",ch);

        fileMarker += fread(&ch1,1,1,f);
        while(fileMarker < fileSize)
        {
        	//printf("%c",ch1);
                if(ch == '<' && ch1 != '/')
                {
                if(data ==0)
                {
                	printf("ERROE:Close Tag missing or Data is between two open Tags!!\n");
                	deleteStack(&top);
                	deleteList(head,tail);
                	return 0;
                }
                	data = 1;
                	fileMarker += getDataAndTag(&ch1,str,data,f);
                	push(&top,str);
                	if(countStack(&top) == 3)
                	{
                		if(string_to_number((str+7)) != studentCount)
                		{
                			printf("Student Tag Count Error\n");
                			deleteStack(&top);
                			deleteList(head,tail);
                			return 0;
                		}
                	}
                	//printStack(&top);
                }
                else if(ch == '>' && ch1 != '\t' && ch1 != '\n' && ch1 != '<')
                {
                	if(data == -1)
                	{
                		printf("Data in invalid location\n");
                		deleteStack(&top);
                		deleteList(head,tail);
                		return 0;
                	}
                	iterator++;
                	data = 0;
			fileMarker += getDataAndTag(&ch1,str,data,f);
			choice = ((iterator%3)+1) + 48;
                switch(choice)
                {
                        case NAME:
                                name = (char*)malloc(string_length(str));
                                stringCopy(str,name);
                                break;
                        case ROLL:
                                roll = string_to_number(str);
                //              printf("\nRoll:%d\n",roll);
                                break;
                        case MARK:
                                mark = string_to_number(str);
                //              printf("\nMark:%d\n",mark);
                                append(head,tail,name,roll,mark);
                                studentCount++;
                                free(name);
                                name = NULL;
                                break;
                }
                }
                else if(ch == '<' && ch1 == '/')
                {
                	data = -1;
                	fileMarker += getDataAndTag(&ch1,str,data,f);
                	//printf("%c",ch1);
                	if(stringCompareCase(str,top->data) != 0)
                	{
                		printf("Close Tag:%s,Open Tag: %s\n",str,top->data);
                		printf("The tags do not match\n");
                		deleteStack(&top);
                		deleteList(head,tail);
                		return 0;
                	}
                	pop(&top);
                	//printStack(&top);
                }
                ch = ch1;
                fileMarker += fread(&ch1,1,1,f);

        }
        return 1;
}

void xmlFileWrite(NODE** head,NODE** tail)
{
	char *str = (char*)malloc(100);
	if(*head == NULL)
	{
		printf("The list is Empty\n");
	}
	NODE* curr;
	curr = *head;
	int studentCount = 0;
	FILE *fp = fopen("/home/econsys4/Intern/Files/xmlParsed.txt","w");
	if(fp == NULL)
	{
		printf("No such file or Directory\n");
		return;
	}
	stringCopy("<XML>\n\t<Student Database>\n",str);
	fwrite(str,1,string_length(str),fp);
	while(curr != NULL)
	{
		//printf("Inside Loop");
		studentCount++;
		stringCopy("\t\t<Student",str);
		fwrite(str,1,string_length(str),fp);
		numberToString(studentCount,str);
		fwrite(str,1,string_length(str),fp);
                stringCopy(">\n\t\t\t<Name>",str);
		fwrite(str,1,string_length(str),fp);
		fwrite(curr->name,1,string_length(curr->name),fp);
                stringCopy("</Name>\n\t\t\t<Roll>",str);
		fwrite(str,1,string_length(str),fp);
		numberToString(curr->roll,str);
		fwrite(str,1,string_length(str),fp);
                stringCopy("</Roll>\n\t\t\t<Mark>",str);
		fwrite(str,1,string_length(str),fp);
		numberToString(curr->mark,str);
		fwrite(str,1,string_length(str),fp);
                stringCopy("</Mark>\n\t\t</Student",str);
		fwrite(str,1,string_length(str),fp);
		numberToString(studentCount,str);
		fwrite(str,1,string_length(str),fp);
                stringCopy(">\n",str);
		fwrite(str,1,string_length(str),fp);
		curr = curr->next;
	}
	        stringCopy("\t</Student Database>\n</XML>",str);
		fwrite(str,1,string_length(str),fp);
	fclose(fp);
	printf("File Write Successful\n");
}


int main()
{
	NODE *head = NULL,*tail=NULL;
	char *name;
	int position,roll ,mark;
	char ch = '0';
	if(xmlFileRead(&head,&tail) == 1)
{
while(1)
	{
		printf("\nEnter an option:\n1.Insert at Head\n2.Append\n3.Insert at a given position\n4.Delete at Head\n5.Delete at Tail\n");
		printf("6.Delete at given Position\n7.Search\n8.Print the list\n9.Sort\nA.Delete Entire List\n0.Exit\n");
		ch = getchar();
		switch(ch)
		{
                        case '1':
                                getInputNode(&name,&roll,&mark);
                                insertHead(&head,&tail,name,roll,mark);
                                free(name);
                                break;
                        case '2':
                                getInputNode(&name,&roll,&mark);
                                append(&head,&tail,name,roll,mark);
                                free(name);
                                break;
                        case '3':
                                getInputNode(&name,&roll,&mark);
                                printf("Position:\n");
                                scanf("%d",&position);
                                insertAt(&head,&tail,name,roll,mark,position);
                                free(name);
                                break;
			case '4':
				deleteFirst(&head,&tail);
				break;
			case '6':
				printf("Enter the position to be deleted:\n");
				scanf("%d",&position);
				deleteAt(&head,&tail,position);
				break;
			case '5':
				deleteLast(&head,&tail);
				break;
			case '7':
				searchList(&head,&tail);
				break;
			case '8':
				printList(&head,&tail);
				break;
			case '9':
				sort(&head,&tail);
				break;
			case 'a':
			case 'A':
				deleteList(&head,&tail);
				break;
			case '0':
			        xmlFileWrite(&head,&tail);
				deleteList(&head,&tail);
				return 0;
			default:
				printf("Enter the correct option\n");
				break;
		}
		getchar();

	}
	}


	return 0;
}
