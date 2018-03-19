#include"imageHeader.h"



int setZoomPixels(RGB** zoom,int k,int row,int col,int flag,RGB* adj1,RGB* adj2)
{
	unsigned int i;
	int op,value;
	unsigned char *str = NULL;
	str = (unsigned char*)malloc(k-1);
	if(str == NULL)
	{
		printf("Memory Allocation failure for extra pixel bytes\n");
		return 0;
	}
	if(adj1->blue > adj2->blue)
	{
		op = (adj1->blue - adj2->blue)/k;
		value = (op) + adj2->blue;
	}
	else
	{
                op = (adj2->blue - adj1->blue)/k;
                value = (op) + adj1->blue;

	}
	for(i=0;i<k-1;i++)
	{
		*(str+i) = value;
		value += op;
	}
	if(adj1->blue > adj2->blue)
	{
		stringReverse(str,k-1);
	}
	if(flag == ROW)
	{
		for(i=1;i<k;i++)
		{
			(*(zoom+row)+col+i)->blue = *(str+i-1);
		}
	}
	else
	{
		for(i=1;i<k;i++)
                {
                        (*(zoom+row+i)+col)->blue = *(str+i-1);
                }
	}

        if(adj1->green > adj2->green)
        {
                op = (adj1->green - adj2->green)/k;
                value = (op) + adj2->green;
        }
        else
        {
                op = (adj2->green - adj1->green)/k;
                value = (op) + adj1->green;

        }
	for(i=0;i<k-1;i++)
	{
		*(str+i) = value;
		value += op;
	}
        if(adj1->green > adj2->green)
        {
                stringReverse(str,k-1);
        }
        if(flag == ROW)
        {
                for(i=1;i<k;i++)
                {
                        (*(zoom+row)+col+i)->green = *(str+i-1);
                }
        }
        else
        {
                for(i=1;i<k;i++)
                {
                        (*(zoom+row+i)+col)->green = *(str+i-1);
                }
        }

        if(adj1->red > adj2->red)
        {
                op = (adj1->red - adj2->red)/k;
                value = (op) + adj2->red;
        }
        else
        {
                op = (adj2->red - adj1->red)/k;
                value = (op) + adj1->red;

        }
	for(i=0;i<k-1;i++)
	{
		*(str+i) = value;
		value += op;
	}
        if(adj1->red > adj2->red)
        {
                stringReverse(str,k-1);
        }
        if(flag == ROW)
        {
                for(i=1;i<k;i++)
                {
                        (*(zoom+row)+col+i)->red = *(str+i-1);
                }
        }
        else
        {
                for(i=1;i<k;i++)
                {
                        (*(zoom+row+i)+col)->red = *(str+i-1);
                }
        }
        free(str);
        str = NULL;
        return 1;

}



void defineHeader(BMH *src,BMH* des,int height,int width,int padding)
{
        if(!src || !des)
        {
                printf("No Header!!!\n");
                return;
        }
        des->signature = src->signature;
        des->reserved1 = src->reserved1;
        des->reserved2 = src->reserved2;
        des->offset = src->offset;
        des->bitmapInfoHeaderSize = src->bitmapInfoHeaderSize;
        des->height = height;
      	des->width = width;
        des->planes = src->planes;
        des->bitsPerPixel = src->bitsPerPixel;
        des->compressionType = src->compressionType;
        des->horizontalResolution = src->horizontalResolution;
        des->verticalResolution = src->verticalResolution;
        des->colors = src->colors;
        des->importantColors = src->importantColors;
        des->imageDataSize = height * width * (src->bitsPerPixel/8);
        des->bmpFileSize = des->imageDataSize + des->offset + (padding*height);

}

void stringReverse(unsigned char* str,int n)
{
        int i = 0;
        unsigned char ch;
        while(i < (n/2))
        {
                ch = *(str+i);
                *(str+i) = *(str-i-1+n);
                *(str-i-1+n) = ch;
                i++;
        }

}




int string_to_number(char* str)
{
	if(string_length(str) == 0)
	{
	return 1;
	}
	if(string_length(str) == 1)
	{
		if(*(str) == '+')
		{
			return 1;
		}
		else if(*(str) == '-')
		{
			return -1;
		}
	}
	int index = 0,number = 0,flag = 0;
	if(*(str) == '-' || *(str) == '+')
	{
		index = 1;
		if(*(str) == '-')
		{
			flag = 1;
		}
	}

	while(*(str+index) !='\0')
	{
		number = (number*10) + (*(str+index)-48);
		index++;
	}

	if(flag)
	{
		number *= -1;
	}

	return number;

}

int string_length(char* str)
{
	int length = 0;
	while(str[length] != '\0')
	{
		length++;
	}
	return length;
}

