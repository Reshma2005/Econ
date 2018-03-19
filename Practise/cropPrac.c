#define HEADER 1
#include"imageHeader.h"
int main(int argc,char* argv[])
{
	struct bitMapHeader num;
	FILE *f = fopen(argv[1],"r+");
	if(!f)
	{
		printf("Error in opening Image\n");
		return 0;
	}
	BMH* header = (BMH*)malloc(sizeof(BMH));
	char path[100];
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
	int height = 300,width = 1009,pHeight = 0,pWidth = 6;
	BMH* cropHeader = defineHeader(header,height,width);
	num = *cropHeader;
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

	char *s = (char*)malloc(cropHeader->imageDataSize);
	fseek(f,((pHeight)*(header->width)*3),SEEK_CUR);
	fseek(f,(pWidth*3),SEEK_CUR);
	int i = 0,j = 0;
	while(i < height)
	{
		fread(s+j,1,(width*3) - 3,f);
		j += (width*3) - 3;
		fseek(f,(((header->width - width)*3)-3),SEEK_CUR);
		i++;
	}


	FILE *fp = fopen("/home/econsys4/Reshma/Images/CropPrac.bmp","w");
        fwrite(cropHeader,sizeof(BMH),1,fp);
        fwrite(s,1,cropHeader->imageDataSize,fp);
	free(s);
	fclose(f);
	fclose(fp);


	return 0;
}



BMH* defineHeader(BMH *src,int height,int width)
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
	des->bmpFileSize = des->imageDataSize + des->offset;

	return des;
}

