#include"imageHeader.h"
char* resizeBig(char* str,int rheight,int rwidth)
{
	unsigned int i=0,j=0;
	int padding = 0,rpadding = 0;
	if(!str)
	{
		printf("Null ponter passed in resize Big function\n");
		return NULL;
	}
	BMH *header = (BMH*)str, rheader = NULL;
	if(rheight == header->height && rwidth == header->width)
	{
		return str;
	}
	int flag = 1,k1,k2;
	k1 = (int)((rwidth - 1) / (header->width - 1));
	k2 = (int)((rheight -1) / (header->height - 1));
	if((k1+1) - ((rwidth - 1) / (header->width - 1)) < 0.5)
	{
		k1++;
		flag = 3;
	}
	if((k2+1) - ((rheight -1) / (header->height - 1)) < 0.5)
	{
		k2++;
		if(flag == 3)
		flag = 2;
		else
		flag = 4;
	}
	str = zoomin(str,k1,k2);
	header = (BMH*)str;
	switch(flag)
	{
		case 2:
			return resizeSmall(str,rheight,rwidth);

		case 3:
			str = resizeSmall(rheight,header->width);

		case 4:
			str =  resizeSmall(header->height,rwidth);
	}
	header = (BMH*)str;
	inpadding 
	resize = (char*)calloc(
}
