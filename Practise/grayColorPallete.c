#include<stdlib.h>
#define SIZE 1000
#define HEADER 1
#include<stdio.h>
#pragma pack(2)
struct bitMapHeader
{
        int signature : 16;
        int bmpFileSize;
        int reserved1 : 16;
        int reserved2 : 16;
        int offset;
        int bitmapInfoHeaderSize;
        int width;
        int height;
        int planes : 16;
        int bitsPerPixels : 16;
        int compressionType;
        int imageDataSize;
        int horizontalResolution;
        int verticalResolution;
        int colors;
        int importantColors;
};
#pragma pack(1)
struct rgbChannel
{
        unsigned char red;
        unsigned char green;
        unsigned char blue;
};
int main()
{
        FILE *f = fopen("/home/econsys4/Pictures/Gray.bmp","rb");
        if(!f)
        {
                printf("Error in opening Image\n");
                return 0;
	}
        struct bitMapHeader num;
	fread(&num,sizeof(struct bitMapHeader),1,f);
#ifdef HEADER
        printf("\nSignature:%x\n",num.signature);
        printf("Size of BMP File: %d\n",num.bmpFileSize);
        printf("Zero:%d\n",num.reserved1);
        printf("Zero:%d\n",num.reserved2);
        printf("Offset to start of image: %d\n",num.offset);
        printf("Size of Bitmap Info Header: %d\n",num.bitmapInfoHeaderSize);
        printf("Width: %d\n",num.width);
        printf("Height: %d\n",num.height);
        printf("Planes: %d\n",num.planes);
        printf("Bits per pixel: %d\n",num.bitsPerPixels);
        printf("Compression Type: %d\n",num.compressionType);
        printf("Size of Image data: %d\n",num.imageDataSize);
        printf("H Res: %d\n",num.horizontalResolution);
        printf("V Res: %d\n",num.verticalResolution);
        printf("No. of colors: %d\n",num.colors);
        printf("No. of imp colors: %d\n\n\n\n",num.importantColors);
#endif

	printf("%d\n",ftell(f));
        char *str = (char*)malloc(1024);
        int j = fread(str,1,1024,f);
	printf("%d\n",j);
      /*  j = 0;
        while(j < 1024)
        {
                printf("%x",*(str+j));
                j++;
        }
*/
return 0;
}
