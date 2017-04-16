#include <stdlib.h>
#include <stdio.h>

FILE * filer, * filew;
int numr,numw;
unsigned char buffer[1000000];
unsigned char header[100];
int cnt[300];

int	main(int argc, char ** argv)
{
	if((filer=fopen(argv[1],"rb"))==NULL){
		fprintf(stderr, "open read file error.\n");
		exit(1);
	}
	if((filew=fopen(argv[2],"wr"))==NULL){
		fprintf(stderr, "open write file error.\n");
		exit(1);
	}
	
	fread(header,1,54,filer);
	fwrite(header,1,54,filew);
	
	while(feof(filer)==0)
	{	
		if((numr=fread(buffer,1,1000000,filer))!=1000000)
		{
			if(ferror(filer)!=0)
			{
				fprintf(stderr,"read file error.\n");
				exit(1);
			}
			else if(feof(filer)!=0);
		}
	}	
	
	int i;
	for(i=0; i<numr; i++)	cnt[buffer[i]]++;
	
	for(i=0; i<260; i++)
	{
		if(cnt[i]!=0)	printf("%d : %d\n",i,cnt[i]);
	}	
		
	fwrite(header,1,54,filew);
	fwrite(buffer,1,numr,filew);
		
	fclose(filer);
	fclose(filew);
	
	
	return 0;
}
