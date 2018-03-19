#pragma once
#define PADDING 4
#define BPP 3
#include<stdlib.h>
#include<stdio.h>
#pragma pack(1)
struct bitMapHeader
{
        int signature : 16;
        unsigned int bmpFileSize;
        int reserved1 : 16;
        int reserved2 : 16;
        int offset;
        int bitmapInfoHeaderSize;
        int width;
        int height;
        int planes : 16;
        int bitsPerPixel : 16;
        int compressionType;
        unsigned int imageDataSize;
        int horizontalResolution;
        int verticalResolution;
        int colors;
        int importantColors;
};
struct rgbPixel
{
	unsigned char red;
	unsigned char green;
	unsigned char blue;
};
struct bgrPixel
{
	unsigned char blue;
	unsigned char green;
	unsigned char red;

};

typedef struct bitMapHeader BMH;
typedef struct rgbPixel RGB;
typedef struct bgrPixel BGR;

void printHeader(BMH* des);
void cropString(char *str,int length,char* cropstr);
BMH* defineHeader(BMH *src,int height,int width,int padding);
void validateInput(int *pHeight,int* pWidth,int* height,int* width,BMH* header);
FILE* openFile(char *path,char* mode);
void commandLine(int argc,char* argv[],FILE** f1,FILE** f2);
