#include"imageHeader.h"
#define DEBUG
void commandLine(int argc,char* argv[],FILE** f1,FILE** f2);
FILE* openFile(char *path,char* mode);

int main(int argc,char *argv[])
{
	FILE *f1 = NULL,*f2 = NULL;
	commandLine(argc,argv,&f1,&f2);
	int height,width,zheight,zwidth,padding = 0,zpadding = 0,k = 0;
	BMH *header = NULL,*zheader = NULL;
	unsigned char *str = NULL,*zoom = NULL;
	unsigned int i = 0, j= 0,x=0;
	RGB **in = NULL;
	header = (BMH*)malloc(sizeof(BMH));
	if(!header)
	{
		printf("Memory allocation Failed for Image Header\n");
		fclose(f1);
		fclose(f2);
		return 0;
	}
	fread(header,sizeof(BMH),1,f1);
	height = header->height;
	width = header->width;
	if((width * BPP) % PADDING != ZERO)
	{
		padding = PADDING - ((width * BPP) % PADDING);
	}
	str = (unsigned char*)malloc(header->bmpFileSize - header->offset);
	if(!str)
	{
		printf("Memory Allocation failed for input buffer\n");
		free(header);
		fclose(f1);
		fclose(f2);
		return 0;
	}
	fread(str,1,header->bmpFileSize - header->offset,f1);
	fclose(f1);

	printf("Enter the zoom out factor:\n");
	scanf("%d",&k);
	zwidth =(int)(((width -1) / k) + 1);
	zheight =(int)(((height -1) / k) + 1);
	printf("height: %d width: %d\n",height,width);
	printf("new height: %d new width: %d\n",zheight,zwidth);
	if((zwidth * BPP) % PADDING != ZERO)
        {
               zpadding = PADDING - ((zwidth * BPP) % PADDING);
        }
	zheader = defineHeader(header,zheight,zwidth,zpadding);
	if(!zheader)
	{
		printf("Memory Allocation failed for output buffer\n");
                free(header);
                free(str);
                fclose(f2);
                return 0;

	}
	zoom = (unsigned char*)calloc(zheader->bmpFileSize - zheader->offset,1);
	if(!zoom)
	{
		printf("Memory Allocation failed for output buffer\n");
                free(header);
		free(str);
		fclose(f2);
		free(zheader);
		return 0;
	}
	in = (RGB**)malloc(sizeof(RGB*) * height);
	if(!in)
	{
		printf("Memory Allocation failed for input double pointer\n");
                free(header);
                free(str);
                fclose(f2);
                free(zheader);
		free(zoom);
		return 0;
	}
	
	for(i = 0;i<height;i++)
	{
		*(in + i) = (RGB*)(str+ i*((width * BPP) + padding));
	}

	for(i = 0;i<zheight;i++)
	{
		for(j=0;j<zwidth;j++)
		{
			*(zoom+x) = (*(in+(i*k))+(j*k))->red;
                        *(zoom+x+1) = (*(in+(i*k))+(j*k))->green;
                        *(zoom+x+2) = (*(in+(i*k))+(j*k))->blue;
			x += 3;

		}
		x += zpadding;
	}
	fwrite(zheader,sizeof(BMH),1,f2);
	fwrite(zoom,1,zheader->bmpFileSize - zheader->offset,f2);
	free(header);
        free(str);
        fclose(f2);
        free(zoom);
       	free(zheader);
        free(in);
	return 0;

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

