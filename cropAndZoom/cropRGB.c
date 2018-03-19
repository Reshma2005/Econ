//#define HEADER 1
#include"imageHeader.h"
int crop(char *path)
{
	BMH* header = (BMH*)malloc(sizeof(BMH));
	if(!header)
	{
		printf("Memory allocation error for header\n");
		return 0;
	}
	FILE *f = openFile(path,"r");
	fread(header,sizeof(BMH),1,f);

	printf("\nHEIGHT:%d WIDTH:%d\n",header->height,header->width);
	int inpadding = (header->bmpFileSize-((header->height * header->width*BPP) + header->offset))/header->height;
	int padding = 0;
	printf("inpadding: %d\n",inpadding);
	int height,width,pHeight,pWidth;
	validateInput(&pHeight,&pWidth,&height,&width,header);
	if((width * (header->bitsPerPixel/8)) % 4 != 0)
	{
		padding = 4 - ((width * (header->bitsPerPixel/8)) % 4);
	}
	BMH* cropHeader = defineHeader(header,height,width,padding);
	if(!cropHeader)
	{
		free(header);
		return 0;
	}
	printf("padding: %d\n",padding);
	int pLocation = 0;
	pLocation = (pHeight * ((header->width * BPP) + inpadding)) + (pWidth * BPP);
	printf("pLocation: %d\n",pLocation);
	char *str = (char*)calloc((header->bmpFileSize-header->offset),1);
	if(!str)
	{
		printf("Memory allocation error for input buffer\n");
		free(header);
		free(cropHeader);
		return 0;
	}
	int move = (header->width) * BPP + inpadding;

	fread(str,1,(header->bmpFileSize-header->offset),f);
	int i=0,j=0,k=0;

	char *cropstr = (char*)malloc(cropHeader->bmpFileSize - cropHeader->offset);
	if(!cropstr)
	{
		printf("Memory allocation error for crop buffer\n");
		free(str);
		free(header);
		free(cropHeader);
		return 0;
	}
	
	while(i < height)
	{
		//printf("pLocation: %d j: %d\n",pLocation,j);
		cropString(str+pLocation,(width*BPP),cropstr+j);
		j += ((width)*BPP) + padding;
		//printf("str: %d\n",(pLocation+j));
		pLocation += (move);
		//printf("pLocation: %d j: %d\n",pLocation,j);
		i++;
	}

	f = fopen("crop.bmp","w");
	if(!f)
	{
		printf("Error in opening image for writing\n");
		free(str);
		free(header);
		free(cropHeader);
		return 0;
	}
	fwrite(cropHeader,sizeof(BMH),1,f);
	fwrite(cropstr,1,cropHeader->bmpFileSize-cropHeader->offset,f);
	fclose(f);
	free(str);


	free(cropstr);
	free(header);
	free(cropHeader);
	return 1;
}


BMH* defineHeader(BMH *src,int height,int width,int padding)
{
        if(!src)
        {
                printf("No Header!!!\n");
                return NULL;
        }
        BMH* des = (BMH*)malloc(sizeof(BMH));
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
        while(*pHeight > header->height || *pHeight < 0)
        {
                printf("Entered location error. Enter again:\n");
                scanf("%d",pHeight);
        }

        printf("Horizontal Location:");
        scanf("%d",pWidth);
        while(*pWidth > header->width || *pWidth < 0)
        {
                printf("Entered location error. Enter again:\n");
                scanf("%d",pWidth);
        }
        //(*pHeight)--;
        //(*pWidth)--;

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
        printf("%d\n",*pHeight);
        *pHeight = header->height - (*pHeight + *height);
        printf("%d\n",*pHeight);
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




