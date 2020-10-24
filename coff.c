// source of this file is Alexie Fru Osloader 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "coff.h"
#include "dos_exe.h"
// DJGPP exe is a modern exe but a stubbed coff for DOS
// lets check in a hackish way
// DJGPP stub has a go32stub string at 512 byte offset 
// which is a conformation in that case it is a COFF file
// and the COFF image starts at 2048 byte offset.
int is_DJ(unsigned char *ef)
{
	char djstr[10]="\0";
	strncpy(djstr,ef+512,8);
	djstr[8]='\0';
	printf("%s\n",djstr);
	if(strcmp(djstr,"go32stub")==0)
		return(1);
	return(0);
}
int is_coff(char *efile)
{
	COFF_HDR *chdr =(COFF_HDR*) efile;
	if(chdr->f_magic == 0x14C)
		return(1);
	else
		return(0);
}
void disp_coff_hdr(char *efile)
{
	if(efile==NULL)
	{
		error_msg(" File is not opened",__FILE__,__func__,__LINE__);
        	return;
	}
	int num_sects=0;
	COFF_HDR *coff_hdr;
	coff_hdr = (COFF_HDR*)efile;
	rpt_print("Magic",coff_hdr->f_magic);
	rpt_print("Number of sections",coff_hdr->f_nscns);
	num_sects = coff_hdr->f_nscns;
  	rpt_print("Symbol table offset",coff_hdr->f_symptr);
  	rpt_print("number of symtab entries",coff_hdr->f_nsyms);
  	rpt_print("Size of optional header",coff_hdr->f_opthdr);
  	rpt_print("flags",coff_hdr->f_flags);
	if(!coff_hdr->f_opthdr) 
	{
    		error_msg("Must have optional header.",__FILE__,__func__,__LINE__);
		return;
	}
	COFF_OPT_HDR  *coff_opt_hdr;
	coff_opt_hdr = (COFF_OPT_HDR *)(efile+sizeof(COFF_HDR));
	
	rpt_print("OPT Header magic",coff_opt_hdr->magic);
    	if(coff_opt_hdr->magic!=0x10B)
		printf("Not DJGPP COFF\n");
	else
		printf("DJGPP COFF\n");
		rpt_print("version stamp",coff_opt_hdr->vstamp);
    	rpt_print(".text size",coff_opt_hdr->tsize);
    	rpt_print(".data size",coff_opt_hdr->dsize);
    	rpt_print(".bss  size",coff_opt_hdr->bsize);
    	rpt_print("entry point",coff_opt_hdr->entry);
    	rpt_print("base of .text",coff_opt_hdr->text_start);
    	rpt_print("base of .data",coff_opt_hdr->data_start);
	
	for(int sects =0; sects<num_sects; sects++)
	{
		COFF_SECTION *sect;
		sect = (COFF_SECTION *)(efile+sizeof(COFF_HDR)+sizeof(COFF_OPT_HDR)+sects*sizeof(COFF_SECTION));
		printf("\tSection name : %s\n",sect->s_name);
      	rpt_print("Physical address",sect->s_paddr);
		rpt_print("Virtual  address",sect->s_vaddr);
		rpt_print("Section size",sect->s_size);
		rpt_print("File ptr to raw data",sect->s_scnptr);
		rpt_print("File ptr to relocation",sect->s_relptr);
		rpt_print("Num of relocation entries",sect->s_nreloc);
		rpt_print("Flags",sect->s_flags);
	}
			
}
