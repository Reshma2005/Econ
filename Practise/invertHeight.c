#include"imageHeader.h"
int main()
{
	FILE *f = fopen("/home/econsys4/Reshma/Images/test1.bmp","r+");
        if(!f)
        {
                printf("Error in opening Image\n");
                return 0;
        }
        BMH* header = (BMH*)malloc(sizeof(BMH));
        char path[100];
        fread(header,sizeof(BMH),1,f);
        char* str = (char*)malloc(header->imageDataSize);
	fread(str,1,header->imageDataSize,f);
	printf("%d\n\n",header->height);

	header->height = header->height * (-1);
	stringReverse(str,header->imageDataSize);
	fclose(f);
	f = fopen("/home/econsys4/Reshma/Images/invertHead.bmp","w");
	fwrite(header,sizeof(BMH),1,f);
	fwrite(str,1,header->imageDataSize,f);
	fclose(f);
	BMH num = *header;


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

	return 0;


}
