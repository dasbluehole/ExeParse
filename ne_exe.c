//ne_exe.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dos_exe.h"
#include "ne_exe.h"
int is_NE(unsigned char *efile)
{
	unsigned short sig =read_signature(efile);
	if(sig == NE)
		return(1);
	else
		return(0);
}
ne_hdr *read_ne_hdr_old(FILE *efile, ext_header *exh)
{
	ne_hdr *neh = NULL;
	neh = (ne_hdr *)malloc(sizeof(ne_hdr));
	if(neh==NULL)
	{
		error_msg("Memory allocation error",__FILE__,__func__,__LINE__);
		return(NULL);
	}
	bzero(neh,sizeof(ne_hdr));
	// go to the file begining
	rewind(efile);
	//advance to ext_header. e_lfanew  
	if((fseek(efile,exh->e_lfanew,SEEK_SET))!=0)
	{
		error_msg("File seek error",__FILE__,__func__,__LINE__);
		return(0);
	}
	if(1!=fread(neh,sizeof(ne_hdr),1,efile))
	{
		error_msg("File Read error",__FILE__,__func__,__LINE__);
		free(neh);
		return(NULL);
	}
	return(neh);
}
void dump_ne_header_old(ne_hdr *neh)
{
	printf("=====================NE Header===================\n");
	printf("Version                : %d \n",neh->ver);
	printf("Revision               : %d \n",neh->rev);
	printf("Entry Tbl offset       : %d \n",neh->enttab);
	printf("Entry table byte count : %d \n",neh->cbenttab);
	printf("Full EXE file CRC      : %ld \n",neh->crc);
	printf("Flags                  : %d \n",neh->flags);
	printf("Auto DATA Segment      : %d \n",neh->autodata);
	printf("HEAP Segmant           : %d \n",neh->heap);
	printf("STACK segment          : %d \n",neh->stack);
	printf("Initial Value IP reg   : %d \n",neh->ip);
	printf("Initial CS             : %d \n",neh->cs);
	printf("Initial SP             : %d \n",neh->sp);
	printf("Initial SS             : %d \n",neh->ss);
	printf("Number of segments     : %d\n",neh->nseg);
	printf("Number of Modules      : %d\n",neh->nmod);
	printf("Nonresident table byte count : %d\n",neh->cbnrestab);
	printf("File offset of Seg tab  : %d\n",neh->segtab);
	printf("File offset of rsrc tab : %d\n",neh->rsrctab);
	printf("File offset of mod tab  : %d\n",neh->modtab);
	printf("File offset of imp tab  : %d\n",neh->imptab);
	printf("File offset of non res name tab : %lu\n",neh->nrestab);
	printf("Number of movable entries       : %d\n",neh->nmovent);
	printf("Alignment of segments           : %d\n",neh->align);
	printf("Number of Items in res tab      : %d\n",neh->res_count);
	printf("=================================================\n");
}
ne_hdr *read_ne_hdr(unsigned char *efile)
{
	if(!efile)
		return NULL;
	ne_hdr *neh = NULL;
	neh = (ne_hdr *)malloc(sizeof(ne_hdr));
	if(neh==NULL)
	{
		error_msg("Memory allocation error",__FILE__,__func__,__LINE__);
		return(NULL);
	}
	bzero(neh,sizeof(ne_hdr));
	dos_header *d = (dos_header *)efile;
	efile += d->e_lfanew;
	memcpy(neh,efile,sizeof(ne_hdr));
	return(neh);
}

void dump_ne_header(unsigned char *efile)
{
	if(!efile)
		return;
	dos_header *d = (dos_header *)efile;
	efile += d->e_lfanew;
	ne_hdr *ne_exe = (ne_hdr *)efile;
	char *ptr;

	ptr = (char *)&ne_exe->sig;
	printf( "%40.40s - %c%c (0x%x)\n", "Signature", ptr[0], ptr[1], ne_exe->sig );
	rpt_print("Version",ne_exe->ver);
	rpt_print("Revision",ne_exe->rev);
	rpt_print("Entry Tbl offset",ne_exe->enttab);
	rpt_print("Entry table byte count",ne_exe->cbenttab);
	rpt_print("Full EXE file CRC",ne_exe->crc);
	rpt_print("Flags",ne_exe->flags);
	rpt_print("Auto DATA Segment",ne_exe->autodata);
	rpt_print("HEAP Segmant",ne_exe->heap);
	rpt_print("STACK segment",ne_exe->stack);
	rpt_print("Initial Value IP reg",ne_exe->ip);
	rpt_print("Initial CS",ne_exe->cs);
	rpt_print("Initial SP",ne_exe->sp);
	rpt_print("Initial SS",ne_exe->ss);
	rpt_print("Number of segments",ne_exe->nseg);
	rpt_print("Number of Modules",ne_exe->nmod);
	rpt_print("Nonresident table byte count",ne_exe->cbnrestab);
	rpt_print("File offset of Seg tab",ne_exe->segtab);
	rpt_print("File offset of rsrc tab",ne_exe->rsrctab);
	rpt_print("File offset of mod tab",ne_exe->modtab);
	rpt_print("File offset of imp tab",ne_exe->imptab);
	rpt_print("File offset of non res name tab",ne_exe->nrestab);
	rpt_print("Number of movable entries",ne_exe->nmovent);
	rpt_print("Alignment of segments",ne_exe->align);
	rpt_print("Number of Items in res tab",ne_exe->res_count);
	char str[15]="";
	switch(ne_exe->exetyp)
	{
		case NEUNK:
			strcpy(str,"UNKNOWN");
			break;
		case NE_OS2:
			strcpy(str,"IBM OS/2 NE");
			break;
		case NEWIND:
			strcpy(str,"Win3.0/3.1 NE");
			break;
		case DOS_4:
			strcpy(str,"DOS-4 NE");
			break;
		case WIN_386:
			strcpy(str,"Win 32");
			break;
		default:
			strcpy(str,"Unknown");
	}
	printf("%40.40s - %s(%ld)\n","OS Type",str,ne_exe->exetyp);
	rpt_print("Additional Flags",ne_exe->addflags);
	rpt_print("SDK Revision",ne_exe->sdkrev);
	rpt_print("SDK Version",ne_exe->sdkver);
}
