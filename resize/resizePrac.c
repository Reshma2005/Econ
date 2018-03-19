#include"imageHeader.h"

void commandLine(int argc,char* argv[],FILE** f1,FILE** f2);
FILE* openFile(char *path,char* mode);

int main()
{
	FILE *f1 = NULL,*f2 = NULL;
	commandLine(argc,argv,&f1,&f2);
	int height,width,rheight,rwidth,padding = 0,rpadding = 0,skip = 0;
	BMH *header = NULL,*rHeader = NULL;
	unsigned char *str = NULL,*resize = NULL;
	unsigned int i = 0, j= 0;
	RGB **in = NULL,**out = NULL;
	header = (BMH*)malloc(sizeof(BMH));
	if(!header)
	{
		printf("Memory allocation Failed for Image Header\n");
		fclose(f1);
		fclose(f2);
		return 0;
	}
	fread(header,sizeof(BMH),1
	height = header->height;
	width = header->width;
	if((width * BPP) % PADDING != ZERO)
	{
		padding = PADDING - ((width * BPP) % PADDING);
	}
	str = (unsigned char*)malloc(header->bmpFileSize - header->offset);
	if(!str)
	{
		printf("Memory Allocation failed for input buffer\n");
		free(header);
		fclose(f1);
		fclose(f2);
		return 0;
	}
	fread(str,1,header->bmpFileSize - header->offset,f1);
	fclose(f1);
	printf("Enter new height and width\nHEIGHT:");
	scanf("%d",&rheight);
	printf("WIDTH:");
	scanf("%d",&rwidth);
	if((rwidth * BPP) % PADDING != ZERO)
        {
               rpadding = PADDING - ((rwidth * BPP) % PADDING);
        }
	rheader = defineHeader(header,rheight,rwidth,rpadding);
	if(!rheader)
	{
		printf("Memory Allocation failed for output buffer\n");
                free(header);
                free(str);
                fclose(f2);
                return 0;

	}
	resize = (unsigned char*)malloc((rheight * ((rwidth * BPP) + rpadding)));
	if(!resize)
	{
		printf("Memory Allocation failed for output buffer\n");
                free(header);
		free(str);
		fclose(f2);
		free(rheader);
		return 0;
	}
	in = (RGB**)malloc(sizeof(RGB*) * height);
	if(!in)
	{
		printf("Memory Allocation failed for input double pointer\n");
                free(header);
                free(str);
                fclose(f2);
                free(rheader);
		free(resize);
		return 0;
	}
	out = (RGB**)malloc(sizeof(RGB*) * rheight);
	if(!out)
	{
		printf("Memory Allocation failed for output double pointer\n");
                free(header);
                free(str);
                fclose(f2);
                free(resize);
                free(rheader);
		free(in);
		return 0;
	}
	for(i = 0;i<height;i++)
	{
		*(in + i) = (RGB*)(str+ i*((width * BPP) + padding));
	}
	for(i = 0;i<rheight;i++)
        {
                *(out + i) = (RGB*)(resize+ i*((rwidth * BPP) + rpadding));
        }

}

void resizeSmall(char* str,int rheight,int rwidth)
{



}



void resizeBig(char* str,int rheight,int rwidth)
{
}
void commandLine(int argc,char* argv[],FILE** f1,FILE** f2)
{
	if(argc < 2)
	{
		printf("Enter path for reading image:\n");
		*f1 = openFile(NULL,"r");
		printf("Enter path for writing image:\n");
		*f2 = openFile(NULL,"w");

	}
	else if(argc < 3)
	{
		*f1 = openFile(argv[1],"r");
		printf("Enter path for writing image:\n");
		*f2 = openFile(NULL,"w");
	}
	else if(argc == 3)
	{
		*f1 = openFile(argv[1],"r");
		*f2 = openFile(argv[2],"w");
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

