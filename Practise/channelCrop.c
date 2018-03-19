#define HEADER 1
#include"imageHeader.h"
int main()
{
	FILE *red,*green,*blue,*cropImage;
	BMH *channel = (BMH*)malloc(sizeof(BMH));
	BMH *crop = (BMH*)malloc(sizeof(BMH));
	char *r,*g,*b,*rgb,path[100];
	int padding = 0;
	int vLoc,hLoc,height,width;
	int j=0,pLoc,i=0;
	BMH *header = (BMH*)malloc(sizeof(BMH));
	red = fopen("/home/econsys/Reshma/Images/red.bmp","r");
	green = fopen("/home/econsys/Reshma/Images/green.bmp","r");
	blue = fopen("/home/econsys/Reshma/Images/blue.bmp","r");
	fread(channel,sizeof(BMH),1,red);
	fseek(red,1024L,SEEK_CUR);
	fseek(green,1078L,SEEK_SET);
	fseek(blue,1078L,SEEK_SET);
	printf("Cropped Image Location:\n");
	scanf("%s",path);
	FILE *image = fopen(path,"r");
	fread(header,sizeof(BMH),1,image);
	validateInput(&vLoc,&hLoc,&height,&width,header);
	if((width * (header->bitsPerPixel/8)) % 4 != 0)
	{
		padding = 4 - ((width * (header->bitsPerPixel/8)) % 4);
	}
	crop = defineHeader(header,height,width,padding);
	r = (char*)malloc(channel->imageDataSize);
	g = (char*)malloc(channel->imageDataSize);
	b = (char*)malloc(channel->imageDataSize);
	rgb = (char*)malloc(header->imageDataSize + (height * padding));
	fread(r,1,channel->imageDataSize,red);
	fread(g,1,channel->imageDataSize,green);
	fread(b,1,channel->imageDataSize,blue);
	pLoc = (vLoc*channel->width) + hLoc;
	while(i < height)
	{
		cropString(rgb+j,r+pLoc,g+pLoc,b+pLoc,width,padding);
		pLoc += channel->width;
		j += (crop->width * 3) + padding;
		i++;
	}
	cropImage = fopen("/home/econsys4/Pictures/crop.bmp","w");
	fwrite(crop,sizeof(BMH),1,cropImage);
	fwrite(rgb,1,(crop->imageDataSize + (height * padding)),cropImage);
	fclose(red);
	fclose(green);
	fclose(blue);
	fclose(image);
	fclose(cropImage);
	free(r);
	free(g);
	free(b);
	free(rgb);
	free(header);
	free(crop);
	free(channel);




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


void cropString(char* rgb,char *red,char *green,char* blue,int width,int padding)
{
	int i = 0,j = 0;
	while(i < width)
	{
		*(rgb+j) = *(blue+i);
		*(rgb+j+1) = *(green + i);
		*(rgb+j+2)= *(red + i);
		j += 3;
		i++;
	}
	i = 0;
	if(padding)
	{
		while(i < padding)
		{
			*(rgb + j + i) = 0;
			i++;
		}
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
