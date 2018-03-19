#include"huffmanHeader.h"
#include"binaryTree.c"
#include"heap.c"

int main()
{
	//char str[] ="ssssssllllllkwssssssssppppllllxxoooo	ooooooodddddddddd";
	HEAP *head = NULL,*tail = NULL;
        BT* huffmanTree = NULL;
        int i =0,codeLength = CODELENGTH,codeStringLength = 0;
        FILE* fptr = fopen("/home/econsys4/Reshma/Files/huffmanencode.txt","r");
        if(!fptr)
        {
                printf("No such file or directory\n");
                return 0;
        }

        fseek(fptr,0L,SEEK_END);
        int fileSize = ftell(fptr);
        rewind(fptr);
        char *str = (char*)malloc(fileSize+1);
        fread(str,1,fileSize,fptr);
        *(str+fileSize) = '\0';

	while(str[i] != '\0')
	{
		addInHeap(str[i],&head,&tail);
		i++;
	}
        huffmanTree = createHuffmanTree(&head,&tail);
	char *code = (char*)malloc(CODELENGTH);
	*(code+0) = '\0';
	i = 0;
	while(str[i] != '\0')
	{
		code = encodeHuffman(huffmanTree,*(str+i),code,&codeLength,&codeStringLength);
		i++;
	}
	if(code)
	{
	printf("CODE: %s\n",code);
	}
	i = 0;
	free(str);
	str = decodeHuffman(huffmanTree,code);
	printf("TEXT: %s\n",str);
	fclose(fptr);
	fptr = fopen("/home/econsys4/Reshma/Files/huffmanDecode.txt","w");
	if(!fptr)
	{
		printf("No such file or Directory");
		free(code);
		free(str);
		deleteHeap(head);
		return 0;
	}
	fwrite(code,1,string_length(code),fptr);
	fclose(fptr);
	free(code);
	free(str);
	deleteHeap(head);
	//deleteBtree(huffmanTree);
	return 0;
}
