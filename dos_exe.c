//dos_exe.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dos_exe.h"

void error_msg(char* msg, char *source_file,const char *funcnam,int line_num)
{
	printf("%s :->in %s file in %s function at line %d\n",msg,source_file, funcnam, line_num);
	perror("Cause :");
}
int is_valid_exe(unsigned char *efile)
{
	dos_header *d = (dos_header *)efile;
	if(d->signature == MZ)
		return(1);
	return(0);
}
// it says if the executable is a modern executable.
int is_modern_exe(unsigned char *efile)
{
	if(!efile)
		return 0;
	dos_header *d = (dos_header *)efile;
	if(d->e_lfanew==0)
		return(0);
	return(1);
}

unsigned int file_size(FILE *in_fp)
{
    long f_size = 0;

    if(in_fp == NULL )
    {
		  error_msg(" File is not opened",__FILE__,__func__,__LINE__);
          goto ErrorReturn;
    }

    if( fseek( in_fp, 0L, SEEK_END ))
    {
		error_msg("Canot seek",__FILE__,__func__,__LINE__);
		goto ErrorReturn;
    }

    f_size = ftell( in_fp );
	rewind(in_fp);
ErrorReturn:

	return( f_size );

}
	
unsigned short read_signature(unsigned char *efile)
{
	// go to the file begining
	unsigned short sig=0;
	dos_header *d = (dos_header *)efile;
	efile += d->e_lfanew;
	sig = *((unsigned short*)efile);
	return(sig);
}
// exef is a buffer where the whole exefile is loaded.
void rpt_print(char *field, long val)
{ 
	printf( "%40.40s - %lu (0x%lx)\n", field,val,val); 
}

void display_dos_hdr_info(unsigned char *exef)
{
	dos_header *e = (dos_header *)exef;
	int sz = sizeof(dos_header);
	rpt_print("Size Of DOS Header",sz);
	printf( "%40.40s - %c%c (0x%lx)\n", "Signature", e->signature&0x00ff,(e->signature&0xff00)>>8,e->signature );
	rpt_print("Bytes in Last Block", e->bytes_in_last_block);
	rpt_print("number of blocks in file",e->blocks_in_file);
	rpt_print("Number of Relocations",e->num_relocs);
	rpt_print("Header paragraphs = %d",e->header_paragraphs);
	rpt_print("Minimum extra paragraphs = %d",e->min_extra_paragraphs);
	rpt_print("Maximum Extra paragraphs = %d",e->max_extra_paragraphs);
	rpt_print("SS =",e->ss);
	rpt_print("SP =",e->sp);
	rpt_print("Checksum =",e->checksum);
	rpt_print("IP =",e->ip);
	rpt_print("CS =",e->cs);
	rpt_print("Relocation table offset",e->reloc_table_offset);
	rpt_print("Overlay Number",e->overlay_number);
	rpt_print("OEM ID   = ",e->oemid);
	rpt_print("OEM INFO = ",e->oeminfo);
	rpt_print("Address of New Exe header ",e->e_lfanew); 
}
 
