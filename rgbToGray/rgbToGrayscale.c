#include<stdlib.h>
#define SIZE 1000
#include<stdio.h>
#pragma pack(2)
#include"imageHeader.h"
int main(int argc,char* argv[])
{
        FILE *f = NULL,*grayScale = NULL;
        FILE *fp = fopen("Gray.bmp","rb");
        if(!fp)
        {
                printf("Error in opening Gray Image\n");
                return 0;
        }
        commandLine(argc,argv,&f,&grayScale);
        unsigned int j = 0,i = 0,k = 0;
        BMH *header = (BMH*)malloc(sizeof(BMH));
        int padding = 0,gpad = 0;
	fread(header,sizeof(struct bitMapHeader),1,fp);
	char* colorPallete = (char*)malloc(1024);
	fread(colorPallete,1,1024,fp);
	fclose(fp);
	fread(header,sizeof(struct bitMapHeader),1,f);
	if((header->height * header->width * 3) + header->offset != header->bmpFileSize)
        {
        	padding = (header->bmpFileSize - ((header->height * header->width * 3) + header->offset)) / header->height;
        }
        if(header->width % PADDING != ZERO)
        {
        	gpad = PADDING - (header->width % PADDING);
        } 
	BMH* gheader = defineHeader(header,header->height,header->width,gpad);
	printHeader(header);
	printHeader(gheader);
        char *str = (char*)malloc(header->bmpFileSize - header->offset);
        
        
        printf("\npadding: %d gpad: %d\n\n",padding,gpad);
        fread(str,1,header->bmpFileSize - header->offset,f);
        char *gray = (char*)calloc(gheader->bmpFileSize - gheader->offset,1);
        RGB** in = (RGB**)malloc(sizeof(RGB*) * header->height);
        for(i=0;i<header->height;i++)
	{
		*(in+i) = (RGB*)(str + (i * (padding + (header->width * 3))));
	}
        printf("%u\n",gheader->bmpFileSize - gheader->offset);
        for(i=0; i < header->height;i++)
        {
        	for(j=0; j <header->width ;j++)
        	{
        		*(gray+k) = (int)((((*(in+i)+j)->red) * 0.3) + (0.59 * ((*(in+i)+j)->green)) + (0.11 * ((*(in+i)+j)->blue)));
        		k++;
        	}
        	k += gpad;
        }
        printf("\nsize: %d\n",k); 
	fwrite(gheader,sizeof(struct bitMapHeader),1,grayScale);
	fwrite(colorPallete,1,1024,grayScale);
	fwrite(gray,1,k,grayScale);
	fclose(f);
	fclose(grayScale);
	free(str);
	free(colorPallete);
	free(gray);

	return 0;
}

void printHeader(BMH* num)
{

        printf("Signature: %x\n",num->signature);
        printf("Size of BMP File: %d\n",num->bmpFileSize);
        printf("Reserved1: %d\n",num->reserved1);
        printf("Reserved2: %d\n",num->reserved2);
        printf("Offset to start of image: %d\n",num->offset);
        printf("Size of Bitmap Info Header: %d\n",num->bitmapInfoHeaderSize);
        printf("Width: %d\n",num->width);
        printf("Height: %d\n",num->height);
        printf("Planes: %d\n",num->planes);
        printf("Bits per pixel: %d\n",num->bitsPerPixel);
        printf("Compression Type: %d\n",num->compressionType);
        printf("Size of Image data: %d\n",num->imageDataSize);
        printf("H Res: %d\n",num->horizontalResolution);
        printf("V Res: %d\n",num->verticalResolution);
        printf("No. of colors: %d\n",num->colors);
        printf("No. of imp colors: %d\n\n\n\n",num->importantColors);
}


	
FILE* openFile(char *path,char* mode)
{
	char str[100];
	FILE *f;
	if(!path)
	{
		printf("Enter: ");
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
        des->offset = 1078;
        des->bitmapInfoHeaderSize = src->bitmapInfoHeaderSize;
        des->height = height;
      	des->width = width;
        des->planes = src->planes;
        des->bitsPerPixel = 8;
        des->compressionType = src->compressionType;
        des->horizontalResolution = src->horizontalResolution;
        des->verticalResolution = src->verticalResolution;
        des->colors = src->colors;
        des->importantColors = src->importantColors;
        des->imageDataSize = height * width;
        des->bmpFileSize = des->imageDataSize + des->offset + (padding*height);
	return des;
}

void commandLine(int argc,char* argv[],FILE** f1,FILE** f2)
{
	if(argc < 2)
	{
		printf("Enter path for reading image:\n");
		*f1 = openFile(NULL,"r");
		printf("Enter path for writing image:\n");
		*f2 = openFile(NULL,"w");
		
	}
	else if(argc < 3)
	{
		*f1 = openFile(argv[1],"r");
		printf("Enter path for writing image:\n");
		*f2 = openFile(NULL,"w");
	}
	else if(argc == 3)	
	{
		*f1 = openFile(argv[1],"r");
		*f2 = openFile(argv[2],"w");
	}
	
}	


