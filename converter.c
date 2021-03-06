#include <stdlib.h>
#include <stdio.h>

#define BufferUnit 2500
#define BufferSize BufferUnit*BufferUnit

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
	unsigned char Blue;
	unsigned char Green;
	unsigned char Red;
};

FILE * filer, * filew;
int numr,numw;

char header[100];
char buffer[BufferSize];

struct FileHeader *fileheader = header;
struct InfoHeader *infoheader = header+14;
struct Pixel *image[BufferUnit];
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
	int i,j;
	for(i=0; i<infoheader->Height; i++)
	{
		for(j=0; j<infoheader->Width; j++)
		{
			image[i][j].Green=image[i][j].Red;
			image[i][j].Blue=image[i][j].Red;
			image[i][j].Red=image[i][j].Red;
		}
	}
}

void formArray()
{
	int i,j;
	for(i=0; i<infoheader->Height; i++)
	{
		image[i]=&buffer[i*(infoheader->Width)*sizeof(struct Pixel)];
	}
}

void output()
{
	if((numw=fwrite(header,1,54,filew))!=54)
	{
		fprintf(stderr,"failed to write head.\n");
		exit(1);
	}		
	if((numw=fwrite(buffer,1,numr,filew))!=numr)
	{
		fprintf(stderr,"failed to write buffer.\n");
		exit(1);
	}
	fclose(filew);
}

int	main(int argc, char ** argv)
{
	if(argc!=3){
		fprintf(stderr,"USAGE: ./converter inputfile outputfile\n");
		exit(1);
	}
	
	if((filer=fopen(argv[1],"rb"))==NULL){
		fprintf(stderr, "failed to open input file.\n");
		exit(1);
	}

	if((filew=fopen(argv[2],"wb"))==NULL){
		fprintf(stderr,"failed to open output file.\n");
		exit(1);
	}
	
	input();
	formArray();
	change();
	output();
	
	return 0;
}
