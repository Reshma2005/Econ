#include"imageHeader.h"
int crop(char *path)
{
	char p[100];
	FILE *f = openFile(path,"r");
	int height,width,pHeight,pWidth,inpadding = 0,padding = 0,RETURN = 1;
	unsigned int pLocation = 0,i=0,j=0,k=0,move;
	BMH* header = NULL,*cropHeader = NULL;
	unsigned char *str = NULL,*cropstr = NULL;
	
	
	header = NULL;
	header = (BMH*)malloc(sizeof(BMH));
	if(!header)
	{
		printf("Memory allocation Failed for Image Header\n");
		return 0;
	}
	fread(header,sizeof(BMH),1,f);

	printf("\nHEIGHT:%d WIDTH:%d\n",header->height,header->width);
	inpadding = (header->bmpFileSize-((header->height * header->width*BPP) + header->offset))/header->height;
	str = (unsigned char*)calloc((header->bmpFileSize-header->offset),1);
	if(!str)
	{
		printf("Memory Allocation failed for input buffer\n");
		free(header);
		return 0;
	}
	fread(str,1,(header->bmpFileSize-header->offset),f);
	free(f);
	f = NULL;
	validateInput(&pHeight,&pWidth,&height,&width,header);
	if(pHeight == 0 && pWidth == 0 && height == header->height && width == header->width)
	{
		f = fopen("crop.bmp","w");
		fwrite(header,sizeof(BMH),1,f);
		fwrite(str,1,header->bmpFileSize-header->offset,f);
		RETURN = 1;
		goto FREE;
	}
	if((width * BPP) % PADDING != 0)
	{
		padding = PADDING - ((width * BPP) % PADDING);
	}
	cropHeader = defineHeader(header,height,width,padding);
	if(!cropHeader)
	{
		RETURN = 0;
		goto FREE;
	}
#ifdef DEBUG
	printf("pHeight: %d pWidth: %d\n",pHeight,pWidth);
#endif
	pLocation = (pHeight * ((header->width * BPP) + inpadding)) + (pWidth * BPP);
	move = (header->width) * BPP + inpadding;
	cropstr = (unsigned char*)calloc((cropHeader->bmpFileSize - cropHeader->offset),1);
	if(!cropstr)
	{
		printf("Memory Allocation failed for crop buffer\n");
		RETURN = 0;
		goto FREE;
		
	}
	
	while(i < height)
	{
		
		cropString(str+pLocation,(width*BPP),cropstr+j);
		j += ((width)*BPP) + padding;
		
		pLocation += (move);
		
		i++;
	}

	f = fopen("crop.bmp","w");
	fwrite(cropHeader,sizeof(BMH),1,f);
	fwrite(cropstr,1,cropHeader->bmpFileSize-cropHeader->offset,f);
	RETURN = 1;
	
	FREE:
	if(f)
	free(f);
	if(str)
	free(str);
	if(cropstr)
	free(cropstr);
	if(header)
	free(header);
	if(cropHeader)
	free(cropHeader);
	
	printf("return: %d\n",RETURN);
	return RETURN;
}


BMH* defineHeader(BMH *src,int height,int width,int padding)
{
        if(!src)
        {
                printf("No Header!!!\n");
                return NULL;
        }
        BMH* des = (BMH*)malloc(sizeof(BMH));
        if(!des)
        {
        	printf("Memory Allocation Failed for crop Header\n");
        	return NULL;
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
	return des;
}


void printHeader(BMH* des)
{
        BMH num = *des;
        printf("Signature:%x\n",num.signature);
        printf("Size of BMP File%d\n",num.bmpFileSize);
        printf("Zero:%d\n",num.reserved1);
        printf("Zero:%d\n",num.reserved2);
        printf("Offset to start of image: %d\n",num.offset);
        printf("Size of Bitmap Info Header: %d\n",num.bitmapInfoHeaderSize);
        printf("Width: %d\n",num.width);
        printf("Height: %d\n",num.height);
        printf("Planes: %d\n",num.planes);
        printf("Bits per pixel: %d\n",num.bitsPerPixel);
        printf("Compression Type: %d\n",num.compressionType);
        printf("Size of Image data: %d\n",num.imageDataSize);
        printf("H Res: %d\n",num.horizontalResolution);
        printf("V Res: %d\n",num.verticalResolution);
        printf("No. of colors: %d\n",num.colors);
        printf("No. of imp colors: %d\n\n\n\n",num.importantColors);
        
}

void cropString(char *str,int length,char* cropstr)
{
	int i = 0;
	while(i < length)
	{
		*(cropstr+i) = *(str+i);
		i++;
	}
	
}



void validateInput(int *pHeight,int* pWidth,int* height,int* width,BMH* header)
{
        printf("Enter pixel Location[x y]\nVertical Location:");
        scanf("%d",pHeight);
        while(*pHeight > header->height || *pHeight < 1)
        {
                printf("Entered location error. Enter again:\n");
                scanf("%d",pHeight);
        }

        printf("Horizontal Location:");
        scanf("%d",pWidth);
        while(*pWidth > header->width || *pWidth < 1)
        {
                printf("Entered location error. Enter again:\n");
                scanf("%d",pWidth);
        }
        (*pHeight)--;
        (*pWidth)--;

        printf("Enter the Height and width:\nHEIGHT:");
        scanf("%d",height);
        while((*height + *pHeight) > header->height)
        {
                printf("Entered height greater that image height. Enter again:\n");
                scanf("%d",height);
        }

        printf("WIDTH:");
        scanf("%d",width);
        while((*width + *pWidth) > header->width)
        {
                printf("Entered width greater that image width. Enter again:\n");
                scanf("%d",width);
        }
        *pHeight = header->height - (*pHeight + *height);
}

FILE* openFile(char *path,char* mode)
{
	char str[100];
	FILE *f;
	if(path == NULL)
	{
		printf("Enter:");
		scanf("%s",str);
		f = fopen(str,mode);
	}
	else
	{
		f = fopen(path,mode);
	}
	while(!f)
	{
			printf("Error in opening image. Enter path again:\n");
			scanf("%s",str);
			f = fopen(str,mode);
	}
	return f;
}





int commandLine(FILE** f,int argc,char* argv[])
{
	if(argc == 1)
	{
		printf("Enter path for reading image:\n");
		if(crop(NULL) == 0)
		{
			return 0;
		}
		printf("Enter path for writing image:\n");
		*f = openFile(NULL,"w");
		
	}
	else if(argc == 2)
	{
		if(crop(argv[1]) == 0)
		{
			return 0;
		}
		printf("Enter path for writing image:\n");
		*f = openFile(NULL,"w");
	}
	else if(argc == 3)	
	{
		if(crop(argv[1]) == 0)
		{
			return 0;
		}
		*f = openFile(argv[2],"w");
	}
}




int setZoomPixels(RGB** zoom,int k,int row,int col,int flag,RGB* adj1,RGB* adj2)
{
	unsigned int i;
	int op,value;
	unsigned char *str = NULL;
	str = (unsigned char*)malloc(k-1);
	if(!str)
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



