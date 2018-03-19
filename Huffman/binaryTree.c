#include"huffmanHeader.h"

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
	if(root->c)
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

int checkBtreeNode(char *str,char ch)
{
	int i = 0;
	while(*(str+i) != '\0')
	{
		if(ch == *(str+i))
		{
			return 1;
		}
		i++;
	}
	return 0;
}

char* encodeHuffman(BT* root,char ch,char* code,int* codeLength,int* codeStringLength)
{
//	ch = toSpecialCharacters(ch);
	if(!root)
	{
		printf("No Huffman Tree\n");
		free(code);
		code = NULL;
		return NULL;
	}
	if(checkBtreeNode(root->c,ch) == 1)
	{
		if(string_length(root->c) == 1)
		{
			return code;
		}
		if(*codeStringLength == (*codeLength)-1)
		{
			(*codeLength) += CODELENGTH;
			char *temp = (char*)realloc(code,(*codeLength));
			if(temp == NULL)
			{
				printf("Realloc Error for code String\n");
				free(code);
				return NULL;
			}
			code = temp;
			if((*codeStringLength) % 150 == 149)
			{
				*(code+(*codeStringLength)) = '\n';
				(*codeStringLength)++;
			}
		}
		if(root->left)
		{
			if(checkBtreeNode(root->left->c,ch) ==1)
			{
				*(code+(*codeStringLength)) = '0';
				(*codeStringLength)++;
				*(code+(*codeStringLength)) = '\0';
				return encodeHuffman(root->left,ch,code,codeLength,codeStringLength);
			}
		}
		if(root->right)
		{
			if(checkBtreeNode(root->right->c,ch) == 1)
			{
				*(code+(*codeStringLength)) = '1';
				(*codeStringLength)++;
				*(code+(*codeStringLength)) = '\0';
				return encodeHuffman(root->right,ch,code,codeLength,codeStringLength);
			}
		}
		return code;
	}
	else
	{
		printf("Character not found\n");
		free(code);
		return NULL;
	}
}

char* decodeHuffman(BT* root,char* code)
{
	int textLength = CODELENGTH;
	int textStringLength = 0;
        char *text = (char*)malloc(CODELENGTH);
	*text = '\0';
	BT* curr = root;
	int i = 0;
	while(*(code+i) != '\0')
	{
		if(*(code+i) == '1')
		{
			if(curr->right)
			{
				curr = curr->right;
                                if(string_length(curr->c) == 1)
                                {
                                if(textStringLength == textLength-1)
                                {
                                        textLength += CODELENGTH;
                                        char *temp = (char*)realloc(text,textLength);
                                        if(temp == NULL)
                                        {
                                                printf("Realloc Error for text String\n");
                                                free(text);
                                                free(code);
                                                return NULL;
                                        }
                                        text = temp;
                                }

                                *(text+textStringLength) = *(curr->c);
                                textStringLength++;
                                *(text+textStringLength) = '\0';
                                //printf("Right: %s\n",text);
                                curr = root;

                                }

			}
		}
		else if(*(code+i) == '0')
		{
			if(curr->left)
			{
				curr = curr->left;
				if(string_length(curr->c) == 1)
				{
                                if(textStringLength == textLength-1)
                                {
                                        textLength += CODELENGTH;
                                        char *temp = (char*)realloc(text,textLength);
                                        if(temp == NULL)
                                        {
                                                printf("Realloc Error for text String\n");
                                                free(text);
                                                free(code);
                                                return NULL;
                                        }
                                        text = temp;
                                }

                                *(text+textStringLength) = *(curr->c);
                                textStringLength++;
                                *(text+textStringLength) = '\0';
                                //printf("Left: %s\n",text);
                                curr = root;

				}
			}
		}

	i++;
	}
	return text;
}
