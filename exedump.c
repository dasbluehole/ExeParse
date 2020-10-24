#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dos_exe.h"
#include "peheader.h"
#include "ne_exe.h"
#include "lx_load.h"
#include "peheader.h"
#include "coff.h"
//signatures
/*#define MZ 0x5a4d
#define NE 0x454e
#define LX 0x584c
#define PE 0x4550
*/
// flag
int is_modern = 0; // 1 for type NE,LX,PE
int is_pe = 0;
int is_ne = 0;
int is_lx = 0;
int is_dj = 0;
int is_cf = 0;

void usage(const char* str)
{
        printf("USAGE %s <file.exe>\n",str);
        printf("file.exe should be DOS, OS/2 or Windows exe\n");
}

int main(int argc, char *argv[])
{
        printf("EXE file scanner\n");
        if(argc!=2)
        {
                usage(argv[0]);
                exit(0);
        }
        FILE *fp=NULL;
        fp = fopen(argv[1],"r");
        if(fp == NULL)
        {
                error_msg("unable to open file",__FILE__,__func__,__LINE__);
                exit(-1);
        }
        unsigned int sz=file_size(fp);
        //printf("\t\t\tSize of file= %u bytes\n",sz);
        if(sz<sizeof(generic_header))
        {
                printf("Error in EXE File\nSize is too small\n\n");
                fclose(fp);
                exit(-2);
        }
        
        unsigned char *efile=NULL;
        efile = (unsigned char *)valloc(sz);
        if(efile == NULL)
        {
                error_msg("Memory alocation error", __FILE__,__func__,__LINE__);
                fclose(fp);
                exit(-3);
        }
		rewind(fp);
        //we allocated a buffer of size equals the file size.
		//int ret_read =fread(efile,sz,1,fp);
		//printf("file load returns %ld \n",ret_read);
	if(fread(efile,sz,1,fp)!=1)
        {
	    error_msg("File Read error",__FILE__,__func__,__LINE__);
            free(efile);
            fclose(fp);
            exit(-4);
        }
        // ok now we have read all the contents from file
        // file handle is not needed any more
        fclose(fp);
        fp=NULL;
        #ifdef _DEBUG_
        int ret = is_valid_exe(efile);
        printf("ret = 0x%0x\n",ret);
        #endif
        if(!is_valid_exe(efile))
        {
		printf("Not a valid exe %s\n",argv[1]);
		printf("Checking if the file is a COFF file\n");
		is_cf = is_coff(efile);
		goto chk_coff;
	}
	printf("[ %s ]A valid exe file\n",argv[1]);
        display_dos_hdr_info(efile);
        
        if(is_modern_exe(efile)==1)
        {
                printf( "Seems to be a Modern EXE file\n");
                is_modern = 1;
        }
        else
        {
    		printf("\nDoesn't Seem to be a Modern EXE file\n");
    		printf("Checking if a DJGPP compiled exe or a COFF file...\n");
    		is_dj = is_DJ(efile);
    	}
chk_coff:
/*	if(is_coff(efile) == 0)
	{
		printf("Not a coff file...\n");
		goto error_exit;
	}
	else
	{
		is_cf = 1;
	//	is_modern =1; // well its not true ;)
	}*/
        if(is_modern)
        {
        /*
                unsigned short sig =read_signature(efile);
                printf("Signature : ");
                switch(sig)
                {
                        case NE : printf("NE file\n"); is_ne = 1;
                                        break;
                        case LX : printf("LX file\n"); is_lx = 1;
                                        break;
                        case PE : printf("PE file\n"); is_pe = 1;
                                        break;
                        default : printf("Unknown (0x%0x)\n",sig);
                }
         */
		is_ne = is_NE(efile);
		is_lx = is_LX(efile);
		is_pe = is_PE(efile);
	}
        pe_opt_hdr *oph=NULL;
        if(is_lx)
        {
		printf("\nLX file...\n");
                dump_lx_header(efile);
        }
        if(is_ne)
        {
    		printf("\nNE file...\n");
                dump_ne_header(efile);
        }
        if(is_pe)
        {
    		printf("\nPE file...\n");
                dump_pe_header_info(efile);
                oph = get_opt_hdr(efile);
                dump_opt_header_info(oph);
        }
	if(is_dj)
	{
		printf("\nDJGPP compiled file...\n");
		unsigned char *cof = efile+2048;
		disp_coff_hdr(cof);
	}
	if(is_cf)
	{
		printf("\nCOFF file...\n");
		disp_coff_hdr(efile);
	}
error_exit:
	
        //cleanup code
        //cleanup code
        if(fp!=NULL)
                fclose(fp);
        if(oph!=NULL)
                free(oph);
        if(efile!=NULL)
                free(efile);

        return(0);
}
