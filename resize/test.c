#include"support.c"
#include"imageHeader.h"
#include"zoomOut.c"
#include"zoomIn.c"
int main()
{
	FILE *f = fopen("/home/econsys4/Pictures/2zoomin.bmp","r");
	fseek(f,0,SEEK_END);
	unsigned size = ftell(f);
	printf("Size: %d\n",size);
	rewind(f);
	char *str = (char*)malloc(size);
	fread(str,1,size,f);
	char* zoom = zoomout(str,2,3);
	BMH* header = (BMH*)zoom;
	FILE *f1 = fopen("/home/econsys4/Pictures/2zoomout.bmp","w");
	fwrite(zoom,1,header->bmpFileSize,f1);
	fclose(f);
	fclose(f1);
	return 0;
}
