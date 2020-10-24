// remove dos stub
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include "dos_exe.h"

int main(int argc, char *argv[])
{
	if(argc<2)
	{
		printf("USAGE: %s <filename>\n",argv[0]);
		printf("filename is name of file whose\n stub has to be dealt with\n");
		printf("file should have a valid dos.exe header\n");
		exit(1);
	}
	FILE *infile = fopen(argv[1],"rb");
	if(infile == NULL)
	{
		perror("Unable to open file:");
		printf("\n%s\n",argv[1]);
		exit(-1);
	}
	dos_header *dhdr=(dos_header*)malloc(sizeof(dos_header));
	if(dhdr==NULL)
	{
		perror("Memory allocation: ");
		if(infile!=NULL)
			fclose(infile);
		exit(-2);
	}
	if(fread(dhdr,sizeof(dos_header),1,infile)!=1)
    {
		perror("File Read error: ");
		free(dhdr);
        fclose(infile);
        exit(-3);
    }
    if(dhdr->signature !=MZ)
    {
		printf("Not DOS Exe file: %s\n",argv[1]);
		fclose(infile);
		free(dhdr);
		exit(-30);
	}
    rewind(infile);
    if( fseek( infile, dhdr->e_lfanew+4, SEEK_SET ))
    {
		perror("Canot seek :");
		fclose(infile);
		free(dhdr);
		exit(-4);
    }
    char outnam[16]="";
    strncpy(outnam,argv[1],strchr(argv[1],'.')-argv[1]+1);
    strcat(outnam,"out");
    printf("outfile = %s\n",outnam);
    
    //we reached to the end of dos stub
    // now dump everything from this offset till file end
    
    FILE *outfile = fopen(outnam,"wb");
    if(outfile == NULL)
    {
		perror(" File open : ");
		fclose(infile);
		free(dhdr);
		exit(-5);
	}
    while(!feof(infile))
    {
		fputc(fgetc(infile),outfile);
	}
	fclose(outfile);
	
	fclose(infile);
	free(dhdr);
	return(0);
}
