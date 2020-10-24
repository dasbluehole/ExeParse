//PE_exe.c
//functions to show pe file header info
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dos_exe.h"
#include "peheader.h"
uint32_t mybase=0;
int is_PE(unsigned char *efile)
{
	unsigned short sig =read_signature(efile);
	if(sig == PE)
		return(1);
	else
		return(0);
}
pe_hdr *get_pe_header(unsigned char *efile)
{
	if(!efile)
		return NULL;
	pe_hdr *peh = NULL;
	peh = (pe_hdr *)malloc(sizeof(pe_hdr));
	if(peh==NULL)
	{
		error_msg("Memory allocation error",__FILE__,__func__,__LINE__);
		return(NULL);
	}
	bzero(peh,sizeof(pe_hdr));
	dos_header *d = (dos_header *)efile;
	efile += d->e_lfanew;
	memcpy(peh,efile,sizeof(pe_hdr));
	return(peh);
}

void dump_pe_header_info(unsigned char *efile)
{
	if(!efile)
		return;
	mybase = efile;
	dos_header *d = (dos_header *)efile;
	efile += d->e_lfanew;
	pe_hdr *pe_exe = (pe_hdr *)efile;
	char *ptr;

	ptr = (char *)&pe_exe->sig;
	printf( "%40.40s - %c%c (0x%x)\n", "Signature", ptr[0], ptr[1], pe_exe->sig );
	char str[50]="";
	int i;
	for(i=0; i<26; i++)
	{
		if(m_id[i].val==pe_exe->machine_id )
		{
			strcpy(str,m_id[i].name);
			break;
		}
	}
	rpt_print(str,pe_exe->machine_id);
	rpt_print("Number of Sections",pe_exe->num_sections);
	rpt_print("Datetime Stamp",pe_exe->date_time_stamp);
	rpt_print("Symbol table pointer",pe_exe->symtab_pointer);
	rpt_print("Number of Symbols",pe_exe->num_symbols);
	rpt_print("Option Header Size",pe_exe->opt_header_size);
	rpt_print("File Characteristic",pe_exe->characteristic);
}
pe_opt_hdr *get_opt_hdr(unsigned char *efile)
{
	if(efile==NULL)
		return NULL;
	// opt header follows the pe header.
	// we have to find the offset of opt header
	long opt_offset = 0;
	dos_header *dh = (dos_header*)efile;
	opt_offset += dh->e_lfanew;
	opt_offset += sizeof(pe_hdr);
	unsigned char *data = efile + opt_offset;
	pe_opt_hdr *opt_hdr = NULL;
	opt_hdr = (pe_opt_hdr*)malloc(sizeof(pe_opt_hdr));
	if(opt_hdr==NULL)
	{
		error_msg("Memory allocation error",__FILE__,__func__,__LINE__);
		return(NULL);
	}
	bzero(opt_hdr,sizeof(pe_opt_hdr));
	memcpy(opt_hdr,data,sizeof(pe_opt_hdr));
	return (opt_hdr);
}
void dump_opt_header_info(pe_opt_hdr *opthdr)
{
	char mystr[20]="";
	printf("option Header Info\n");
	//rpt_print("Signature",opthdr->signature);
	if(opthdr->signature == 267)
		strcpy(mystr,"32-Bit");
	else if(opthdr->signature == 523)
		strcpy(mystr,"64-Bit");
	else if(opthdr->signature == 263)
		strcpy(mystr, "ROM Image");
	else
		strcpy(mystr, "Unknown");
	rpt_print(mystr,opthdr->signature);
	rpt_print("Major Linker Version",opthdr->MajorLinkerVersion);
	rpt_print("Minor Linker Version",opthdr->MinorLinkerVersion);
	rpt_print("Total Size of Code",opthdr->SizeOfCode);
	rpt_print("Total size Initializeed Data",opthdr->SizeOfInitializedData);
	rpt_print("Total Size of Uninitialized data",opthdr->SizeOfUninitializedData);
	rpt_print("Address of entry point",opthdr->AddressOfEntryPoint);
	rpt_print("Base of Code",opthdr->BaseOfCode);
	rpt_print("Base of Data",opthdr->BaseOfData);
	rpt_print("Image Base",opthdr->ImageBase);
	rpt_print("SectionAlignment",opthdr->SectionAlignment);
	rpt_print("FileAlignment",opthdr->FileAlignment);
	rpt_print("MajorOSVersion Required",opthdr->MajorOSVersion);
	rpt_print("MinorOSVersion",opthdr->MinorOSVersion);
	rpt_print("MajorImageVersion",opthdr->MajorImageVersion);
	rpt_print("MinorImageVersion",opthdr->MinorImageVersion);
	rpt_print("MajorSubsystemVersion",opthdr->MajorSubsystemVersion);
	rpt_print("MinorSubsystemVersion",opthdr->MinorSubsystemVersion);
	rpt_print("Win32VersionValue",opthdr->Win32VersionValue);
	rpt_print("SizeOfImage",opthdr->SizeOfImage);
	rpt_print("SizeOfHeaders",opthdr->SizeOfHeaders);
	rpt_print("Checksum",opthdr->Checksum);
	rpt_print("Subsystem",opthdr->Subsystem);
	rpt_print("DLLCharacteristics",opthdr->DLLCharacteristics);
	rpt_print("SizeOfStackReserve",opthdr->SizeOfStackReserve);
	rpt_print("SizeOfStackCommit",opthdr->SizeOfStackCommit);
	rpt_print("SizeOfHeapReserve",opthdr->SizeOfHeapReserve);
	rpt_print("SizeOfHeapCommit",opthdr->SizeOfHeapCommit);
	rpt_print("LoaderFlags(obsolete)",opthdr->LoaderFlags);
	rpt_print("NumberOfRvaAndSizes",opthdr->NumberOfRvaAndSizes);
	void (*entryFunction) () = (opthdr->AddressOfEntryPoint + mybase);
	//entryFunction();
}
	
