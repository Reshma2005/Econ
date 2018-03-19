#define HEADER 1
#include<stdlib.h>
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
int main(int argc,char* argv[])
{
	struct bitMapHeader num;
	FILE *f = fopen(argv[1],"r+");
	if(!f)
	{
		printf("Error in opening Image\n");
		return 0;
	}
        FILE *fp = fopen("/home/econsys4/Reshma/Images/Gray.bmp","rb");
        if(!fp)
        {
                printf("Error in opening Image Gray\n");
                return 0;
        }
        char* colorPallete = (char*)malloc(1024);
	fread(&num,sizeof(struct bitMapHeader),1,fp);
        fread(colorPallete,1,1024,fp);
	struct rgbChannel rgb;
	fread(&num,sizeof(struct bitMapHeader),1,f);
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
        printf("Bits per pixel: %d\n",num.bitsPerPixels);
        printf("Compression Type: %d\n",num.compressionType);
        printf("Size of Image data: %d\n",num.imageDataSize);
        printf("H Res: %d\n",num.horizontalResolution);
        printf("V Res: %d\n",num.verticalResolution);
        printf("No. of colors: %d\n",num.colors);
        printf("No. of imp colors: %d\n\n\n\n",num.importantColors);
#endif
	char *str = (char*)malloc(num.imageDataSize);
	fread(str,1,num.imageDataSize,f);
	num.bitsPerPixels = 8;
	num.imageDataSize = num.imageDataSize/3;
	num.offset = 1078;
	num.bmpFileSize = num.offset + num.imageDataSize;
        char *r = (char*)malloc(num.imageDataSize);
        char *b = (char*)malloc(num.imageDataSize);
        char *g = (char*)malloc(num.imageDataSize);
	int j = 0;
	int i = 0;
        while(j < num.imageDataSize)
        {
		*(b+j) = *(str+i);
		*(g+j) = *(str+i+1);
		*(r+j) = *(str+i+2);
		i += 3;
		j++;
        }
	//printf("i: %d j: %d\n",i,j);
	//printf("r:%s\n",r);
	fclose(f);
	char path[100];
	printf("Enter the path for creating red scale:\n");
	scanf("%s",path);
        FILE *red = fopen(path,"wb");
        printf("Enter the path for creating green scale:\n");
        scanf("%s",path);
        FILE *green = fopen(path,"wb");
        printf("Enter the path for creating blue scale:\n");
        scanf("%s",path);
        FILE *blue = fopen(path,"wb");
        fwrite(&num,sizeof(struct bitMapHeader),1,red);
        fwrite(&num,sizeof(struct bitMapHeader),1,green);
        fwrite(&num,sizeof(struct bitMapHeader),1,blue);
	fwrite(colorPallete,1,1024,red);
	fwrite(colorPallete,1,1024,green);
	fwrite(colorPallete,1,1024,blue);
	fwrite(r,1,num.imageDataSize,red);
	//printf("i: %d\n",i);
	fwrite(g,1,num.imageDataSize,green);
	fwrite(b,1,num.imageDataSize,blue);
	fclose(red);
	fclose(blue);
	fclose(green);
	//free(str);
	//free(r);
	//free(g);
	//free(b);


	red = fopen("/home/econsys4/Pictures/red.bmp","rb");
	green = fopen("/home/econsys4/Pictures/green.bmp","rb");
	blue = fopen("/home/econsys4/Pictures/blue.bmp","rb");
        if(!red || !blue || !green)
        {
                printf("No such file or directory\n");
                return 0;
        }

	fread(&num,sizeof(struct bitMapHeader),1,red);
        fread(&num,sizeof(struct bitMapHeader),1,green);
        fread(&num,sizeof(struct bitMapHeader),1,blue);

	fread(colorPallete,1,1024,red);
        fread(colorPallete,1,1024,green);
        fread(colorPallete,1,1024,blue);

	fread(r,1,num.imageDataSize,red);
	fread(b,1,num.imageDataSize,blue);
	fread(g,1,num.imageDataSize,green);

	i=0;
	j=0;
	while(j < num.imageDataSize)
	{
		*(str+i) = *(b+j);
		*(str+i+1) = *(g+j);
		*(str+i+2) = *(r+j);
		j++;
		i += 3;
	}
	num.imageDataSize *= 3;
	num.bitsPerPixels = 24;
	num.offset = 54;
	num.bmpFileSize = num.imageDataSize + num.offset;
        printf("Enter the path for creating combined scale output image:\n");
        scanf("%s",path);
        FILE *out = fopen(path,"wb");
	fwrite(&num,sizeof(struct bitMapHeader),1,out);
        fwrite(str,1,num.imageDataSize,out);
	fclose(out);
	fclose(red);
	fclose(blue);
	fclose(green);
	free(str);
	free(r);
	free(b);
	free(g);
	free(colorPallete);
	return 0;
}

