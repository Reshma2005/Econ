#include"imageHeader.h"
int main()
{
	FILE* f = fopen("/home/econsys4/Pictures/crop.bmp","r");
	BMH* header = (BMH*)malloc(sizeof(BMH));
	fread(header,sizeof(BMH),1,f);
	char *str = (char*)malloc(header->imageDataSize);
	fread(str,1,header->imageDataSize,f);
	fclose(f);
	f = fopen("/home/econsys4/Pictures/copy.bmp","w");
	fwrite(header,sizeof(BMH),1,f);
	fwrite(str,1,header->imageDataSize,f);
	free(header);
	free(str);
	return 0;
}
