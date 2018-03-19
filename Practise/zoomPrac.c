#define HEADER 1
#include"imageHeader.h"
int main(int argc,char* argv[])
{
	int k,i=0;
	char *str,path[100];
	BGR **bgr;
	BMH *header = (BMH*)malloc(sizeof(BMH));
	FILE *f;
	f = fopen(argv[1],"r");
	while(!f)
	{
		printf("Error in openning image.\nEnter Again:\n");
		scanf("%s",path);
		f = fopen(path,"r");
	}
	fread(header,sizeof(BMH),1,f);
	int bpp = header->bitsPerPixel / 8;
	int padding = (header->bmpFileSize - (header->imageDataSize + header->offset)) / (header->height);
	str = (char*)malloc(header->imageDataSize * (padding*header->height));
	fread(str,1,header->imageDataSize,f);
	bgr = (BGR**)malloc(sizeof(BGR*)*(header->height));
	printf("Line End:");
	while(i < (header->height))
	{
		*(bgr+i) =(BGR*)(str + (i*((header->width*BPP) + (i*padding))));
		printf("%d ",(i*((header->width*BPP) + (i*padding))));
		i++;
	}
	k = string_to_number(argv[2]);
	printf("\nk: %d\n",k);
	char* zoom = ktimesZoom(bgr,header->height,header->width,k,&padding);
        int height = (k*(header->height-1))+1;
        int width = (k*(header->width-1))+1;
	BMH *zoomHeader;
	padding = 3;
	zoomHeader = defineHeader(header,height,width,padding);
	if(f)
		fclose(f);
/*	f = fopen(argv[3],"w");
	fwrite(zoomHeader,sizeof(BMH),1,f);
	fwrite(zoom,1,(zoomHeader->imageDataSize*bpp)+(padding*height),f);

	if(bgr)
		free(bgr);
	if(str)
		free(str);
	if(zoom)
		free(zoom);
	if(header)
		free(header);
	if(zoomHeader)
		free(zoomHeader);
	if(f)
		fclose(f);

*/









	return 0;
}


char* ktimesZoom(BGR** in,int height,int width,int k,int *padding)
{
	BGR *temp,*adj1,*adj2;
	unsigned int i,j,zi=0,zj=0;
	int zwidth = (k*(width -1)) + 1;
	int zheight = (k * (height - 1) + 1);
	//FILE *f = fopen("/home/econsys4/Reshma/Files/zoom.txt","w");
	*padding = 0;
	if((zwidth * BPP) % PADDING != ZERO)
	{
		*padding = PADDING - (zwidth * BPP) % PADDING;
	}
	char *zoom = (char*)calloc((zheight*((zwidth * BPP) + *padding)),1);
	BGR** out = (BGR**)malloc(sizeof(BGR*) * zheight);
	for(i=0;i<zheight;i++)
	{
		*(out+i) = (BGR*)(zoom + (i * ( *padding + (zwidth * BPP))));
	}
	for(i=0;i<height;i++)
	{
		zj = 0;
		for(j=0;j<width;j++)
		{
			(*(out+zi) + zj)->blue = (*(in+i) + j)->blue;
			(*(out+zi) + zj)->green = (*(in+i) + j)->green;
			(*(out+zi) + zj)->red = (*(in+i) + j)->red;
			zj += k;
		}
		zi += k;
	}
        for(i=0;i<zheight;i = i+k)
        {
                temp = *(out+i);
                for(j=k;j<zwidth;j = j+k)
                {
                        //printf("\nleft\n");
                        //fprintf(f,"i: %d j: %d ",i,j);
                        adj1 = temp;          //Left Adjacent pixel
                        adj2 = *(out+i)+j;    //Right Adjacent pixel
                        setZoomPixels(out,k,i,j-k,ROW,adj1,adj2);
                        //printf("\nright\n");
                        temp = adj2;
                }
        }

        for(j=0;j<zwidth;j++)
        {
                temp = *(out)+j;
                for(i=k;i<zheight;i = i+k)
                {
                        //fprintf(f,"i: %d j: %d ",i,j);
                        adj1 = temp;            //Upper Adjacent Pixel
                        adj2 = *(out+i)+j;     //Lower Adjacent Pixel
                        setZoomPixels(out,k,i-k,j,COL,adj1,adj2);
                        temp = adj2;
                        //fprintf(f,".");
                }
                //fprintf(f,"\n");
        }
        return zoom;


}


void setZoomPixels(BGR** zoom,int k,int row,int col,int flag,BGR* adj1,BGR* adj2)
{
	unsigned int i;
	unsigned char op,value;
	char *str = NULL;
	str = (char*)malloc(k-1);
//	printf("k-1: %d\n",k-1);
	if(str != NULL)
	{
		printf("Malloc Success\n");
	}
	if(adj1->blue > adj2->blue)
	{
		op = adj1->blue - adj2->blue;
		value = (op/k) + adj2->blue;
		printf("\n1.%d %d %d ",adj1->blue,value,adj2->blue);
	}
	else
	{
                op = adj2->blue - adj1->blue;
                value = (op/k) + adj1->blue;
                printf("\n2.%d %d %d ",adj1->blue,value,adj2->blue);

	}
	printf("\nValue:");
	for(i=0;i<k-1;i++)
	{
		printf("%d ",value);
		*(str+i) = value;
		value += op;
	}
	if(adj1->blue > adj2->blue)
	{
		stringReverse(str,k-1);
	}
	if(flag == ROW)
	{
		for(i=1;i<k;i++)
		{
			(*(zoom+row)+col+i)->blue = *(str+i-1);
		}
	}
	else
	{
		for(i=1;i<k;i++)
                {
                        (*(zoom+row+i)+col)->blue = *(str+i-1);
                }
	}

        if(adj1->green > adj2->green)
        {
                op = adj1->green - adj2->green;
                value = (op/k) + adj2->green;
        }
        else
        {
                op = adj2->green - adj1->green;
                value = (op/k) + adj1->green;

        }
	for(i=0;i<k-1;i++)
	{
		printf("%d ",value);
		*(str+i) = value;
		value += op;
	}
	printf("\n");
        if(adj1->green > adj2->green)
        {
                stringReverse(str,k-1);
        }
        if(flag == ROW)
        {
                for(i=1;i<k;i++)
                {
                        (*(zoom+row)+col+i)->green = *(str+i-1);
                }
        }
        else
        {
                for(i=1;i<k;i++)
                {
                        (*(zoom+row+i)+col)->green = *(str+i-1);
                }
        }

        if(adj1->red > adj2->red)
        {
                op = adj1->red - adj2->red;
                value = (op/k) + adj2->red;
        }
        else
        {
                op = adj2->red - adj1->red;
                value = (op/k) + adj1->red;

        }
	printf("\nValue:");
	for(i=0;i<k-1;i++)
	{
		printf("%d ",value);
		*(str+i) = value;
		value += op;
	}
	printf("\n");
        if(adj1->red > adj2->red)
        {
                stringReverse(str,k-1);
        }
        if(flag == ROW)
        {
                for(i=1;i<k;i++)
                {
                        (*(zoom+row)+col+i)->red = *(str+i-1);
                }
        }
        else
        {
                for(i=1;i<k;i++)
                {
                        (*(zoom+row+i)+col)->red = *(str+i-1);
                }
        }
        free(str);
        str = NULL;

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


void stringReverse(char* str,int n)
{
        int i = 0;
        char ch;
        while(i < (n/2))
        {
                ch = *(str+i);
                *(str+i) = *(str-i-1+n);
                *(str-i-1+n) = ch;
                i++;
        }

}




int string_to_number(char* str)
{
	if(string_length(str) == 0)
	{
	return 1;
	}
	if(string_length(str) == 1)
	{
		if(*(str) == '+')
		{
			return 1;
		}
		else if(*(str) == '-')
		{
			return -1;
		}
	}
	int index = 0,number = 0,flag = 0;
	if(*(str) == '-' || *(str) == '+')
	{
		index = 1;
		if(*(str) == '-')
		{
			flag = 1;
		}
	}

	while(*(str+index) !='\0')
	{
		number = (number*10) + (*(str+index)-48);
		index++;
	}

	if(flag)
	{
		number *= -1;
	}

	return number;

}

int string_length(char* str)
{
	int length = 0;
	while(str[length] != '\0')
	{
		length++;
	}
	return length;
}

