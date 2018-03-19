//#define HEADER 1
#include"imageHeader.h"
int main(int argc,char* argv[])
{
	struct bitMapHeader num;
	BMH* header = (BMH*)malloc(sizeof(BMH));
	FILE *f = fopen(argv[1],"r");
	if(!f)
	{
		printf("File cannot be opened\n");
		return 0;
	}
	fread(header,sizeof(BMH),1,f);
	num = *header;

#ifdef HEADER
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
#endif





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
	printf("padding: %d\n",padding);
	int pLocation = 0;
	printf("pHeight: %d pWidth: %d\n",pHeight,pWidth);
	pLocation = (pHeight * ((header->width * BPP) + inpadding)) + (pWidth * BPP);
	printf("pLocation: %d\n",pLocation);
	char *str = (char*)calloc((header->bmpFileSize-header->offset),1);
	int move = (header->width) * BPP + inpadding;

	fread(str,1,(header->bmpFileSize-header->offset),f);
//	char *temp = str+header->imageDataSize-1;
	int i=0,j=0,k=0;
//	stringReverse(str,header->imageDataSize);
	char *cropstr = (char*)malloc(cropHeader->bmpFileSize - cropHeader->offset);
	
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
//	stringReverse(cropstr,cropHeader->imageDataSize);
	//printf("Enter the loaction for the crop image:\n");
	//scanf("%s",path);
	f = fopen(argv[2],"w");
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
	return 0;
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


        BMH num = *des;
#ifdef HEADER
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
#endif


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
        printf("%d\n",*pHeight);
        *pHeight = header->height - (*pHeight + *height);
        printf("%d\n",*pHeight);
}
