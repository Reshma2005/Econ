
#include"cropRGB.c"
#include"imageHeader.h"
#define HEADER 1
int main(int argc,char* argv[])
{
	clock_t t;
	t = clock();
	printf("%s\n",__TIME__);
	BGR *temp,*adj1,*adj2;
	unsigned long i,j,zi = 0,zj = 0;
	int width=4,height=4,k = 1;
	unsigned int imageDataSize = 48,bmpFileSize = 102,offset = 54;
	int zwidth,zheight,padding = 0,inpadding =0;
	
	FILE *f2;
	if(commandLine(&f2,argc,argv) == 0)
	{
		return 0;
	}
	FILE *f = fopen("crop.bmp","r");
	if(!f)
	{
		printf("File cannot be opened\n");
		return 0;
	}
	BMH *header = (BMH*)malloc(sizeof(BMH));
	if(!header)
	{
		printf("Memory allocation Failed for Image Header\n");
		fclose(f);
		fclose(f2);
		remove("crop.bmp");
		return 0;
	}
	fread(header,sizeof(BMH),1,f);
	height = header->height;
	width = header->width;
	unsigned char *str = (unsigned char*)malloc(header->bmpFileSize - header->offset);
	if(!str)
	{
		printf("Memory Allocation failed for input buffer\n");
		free(header);
		fclose(f);
		fclose(f2);
		return 0;
	}
	fread(str,1,(header->bmpFileSize - header->offset),f);
	fclose(f);
	printf("Enter zoom factor:\n");
	scanf("%d",&k);
	if(k == 1)
	{
		printf("\nSame Size\n");
		fwrite(header,sizeof(BMH),1,f2);
		fwrite(str,1,(header->bmpFileSize - header->offset),f2);
		free(str);
		free(header);
		fclose(f2);
		return 0;
	}
	printf("height: %d Width: %d k: %d\n",header->height,header->width,k);
	zwidth = (k*(width -1)) + 1;
	zheight = (k * (height - 1)) + 1;
	printf("Zheight: %d Zwidth: %d\n",zheight,zwidth);
	
	if((zwidth * BPP) % PADDING != ZERO)
	{
		padding = PADDING - (zwidth * BPP) % PADDING;
	}
	if((width * BPP) % PADDING != ZERO)
	{
		inpadding = PADDING - (width * BPP) % PADDING;
	}
	unsigned char *zoom = (unsigned char*)calloc((zheight*((zwidth * BPP) + padding)),1);
	if(!zoom)
	{
		printf("Memory Allocation failure for Zoom buffer\n");
		free(header);
		free(str);
		fclose(f2);
		return 0;
	}
	BGR **in = (BGR**)malloc(sizeof(BGR*) * height);
	if(!in)
	{
		printf("Memory Allocation failure for double pointer\n");
		free(header);
		free(str);
		fclose(f2);
		free(zoom);
		return 0;
		
	}
	BGR** out = (BGR**)malloc(sizeof(BGR*) * zheight);
	if(!out)
	{
		printf("Memory Allocation failure for double pointer\n");
		free(header);
		free(str);
		fclose(f2);
		free(zoom);
		free(in);
		return 0;
	}
	for(i=0;i<height;i++)
	{
		*(in+i) = (BGR*)(str + (i * (inpadding + (width * BPP))));
	}
	for(i=0;i<zheight;i++)
	{
		*(out+i) = (BGR*)(zoom + (i * (padding + (zwidth * BPP))));
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
                        adj1 = temp;          //Left Adjacent pixel
                        adj2 = *(out+i)+j;    //Right Adjacent pixel
                        if(setZoomPixels(out,k,i,j-k,ROW,adj1,adj2) == 0)
                        {
                        	free(header);
				free(str);
				fclose(f2);
				free(zoom);
				free(in);
				free(out);
				return 0;
                        }
                        temp = adj2;
                }
        }
        
        for(j=0;j<zwidth;j++)
        {
                temp = *(out)+j;
                for(i=k;i<zheight;i = i+k)
                {
                        adj1 = temp;            //Upper Adjacent Pixel
                        adj2 = *(out+i)+j;     //Lower Adjacent Pixel
                        if(setZoomPixels(out,k,i-k,j,COL,adj1,adj2) == 0)
                        {
                        	free(header);
				free(str);
				fclose(f2);
				free(zoom);
				free(in);
				free(out);
				return 0;
                        }
                        temp = adj2;
                }
        }

	BMH *zheader = defineHeader(header,zheight,zwidth,padding);
	if(!zheader)
	{
		printf("Memory Allocation failure for double pointer\n");
		free(header);
		free(str);
		fclose(f2);
		free(zoom);
		free(in);
		free(out);
		return 0;
	}
	fwrite(zheader,sizeof(BMH),1,f2);
	fwrite(zoom,1,(zheader->bmpFileSize - zheader->offset),f2);
	fclose(f2);
	free(zoom);
	free(in);
	free(out);
	free(str);
	free(header);
	free(zheader);
	t = clock() - t;
	double time = ((double)t)/CLOCKS_PER_SEC;
	printf("\nExecution Time: %f ms\n",time*1000);
	return 0;

}



int setZoomPixels(BGR** zoom,int k,int row,int col,int flag,BGR* adj1,BGR* adj2)
{
	unsigned int i;
	int op,value;
	unsigned char *str = NULL;
	str = (unsigned char*)malloc(k-1);
	if(str == NULL)
	{
		printf("Memory Allocation failure for extra pixel bytes\n");
		return 0;
	}
	if(adj1->blue > adj2->blue)
	{
		op = (adj1->blue - adj2->blue)/k;
		value = (op) + adj2->blue;
		//printf("\n1.%d %d %d ",adj1->blue,value,adj2->blue);
	}
	else
	{
                op = (adj2->blue - adj1->blue)/k;
                value = (op) + adj1->blue;
                //printf("\n2.%d %d %d ",adj1->blue,value,adj2->blue);

	}
	//printf("\nValue:");
	for(i=0;i<k-1;i++)
	{
		//printf("%d ",value);
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
                op = (adj1->green - adj2->green)/k;
                value = (op) + adj2->green;
        }
        else
        {
                op = (adj2->green - adj1->green)/k;
                value = (op) + adj1->green;

        }
	for(i=0;i<k-1;i++)
	{
		//printf("%d ",value);
		*(str+i) = value;
		value += op;
	}
	//printf("\n");
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
                op = (adj1->red - adj2->red)/k;
                value = (op) + adj2->red;
        }
        else
        {
                op = (adj2->red - adj1->red)/k;
                value = (op) + adj1->red;

        }
	//printf("\nValue:");
	for(i=0;i<k-1;i++)
	{
		//printf("%d ",value);
		*(str+i) = value;
		value += op;
	}
	//printf("\n");
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
        return 1;

}

void stringReverse(unsigned char* str,int n)
{
        int i = 0;
        unsigned char ch;
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

