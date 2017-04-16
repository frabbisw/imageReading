#include <stdlib.h>
#include <stdio.h>
#define BufferSize 1000000

struct FileHeader
{
	unsigned char Sign1;
	unsigned char Sign2;
	unsigned int FileSize;
	unsigned int Reserved;
	unsigned int DataOffset;
};
struct InfoHeader
{
	unsigned int Size;
	unsigned int Width;
	unsigned int Height;
	unsigned char Planes1;
	unsigned char Planes2;
	unsigned char BitCount1;
	unsigned char BitCount2;
	unsigned int Compression;
	unsigned int ImageSize;
	unsigned int XpixelsPerM;
	unsigned int YpixelsPerM;
	unsigned int ColorsUsed;
	unsigned int ColorsImportant;
};
struct Pixel
{
	unsigned char Red;
	unsigned char Green;
	unsigned char Blue;
};
struct Line
{
	struct Pixel *values;
	unsigned char garbage1;
	unsigned char garbage2;
};

FILE * filer, * filew;
int numr,numw;

char header[100];
char buffer[BufferSize];

struct FileHeader *fileheader = header;
struct InfoHeader *infoheader = header+14;
struct Pixel *pixels = header+54+24*3;  

void input()
{
	if((numr=fread(header,1,54,filer))!=BufferSize)
	{
		if(ferror(filer)!=0)
		{
			fprintf(stderr,"read file error-1.\n");
			exit(1);
		}
		else if(feof(filer)!=0);
	}
	if((numr=fread(buffer,1,BufferSize,filer))!=BufferSize)
	{
		if(ferror(filer)!=0)
		{
			fprintf(stderr,"read file error-2.\n");
			exit(1);
		}
		else if(feof(filer)!=0);
	}		
	fclose(filer);
}

void change()
{
	/*pixels
	int i;
	for(i=0; i<infoheader->Height; i++)
	{
		
	}
	
	/*struct Pixel *visit = pixels;
	int i;
	for(i=0; i<infoheader->Height*infoheader->Width; i++)
	{
		//pixels
	}
	
	/*
	//struct Pixel **k = &pixels;
	
	int i;
	for(i=0; i<infoheader->Height; i++)
	{
		//image[i]=&pixels[i*infoheader->Width+i*2];
		image[i]=pixels;//+i*infoheader->Width+i*2;
	}
	*/
	/*
	int i;
	for(i=0;i<infoheader->Height*infoheader->Width+2;i++)
	{
		struct Pixel p = pixels[i];
		printf("\t%d %d %d\n",p.Red,p.Green,p.Blue);
	}
	*/
}

void output()
{
	if((numw=fwrite(header,1,54,filew))!=54)
	{
		fprintf(stderr,"write file error-1.\n");
		exit(1);
	}		
	if((numw=fwrite(buffer,1,numr,filew))!=numr)
	{
		fprintf(stderr,"write file error-2.\n");
		exit(1);
	}
	fclose(filew);
}

int	main(int argc, char ** argv)
{
	if(argc!=3){
		fprintf(stderr,"USAGE: binary-test inputfile outputfile.\n");
		exit(1);
	}
	
	if((filer=fopen(argv[1],"rb"))==NULL){
		fprintf(stderr, "open read file error.\n");
		exit(1);
	}

	if((filew=fopen(argv[2],"wb"))==NULL){
		fprintf(stderr,"open write file error.\n");
		exit(1);
	}
	
	input();
	change();
	output();
	
	return 0;
}
