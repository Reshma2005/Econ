//#define HEADER 1
#include"imageHeader.h"
int main(int argc,char* argv[])
{
	unsigned int pLocation = 0,move,i=0,j=0,k=0;
	int height,width,pHeight,pWidth,padding = 0,inpadding = 0;
	FILE *f = NULL,*f2 = NULL;
	BMH* header = NULL,*cropHeader = NULL;
	unsigned char *str = NULL,*cropstr = NULL;
	
	commandLine(argc,argv,&f,&f2);       //opens files stored as command line arguments
	header = (BMH*)malloc(sizeof(BMH));
	if(!header)
	{
		printf("Memory allocation Failed for Image Header\n");
		return 0;
	}
	fread(header,sizeof(BMH),1,f);
	
	str = (unsigned char*)calloc((header->bmpFileSize-header->offset),1);
	if(!str)
	{
		printf("Memory Allocation failed for input buffer\n");
		goto FREE;
	}
	fread(str,1,(header->bmpFileSize-header->offset),f);
	
	fclose(f);
	f = NULL;


	printf("\nHEIGHT:%d WIDTH:%d\n",header->height,header->width);
	
	
	validateInput(&pHeight,&pWidth,&height,&width,header);        //validates crop image dimentions
	
	
	if(pHeight == 0 && pWidth == 0 && height == header->height && width == header->width)
	{
		fwrite(header,sizeof(BMH),1,f2);
		fwrite(str,1,header->bmpFileSize-header->offset,f2);
		goto FREE;
	}
	
	inpadding = (header->bmpFileSize-((header->height * header->width*BPP) + header->offset))/header->height;
	if((width * BPP) % PADDING != 0)
	{
		padding = PADDING - ((width * BPP) % PADDING);
	}

	pLocation = (pHeight * ((header->width * BPP) + inpadding)) + (pWidth * BPP);	
	move = (header->width) * BPP + inpadding;

	cropHeader = defineHeader(header,height,width,padding);    //defines a header for the given height width and padding
	if(!cropHeader)
	{
		printf("Memory allocation Failed for Crop Image Header\n");
		goto FREE;
	}
	
	cropstr = (unsigned char*)calloc((cropHeader->bmpFileSize - cropHeader->offset),1);
	if(!cropstr)
	{
		printf("Memory Allocation failed for crop buffer\n");
		goto FREE;
		
	}
	
	while(i < height)
	{
		
		cropString(str+pLocation,(width*BPP),cropstr+j);
		j += ((width)*BPP) + padding;
		
		pLocation += (move);
		
		i++;
	}
	
	fwrite(cropHeader,sizeof(BMH),1,f2);
	fwrite(cropstr,1,cropHeader->bmpFileSize-cropHeader->offset,f2);
	
	
	FREE:
	if(f)
	free(f);
	if(f2)
	fclose(f2);
	if(str)
	free(str);
	if(cropstr)
	free(cropstr);
	if(header)
	free(header);
	if(cropHeader)
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
        printf("Signature: %x\n",num.signature);
        printf("Size of BMP File: %d\n",num.bmpFileSize);
        printf("Reserved1: %d\n",num.reserved1);
        printf("Reserved2: %d\n",num.reserved2);
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

