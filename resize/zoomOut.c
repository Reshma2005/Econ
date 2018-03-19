char* zoomout(char* str,int k1,int k2)
{
	if(!str)
	{
		printf("Null pointer in Zoom out function\n");
		return NULL;
	}
	int height,width,zheight,zwidth,padding = 0,zpadding = 0;
	BMH *header = (BMH*)str,*zheader = NULL;
	unsigned char *zoom = NULL;
	unsigned int i = 0, j= 0,x=0;
	RGB **in = NULL;
	char* out = NULL;
	
	height = header->height;
	width = header->width;
	zwidth =(int)(((width -1) / k1) + 1);
	zheight =(int)(((height -1) / k2) + 1);
	printf("height: %d width: %d\n",height,width);
	printf("new height: %d new width: %d\n",zheight,zwidth);
	if((zwidth * BPP) % PADDING != ZERO)
        {
               zpadding = PADDING - ((zwidth * BPP) % PADDING);
        }
	if((width * BPP) % PADDING != ZERO)
	{
		padding = PADDING - ((width * BPP) % PADDING);
	}
	//printf("height: %d Width: %d k: %d\n",height,width,k);
	
	printf("Zheight: %d Zwidth: %d\n",zheight,zwidth);
	
	unsigned int bmpFileSize = zheight * ((zwidth * BPP) + zpadding) + header->offset;
	out = (char*)calloc(bmpFileSize,1);
	if(!out)
	{
		printf("Memory Allocation failed for Zoom out output buffer\n");
		return NULL;
	}
	zheader = (BMH*)out;
	defineHeader(header,zheader,zheight,zwidth,zpadding);
	zoom = (unsigned char*)(out + sizeof(BMH));
	in = (RGB**)malloc(sizeof(RGB*) * height);
	if(!in)
	{
		printf("Memory Allocation failed for Zoom out input double pointer\n");
                //free(header);
                free(out);
                //fclose(f2);
                //free(zheader);
		//free(zoom);
		return NULL;
	}
	for(i = 0;i<height;i++)
	{
		*(in + i) = (RGB*)(str+ sizeof(BMH) + i*((width * BPP) + padding));
	}

	x = 0;
	for(i = 0;i<zheight;i++)
	{
		for(j=0;j<zwidth;j++)
		{
			*(zoom+x) = (*(in+(i*k2))+(j*k1))->red;
                        *(zoom+x+1) = (*(in+(i*k2))+(j*k1))->green;
                        *(zoom+x+2) = (*(in+(i*k2))+(j*k1))->blue;
			x += 3;

		}
		x += zpadding;
	}
	free(in);
	free(str);
	return out;
	
}
