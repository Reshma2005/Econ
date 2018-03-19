#include<stdlib.h>
#define SIZE 1000
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
int main(int argc,char* argv[])
{
        FILE *f = fopen(argv[1],"r+");
        if(!f)
        {
                printf("Error in opening Image\n");
                return 0;
	}
        FILE *fp = fopen("/home/econsys4/Reshma/Images/Gray.bmp","rb");
        if(!fp)
        {
                printf("Error in opening Gray Image\n");
                return 0;
        }
        struct bitMapHeader num;
	fread(&num,sizeof(struct bitMapHeader),1,fp);
	char* colorPallete = (char*)malloc(1024);
	fread(colorPallete,1,1024,fp);
	fread(&num,sizeof(struct bitMapHeader),1,f);
        char *str = (char*)malloc(num.imageDataSize);
        fread(str,1,num.imageDataSize,f);
        num.bitsPerPixels = 8;
        num.imageDataSize = num.imageDataSize/3;
	num.offset = 1078;
        num.bmpFileSize = num.offset + num.imageDataSize;
	//num.imageDataSize = num.imageDataSize/3;
	//num.imageDataSize = 0;
        char *gray = (char*)malloc(num.imageDataSize);
        int j = 0;
        int i = 0;
        while(j < num.imageDataSize)
        {
                *(gray+j) =(int)(((*(str+i+2)) * 0.3) + (0.59 * (*(str+i+1))) + (0.11 * (*(str+i))));
                i += 3;
                j++;
        }
        printf("Enter the path for Grayscale image:\n");
        char path[100];
        scanf("%s",path);

	FILE *grayScale = fopen(path,"wb");
	if(!grayScale)
	{
		printf("Error in opening the image to write\n");
		fclose(f);
	        free(str);
	        free(gray);
		return 0;
	}
	//num.imageDataSize = 0;
	fwrite(&num,sizeof(struct bitMapHeader),1,grayScale);
	fwrite(colorPallete,1,1024,grayScale);
	fwrite(gray,1,j,grayScale);
	fclose(f);
	fclose(grayScale);
	free(str);
	free(colorPallete);
	free(gray);

	return 0;
}
