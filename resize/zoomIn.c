char* zoomin(char* str,int k1,int k2)
{
	RGB *temp,*adj1,*adj2;
	unsigned long i,j,zi = 0,zj = 0;
	BMH* header = (BMH*)str,*zheader = NULL;
	int width = header->width,height = header->height;
	unsigned int imageDataSize = 48,bmpFileSize,offset = 54;
	int zwidth = (k1*(width -1)) + 1,zheight = (k2 * (height - 1)) + 1,padding = 0,zpadding =0;
	
	if((zwidth * BPP) % PADDING != ZERO)
	{
		zpadding = PADDING - (zwidth * BPP) % PADDING;
	}
	if((width * BPP) % PADDING != ZERO)
	{
		padding = PADDING - (width * BPP) % PADDING;
	}
	bmpFileSize = zheight * ((zwidth * BPP) + zpadding) + header->offset;
	unsigned char *zoom = (unsigned char*)calloc(bmpFileSize,1);
	if(!zoom)
	{
		printf("Memory Allocation failure for Zoom in output buffer\n");
		return NULL;
	}
	zheader = (BMH*)zoom;
	defineHeader(header,zheader,zheight,zwidth,zpadding);
	
	RGB **in = (RGB**)malloc(sizeof(RGB*) * height);
	if(!in)
	{
		printf("Memory Allocation failure for double pointer in Zoom in\n");
		free(zoom);
		return NULL;
		
	}
	for(i = 0;i<height;i++)
	{
		*(in + i) = (RGB*)(str+ sizeof(BMH) + i*((width * BPP) + padding));
	}
	
	RGB** out = (RGB**)malloc(sizeof(RGB*) * zheight);
	if(!out)
	{
		printf("Memory Allocation failure for double pointer\n");
		free(zoom);
		free(in);
		return NULL;
	}
	for(i=0;i<zheight;i++)
	{
		*(out+i) = (RGB*)(zoom + sizeof(BMH) + (i * (zpadding + (zwidth * BPP))));
	}
	
	
	for(i=0;i<height;i++)
	{
		zj = 0;
		for(j=0;j<width;j++)
		{
			(*(out+zi) + zj)->blue = (*(in+i) + j)->blue;
			(*(out+zi) + zj)->green = (*(in+i) + j)->green;
			(*(out+zi) + zj)->red = (*(in+i) + j)->red;
			zj += k1;
		}
		zi += k2;
	}
	

        for(i=0;i<zheight;i = i+k2)
        {
                temp = *(out+i);
                for(j=k1;j<zwidth;j = j+k1)
                {
                        adj1 = temp;          //Left Adjacent pixel
                        adj2 = *(out+i)+j;    //Right Adjacent pixel
                        if(setZoomPixels(out,k1,i,j-k1,ROW,adj1,adj2) == 0)
                        {
				free(zoom);
				free(in);
				free(out);
				return NULL;
                        }
                        temp = adj2;
                }
        }
        
        for(j=0;j<zwidth;j++)
        {
                temp = *(out)+j;
                for(i=k2;i<zheight;i = i+k2)
                {
                        adj1 = temp;            //Upper Adjacent Pixel
                        adj2 = *(out+i)+j;     //Lower Adjacent Pixel
                        if(setZoomPixels(out,k2,i-k2,j,COL,adj1,adj2) == 0)
                        {
                   
				free(zoom);
				free(in);
				free(out);
				return NULL;
                        }
                        temp = adj2;
                }
        }
        free(in);
        free(out);
        free(str);
        return zoom;
}
