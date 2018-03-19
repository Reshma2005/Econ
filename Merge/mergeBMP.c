#include"imageHeader.h"
#include<time.h>
void commandLine(FILE** f1,FILE** f2,FILE** f3,int argc,char* argv[]);
int main(int argc,char* argv[])
{
	clock_t t;
	t = clock();
	FILE *l,*r,*f;
	commandLine(&l,&r,&f,argc,argv);
	BMH *lheader = NULL,*rheader = NULL,*header = NULL;
	unsigned char *lImage = NULL,*rImage = NULL,*out = NULL;
	RGB **left = NULL,**right = NULL;
	unsigned int i = 0,j = 0,k = 0;
	int lpad = 0,rpad = 0,height,width,common = 0,padding = 0;
	lheader = (BMH*)malloc(sizeof(BMH));
	rheader = (BMH*)malloc(sizeof(BMH));
	if(!lheader || !rheader)
	{
		if(lheader)
		{
			free(lheader);
		}
		if(rheader)
		{
			free(rheader);
		}
		fclose(f);
		fclose(l);
		fclose(r);
		printf("Memory Allocation Error for header\n");
		return 0;
	}
	fread(lheader,sizeof(BMH),1,l);
	fread(rheader,sizeof(BMH),1,r);
	if(lheader->height != rheader->height)
	{
		printf("Heights dont match\n");
		free(rheader);
		free(lheader);
		return 0;
	}
	//printf("lwidth: %d rwidth: %d\n",lheader->width,rheader->width);
	height = lheader->height;
	lImage = (unsigned char*)malloc(lheader->bmpFileSize - lheader->offset);
	rImage = (unsigned char*)malloc(rheader->bmpFileSize - rheader->offset);
	if(!lImage || !rImage)
        {
                if(lImage)
                {
                        free(lImage);
                }
                if(rImage)
                {
                        free(rImage);
                }
		free(lheader);
		free(rheader);
		fclose(l);
		fclose(r);
		fclose(f);
                printf("Memory Allocation Error for input Image buffer\n");
                return 0;
        }
	fread(lImage,1,lheader->bmpFileSize - lheader->offset,l);
	fread(rImage,1,rheader->bmpFileSize - rheader->offset,r);
	fclose(l);
	fclose(r);

	if((lheader->width * BPP) % PADDING != ZERO)
	{
		lpad = PADDING - (lheader->width * BPP);
	}
	if((rheader->width * BPP) % PADDING != ZERO)
        {
                rpad = PADDING - (rheader->width * BPP);
        }

	left = (RGB**)malloc(lheader->height * sizeof(RGB*));
	right = (RGB**)malloc(rheader->height * sizeof(RGB*));
	if(!left || !right)
	{
		if(left)
		{
			free(left);
		}
		if(right)
		{
			free(right);
		}
		free(lheader);
		free(rheader);
		free(lImage);
		free(rImage);
		fclose(f);
	}


	for(i = 0;i < lheader->height;i++)
	{
		*(left+i) = (RGB*)(lImage + (i * ((lheader->width * BPP) + lpad)));
		*(right+i) = (RGB*)(rImage + (i * ((rheader->width * BPP) + rpad)));
	}

	for(j = (lheader->width - 1);j >= 0;j--)
	{
		for(i = 0;i < height;i++)
		{
			if((*(left+i)+j)->red != (*(right+i))->red || (*(left+i)+j)->green != (*(right+i))->green || (*(left+i)+j)->blue != (*(right+i))->blue)
			{
				break;
			}
		}
		if(i == height)
		{
			common = (lheader->width - j);
			//printf("\nlwidth: %d j: %d common: %d\n\n",lheader->width,j,common);
			break;
		}
	}
	width = lheader->width + rheader->width - common;
        //printf("lwidth: %d rwidth: %d common: %d width: %d\n",lheader->width,rheader->width,common,width);
	if((width * BPP) % PADDING != ZERO)
	{
		padding = PADDING - (width * BPP) % PADDING;
	}
	//printf("lpad: %d rpad: %d pad: %d\n\n",lpad,rpad,padding);
	out = (unsigned char*)calloc(height * ((width * BPP) + padding),1);
	if(!out)
	{
		printf("Memory allocation error for output buffer\n");
		free(lheader);
		free(rheader);
		free(lImage);
		free(rImage);
		free(left);
		free(right);
		fclose(f);
		return 0;
	}
	unsigned li = common;
	for(i = 0;i<height;i++)
	{
		for(j=0;j<width;j++)
		{
			if(j < lheader->width)
			{
				*(out + k) = (*(left+i)+j)->red;
				*(out + k+ 1) = (*(left+i)+j)->green;
				*(out + k+ 2) = (*(left+i)+j)->blue;
			}
			else
			{
				//rpad = j + common - lheader->width;
				*(out + k) = (*(right+i)+li)->red;
                                *(out + k+ 1) = (*(right+i)+li)->green;
                                *(out + k+ 2) = (*(right+i)+li)->blue;
				li++;
			}
			k += BPP;
		}
		k = k+padding;
		li = common;
	}
	//printf("\n");
	header = defineHeader(lheader,height,width,padding);
	if(!header)
	{
                free(lheader);
                free(rheader);
                free(lImage);
                free(rImage);
                free(left);
                free(right);
	        fclose(f);
		free(out);
	        return 0;

	}

	fwrite(header,sizeof(BMH),1,f);
	fwrite(out,1,header->bmpFileSize - header->offset,f);
	if(lheader)
		free(lheader);
	if(rheader)
                free(rheader);
	if(header)
		free(header);
	if(lImage)
                free(lImage);
	if(rImage)
                free(rImage);
	if(left)
                free(left);
	if(right)
                free(right);
	if(out)
		free(out);
	fclose(f);
	
	t = clock() - t;
	double time = ((double)t)/CLOCKS_PER_SEC;
	printf("\nExecution Time: %f ms\n",time*1000);
	return 0;

	

}



void commandLine(FILE** f1,FILE** f2,FILE** f3,int argc,char* argv[])
{
	if(argc == 1)
	{
		printf("Enter path for left image:\n");
		*f1 = openFile(NULL,"r");
		printf("Enter path for right image:\n");
		*f2 = openFile(NULL,"r");
		printf("Enter path for output image:\n");
		*f3 = openFile(NULL,"w");
	}
	else if(argc == 2)
	{
		*f1 = openFile(argv[1],"r");
		printf("Enter path for right image:\n");
		*f2 = openFile(NULL,"r");
		printf("Enter path for writing image:\n");
		*f3 = openFile(NULL,"w");
	}
	else if(argc == 3)
	{
		*f1 = openFile(argv[1],"r");
		*f2 = openFile(argv[2],"r");
		printf("Enter path for writing image:\n");
		*f3 = openFile(NULL,"w");
	}
	else
	{
		*f1 = openFile(argv[1],"r");
		*f2 = openFile(argv[2],"r");
		*f3 = openFile(argv[3],"w");
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

}

