//lx_exe.c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dos_exe.h"
#include "lx_load.h"

lx_hdr *read_lx_header_old(FILE *efile, ext_header *exh)
{
	lx_hdr *lxh = NULL;
	lxh = (lx_hdr *)malloc(sizeof(lx_hdr));
	if(lxh==NULL)
	{
		error_msg("Memory allocation error",__FILE__,__func__,__LINE__);
		return(NULL);
	}
	bzero(lxh,sizeof(lx_hdr));
	// go to the file begining
	rewind(efile);
	//advance to ext_header. e_lfanew  
	if((fseek(efile,exh->e_lfanew,SEEK_SET))!=0)
	{
		error_msg("File seek error",__FILE__,__func__,__LINE__);
		return(0);
	}
	if(1!=fread(lxh,sizeof(lx_hdr),1,efile))
	{
		error_msg("File Read error",__FILE__,__func__,__LINE__);
		free(lxh);
		return(NULL);
	}
	return(lxh);
}
void dump_lx_header_old(lx_hdr *lx_exe)
{
	char *ptr;

	ptr = (char *)&lx_exe->sig;
	printf( "%40.40s - %c%c (0x%x)\n", "magic", ptr[0], ptr[1], lx_exe->sig );
	printf( "%40.40s - %s %d (0x%x)\n", "Byte Order", 
			(lx_exe->byte_order&0x00FF)&BIG_ENDIAN?"BIG ENDIAN":"LITTLE ENDIAN", 
				(lx_exe->byte_order&0x00FF), (lx_exe->byte_order&0x00ff) );
	printf( "%40.40s - %s %d (0x%x)\n", "Word Order", 
		(lx_exe->word_order&0x00FF)&BIG_ENDIAN?"BIG ENDIAN":"LITTLE ENDIAN",
			(lx_exe->word_order&0x00FF), (lx_exe->word_order&0x00FF));
	printf( "%40.40s - %d (0x%x)\n", "Exe Format Level", lx_exe->lx_version, lx_exe->lx_version );
	switch( lx_exe->cpu_type )
		{
		case CPU_286:	ptr = "80286+"; break;
		case CPU_386:	ptr = "80386+"; break;
		case CPU_486:	ptr = "80486+"; break;
		case CPU_PENTIUM:	ptr = "PENTIUM+"; break;
		default:	ptr = "OTHER"; break;
		}
	printf( "%40.40s - %s %d (0x%x)\n", "Cpu Type", ptr, lx_exe->cpu_type, lx_exe->cpu_type );
	switch( lx_exe->os_type )
		{
		case OS_UNKNOWN:	ptr = "Unknown"; break;
		case OS_OS2:	ptr = "OS/2"; break;
		case OS_WIN:	ptr = "Windows Ref"; break;
		case OS_DOS4:	ptr = "DOS 4.X"; break;
		case OS_WIN386:	ptr = "Win386 Ref"; break;
		default:	ptr = "OTHER"; break;
		}
	printf( "%40.40s - %s %d (0x%x)\n", "OSType", ptr, lx_exe->os_type, lx_exe->os_type );
	printf( "%40.40s - %lu (0x%lx)\n", "ModuleVersion", lx_exe->module_version, lx_exe->module_version );
	printf( "%40.40s - %lu (0x%lx)\n", "ModFlags", lx_exe->module_flags, lx_exe->module_flags );
	printf( "%40.40s - %lu (0x%lx)\n", "ModNumPgs", lx_exe->module_num_pages, lx_exe->module_num_pages );
	printf( "%40.40s - %lu (0x%lx)\n", "EIPObjNum", lx_exe->eip_object, lx_exe->eip_object );
	printf( "%40.40s - %lu (0x%lx)\n", "EIP", lx_exe->eip, lx_exe->eip );
	printf( "%40.40s - %lu (0x%lx)\n", "ESPObjNum", lx_exe->esp_object, lx_exe->esp_object );
	printf( "%40.40s - %lu (0x%lx)\n", "Esp", lx_exe->esp, lx_exe->esp );
	printf( "%40.40s - %lu (0x%lx)\n", "PgSize", lx_exe->page_size, lx_exe->page_size );
	printf( "%40.40s - %lu (0x%lx)\n", "PgOfsShift", lx_exe->page_offset_shift, lx_exe->page_offset_shift );
	printf( "%40.40s - %lu (0x%lx)\n", "FixupSectionSize", lx_exe->fixup_section_size, lx_exe->fixup_section_size );
	printf( "%40.40s - %lu (0x%lx)\n", "FixupCksum", lx_exe->fixup_section_checksum, lx_exe->fixup_section_checksum);
	printf( "%40.40s - %lu (0x%lx)\n", "LdrSecSize", lx_exe->loader_section_size, lx_exe->loader_section_size );
	printf( "%40.40s - %lu (0x%lx)\n", "LdrSecCksum", lx_exe->loader_section_checksum, lx_exe->loader_section_checksum );
	printf( "%40.40s - %lu (0x%lx)\n", "ObjTblOfs", lx_exe->object_page_table_offset, lx_exe->object_table_offset );
	printf( "%40.40s - %lu (0x%lx)\n", "NumObjects", lx_exe->module_num_objects, lx_exe->module_num_objects );
	printf( "%40.40s - %lu (0x%lx)\n", "ObjPgTblOfs", lx_exe->object_page_table_offset, lx_exe->object_page_table_offset );
	printf( "%40.40s - %lu (0x%lx)\n", "ObjIterPgsOfs", lx_exe->object_iter_pages_offset, lx_exe->object_iter_pages_offset );
	printf( "%40.40s - %lu (0x%lx)\n", "RscTblOfs", lx_exe->resource_table_offset, lx_exe->resource_table_offset );
	printf( "%40.40s - %lu (0x%lx)\n", "NumRscTblEnt", lx_exe->num_resource_table_entries, lx_exe->num_resource_table_entries );
	printf( "%40.40s - %lu (0x%lx)\n", "ResNameTblOfs", lx_exe->resident_name_table_offset, lx_exe->resident_name_table_offset );
	printf( "%40.40s - %lu (0x%lx)\n", "EntryTblOfs", lx_exe->entry_table_offset, lx_exe->entry_table_offset );
	printf( "%40.40s - %lu (0x%lx)\n", "ModDirOfs", lx_exe->module_directives_offset, lx_exe->module_directives_offset );
	printf( "%40.40s - %lu (0x%lx)\n", "NumModDirs", lx_exe->num_module_directives, lx_exe->num_module_directives );
	printf( "%40.40s - %lu (0x%lx)\n", "FixupPgTblOfs", lx_exe->fixup_page_table_offset, lx_exe->fixup_page_table_offset );
	printf( "%40.40s - %lu (0x%lx)\n", "FixupRecTblOfs", lx_exe->fixup_record_table_offset, lx_exe->fixup_record_table_offset );
	printf( "%40.40s - %lu (0x%lx)\n", "ImpModTblOfs", lx_exe->import_module_table_offset, lx_exe->import_module_table_offset );
	printf( "%40.40s - %lu (0x%lx)\n", "NumImpModEnt", lx_exe->num_import_mod_entries, lx_exe->num_import_mod_entries );
	printf( "%40.40s - %lu (0x%lx)\n", "ImpProcTblOfs", lx_exe->import_proc_table_offset, lx_exe->import_proc_table_offset);
	printf( "%40.40s - %lu (0x%lx)\n", "PerPgCksumOfs", lx_exe->per_page_checksum_offset, lx_exe->per_page_checksum_offset );
	printf( "%40.40s - %lu (0x%lx)\n", "DataPgOfs", lx_exe->data_pages_offset, lx_exe->data_pages_offset );
	printf( "%40.40s - %lu (0x%lx)\n", "NumPreloadPg", lx_exe->num_preload_pages, lx_exe->num_preload_pages );
	printf( "%40.40s - %lu (0x%lx)\n", "NResNameTblOfs", lx_exe->non_resident_name_table_offset, lx_exe->non_resident_name_table_offset);
	printf( "%40.40s - %lu (0x%lx)\n", "NResNameTblLen", lx_exe->non_resident_name_table_len, lx_exe->non_resident_name_table_len);
	printf( "%40.40s - %lu (0x%lx)\n", "NResNameTblCksum", lx_exe->non_resident_name_table_checksum, lx_exe->non_resident_name_table_checksum);
	printf( "%40.40s - %lu (0x%lx)\n", "AutoDSObj", lx_exe->auto_ds_object_num, lx_exe->auto_ds_object_num );
	printf( "%40.40s - %lu (0x%lx)\n", "DebugInfoOfs", lx_exe->debug_info_offset, lx_exe-> debug_info_offset );
	printf( "%40.40s - %lu (0x%lx)\n", "DebugInfoLen", lx_exe->debug_info_len, lx_exe->debug_info_len);
	printf( "%40.40s - %lu (0x%lx)\n", "NumInstPreload", lx_exe->num_instance_preload, lx_exe->num_instance_preload );
	printf( "%40.40s - %lu (0x%lx)\n", "NumInstDemand", lx_exe->num_instance_demand, lx_exe->num_instance_demand );
	printf( "%40.40s - %lu (0x%lx)\n", "HeapSize", lx_exe->heapsize, lx_exe->heapsize );
	printf( "%40.40s - %lu (0x%lx)\n", "StackSize", lx_exe->stacksize, lx_exe->stacksize );

	if( lx_exe->module_flags & MODF_RESERVED1 )
		printf( "Module flag MODF_RESERVED1 set\n" );
	if( lx_exe->module_flags & MODF_RESERVED2 )
		printf( "Module flag MODF_RESERVED2 set\n" );
	if( lx_exe->module_flags & MODF_PERPROCLIB )
		printf( "Module flag MODF_PERPROCLIB set\n" );
	if( lx_exe->module_flags & MODF_RESERVED3 )
		printf( "Module flag MODF_RESERVED3 set\n" );
	if( lx_exe->module_flags & MODF_INTERNALFIX )
		printf( "Module flag MODF_INTERNALFIX set\n" );
	if( lx_exe->module_flags & MODF_EXTERNALFIX )
		printf( "Module flag MODF_EXTERNALFIX set\n" );
	if( lx_exe->module_flags & MODF_RESERVED4 )
		printf( "Module flag MODF_RESERVED4 set\n" );
	if( lx_exe->module_flags & MODF_RESERVED5 )
		printf( "Module flag MODF_RESERVED5 set\n" );
	if( lx_exe->module_flags & MODF_NOWINCOMPAT )
		printf( "Module flag MODF_NOWINCOMPAT set\n" );
	if( lx_exe->module_flags & MODF_WINCOMPAT )
		printf( "Module flag MODF_WINCOMPAT set\n" );
	if( lx_exe->module_flags & MODF_USESWINAPIU )
		printf( "Module flag MODF_USESWINAPIU set\n" );
	if( lx_exe->module_flags & MODF_RESERVED6 )
		printf( "Module flag MODF_RESERVED6 set\n" );
	if( lx_exe->module_flags & MODF_RESERVED7 )
		printf( "Module flag MODF_RESERVED7 set\n" );
	if( lx_exe->module_flags & MODF_RESERVED8 )
		printf( "Module flag MODF_RESERVED8 set\n" );
	if( lx_exe->module_flags & MODF_NOTLOADABLE )
		printf( "Module flag MODF_NOTLOADABLE set\n" );
	if( lx_exe->module_flags & MODF_RESERVED9 )
		printf( "Module flag MODF_RESERVED9 set\n" );
	if( lx_exe->module_flags & MODF_PERPROCLIBTERM )
		printf( "Module flag MODF_PERPROCLIBTERM is set.\n" );
	if( lx_exe->module_flags & MODF_TYPEMASK == MODF_TYPPROGRAM )
		printf( "EXE is a PROGRAM\n" );
	if( lx_exe->module_flags & MODF_TYPEMASK == MODF_TYPLIBRARY )
		printf( "EXE is a LIBRARY\n" );
	if( lx_exe->module_flags & MODF_TYPEMASK == MODF_TYPPROTMEMLIB )
		printf( "EXE is a PROTMEMLIB\n" );
	if( lx_exe->module_flags & MODF_TYPEMASK == MODF_TYPPHYSDEV )
		printf( "EXE is a PHYSDEV\n" );
	if( lx_exe->module_flags & MODF_TYPEMASK == MODF_TYPVIRTDEV )
		printf( "EXE is a VIRTDEV\n" );
}
lx_hdr *read_lx_header(unsigned char *efile)
{
	if(!efile)
		return NULL;
	lx_hdr *lxh = NULL;
	lxh = (lx_hdr *)malloc(sizeof(lx_hdr));
	if(lxh==NULL)
	{
		error_msg("Memory allocation error",__FILE__,__func__,__LINE__);
		return(NULL);
	}
	bzero(lxh,sizeof(lx_hdr));
	dos_header *d = (dos_header *)efile;
	efile += d->e_lfanew;
	memcpy(lxh,efile,sizeof(lx_hdr));
	return(lxh);
}
void dump_lx_header(unsigned char *efile)
{
	if(!efile)
		return;
	dos_header *d = (dos_header *)efile;
	efile += d->e_lfanew;
	lx_hdr *lx_exe = (lx_hdr *)efile;
	char *ptr;

	ptr = (char *)&lx_exe->sig;
	printf( "%40.40s - %c%c (0x%x)\n", "magic", ptr[0], ptr[1], lx_exe->sig );
	printf( "%40.40s - %s %d (0x%x)\n", "Byte Order", 
			(lx_exe->byte_order&0x00FF)&BIG_ENDIAN?"BIG ENDIAN":"LITTLE ENDIAN", 
				(lx_exe->byte_order&0x00FF), (lx_exe->byte_order&0x00ff) );
	printf( "%40.40s - %s %d (0x%x)\n", "Word Order", 
		(lx_exe->word_order&0x00FF)&BIG_ENDIAN?"BIG ENDIAN":"LITTLE ENDIAN",
			(lx_exe->word_order&0x00FF), (lx_exe->word_order&0x00FF));
	printf( "%40.40s - %d (0x%x)\n", "Exe Format Level", lx_exe->lx_version, lx_exe->lx_version );
	switch( lx_exe->cpu_type )
		{
		case CPU_286:	ptr = "80286+"; break;
		case CPU_386:	ptr = "80386+"; break;
		case CPU_486:	ptr = "80486+"; break;
		case CPU_PENTIUM:	ptr = "PENTIUM+"; break;
		default:	ptr = "OTHER"; break;
		}
	printf( "%40.40s - %s %d (0x%x)\n", "Cpu Type", ptr, lx_exe->cpu_type, lx_exe->cpu_type );
	switch( lx_exe->os_type )
		{
		case OS_UNKNOWN:	ptr = "Unknown"; break;
		case OS_OS2:	ptr = "OS/2"; break;
		case OS_WIN:	ptr = "Windows Ref"; break;
		case OS_DOS4:	ptr = "DOS 4.X"; break;
		case OS_WIN386:	ptr = "Win386 Ref"; break;
		default:	ptr = "OTHER"; break;
		}
	printf( "%40.40s - %s %d (0x%x)\n", "OSType", ptr, lx_exe->os_type, lx_exe->os_type );
	printf( "%40.40s - %lu (0x%lx)\n", "ModuleVersion", lx_exe->module_version, lx_exe->module_version );
	printf( "%40.40s - %lu (0x%lx)\n", "ModFlags", lx_exe->module_flags, lx_exe->module_flags );
	printf( "%40.40s - %lu (0x%lx)\n", "ModNumPgs", lx_exe->module_num_pages, lx_exe->module_num_pages );
	printf( "%40.40s - %lu (0x%lx)\n", "EIPObjNum", lx_exe->eip_object, lx_exe->eip_object );
	printf( "%40.40s - %lu (0x%lx)\n", "EIP", lx_exe->eip, lx_exe->eip );
	printf( "%40.40s - %lu (0x%lx)\n", "ESPObjNum", lx_exe->esp_object, lx_exe->esp_object );
	printf( "%40.40s - %lu (0x%lx)\n", "Esp", lx_exe->esp, lx_exe->esp );
	printf( "%40.40s - %lu (0x%lx)\n", "PgSize", lx_exe->page_size, lx_exe->page_size );
	printf( "%40.40s - %lu (0x%lx)\n", "PgOfsShift", lx_exe->page_offset_shift, lx_exe->page_offset_shift );
	printf( "%40.40s - %lu (0x%lx)\n", "FixupSectionSize", lx_exe->fixup_section_size, lx_exe->fixup_section_size );
	printf( "%40.40s - %lu (0x%lx)\n", "FixupCksum", lx_exe->fixup_section_checksum, lx_exe->fixup_section_checksum);
	printf( "%40.40s - %lu (0x%lx)\n", "LdrSecSize", lx_exe->loader_section_size, lx_exe->loader_section_size );
	printf( "%40.40s - %lu (0x%lx)\n", "LdrSecCksum", lx_exe->loader_section_checksum, lx_exe->loader_section_checksum );
	printf( "%40.40s - %lu (0x%lx)\n", "ObjTblOfs", lx_exe->object_page_table_offset, lx_exe->object_table_offset );
	printf( "%40.40s - %lu (0x%lx)\n", "NumObjects", lx_exe->module_num_objects, lx_exe->module_num_objects );
	printf( "%40.40s - %lu (0x%lx)\n", "ObjPgTblOfs", lx_exe->object_page_table_offset, lx_exe->object_page_table_offset );
	printf( "%40.40s - %lu (0x%lx)\n", "ObjIterPgsOfs", lx_exe->object_iter_pages_offset, lx_exe->object_iter_pages_offset );
	printf( "%40.40s - %lu (0x%lx)\n", "RscTblOfs", lx_exe->resource_table_offset, lx_exe->resource_table_offset );
	printf( "%40.40s - %lu (0x%lx)\n", "NumRscTblEnt", lx_exe->num_resource_table_entries, lx_exe->num_resource_table_entries );
	printf( "%40.40s - %lu (0x%lx)\n", "ResNameTblOfs", lx_exe->resident_name_table_offset, lx_exe->resident_name_table_offset );
	printf( "%40.40s - %lu (0x%lx)\n", "EntryTblOfs", lx_exe->entry_table_offset, lx_exe->entry_table_offset );
	printf( "%40.40s - %lu (0x%lx)\n", "ModDirOfs", lx_exe->module_directives_offset, lx_exe->module_directives_offset );
	printf( "%40.40s - %lu (0x%lx)\n", "NumModDirs", lx_exe->num_module_directives, lx_exe->num_module_directives );
	printf( "%40.40s - %lu (0x%lx)\n", "FixupPgTblOfs", lx_exe->fixup_page_table_offset, lx_exe->fixup_page_table_offset );
	printf( "%40.40s - %lu (0x%lx)\n", "FixupRecTblOfs", lx_exe->fixup_record_table_offset, lx_exe->fixup_record_table_offset );
	printf( "%40.40s - %lu (0x%lx)\n", "ImpModTblOfs", lx_exe->import_module_table_offset, lx_exe->import_module_table_offset );
	printf( "%40.40s - %lu (0x%lx)\n", "NumImpModEnt", lx_exe->num_import_mod_entries, lx_exe->num_import_mod_entries );
	printf( "%40.40s - %lu (0x%lx)\n", "ImpProcTblOfs", lx_exe->import_proc_table_offset, lx_exe->import_proc_table_offset);
	printf( "%40.40s - %lu (0x%lx)\n", "PerPgCksumOfs", lx_exe->per_page_checksum_offset, lx_exe->per_page_checksum_offset );
	printf( "%40.40s - %lu (0x%lx)\n", "DataPgOfs", lx_exe->data_pages_offset, lx_exe->data_pages_offset );
	printf( "%40.40s - %lu (0x%lx)\n", "NumPreloadPg", lx_exe->num_preload_pages, lx_exe->num_preload_pages );
	printf( "%40.40s - %lu (0x%lx)\n", "NResNameTblOfs", lx_exe->non_resident_name_table_offset, lx_exe->non_resident_name_table_offset);
	printf( "%40.40s - %lu (0x%lx)\n", "NResNameTblLen", lx_exe->non_resident_name_table_len, lx_exe->non_resident_name_table_len);
	printf( "%40.40s - %lu (0x%lx)\n", "NResNameTblCksum", lx_exe->non_resident_name_table_checksum, lx_exe->non_resident_name_table_checksum);
	printf( "%40.40s - %lu (0x%lx)\n", "AutoDSObj", lx_exe->auto_ds_object_num, lx_exe->auto_ds_object_num );
	printf( "%40.40s - %lu (0x%lx)\n", "DebugInfoOfs", lx_exe->debug_info_offset, lx_exe-> debug_info_offset );
	printf( "%40.40s - %lu (0x%lx)\n", "DebugInfoLen", lx_exe->debug_info_len, lx_exe->debug_info_len);
	printf( "%40.40s - %lu (0x%lx)\n", "NumInstPreload", lx_exe->num_instance_preload, lx_exe->num_instance_preload );
	printf( "%40.40s - %lu (0x%lx)\n", "NumInstDemand", lx_exe->num_instance_demand, lx_exe->num_instance_demand );
	printf( "%40.40s - %lu (0x%lx)\n", "HeapSize", lx_exe->heapsize, lx_exe->heapsize );
	printf( "%40.40s - %lu (0x%lx)\n", "StackSize", lx_exe->stacksize, lx_exe->stacksize );

	if( lx_exe->module_flags & MODF_RESERVED1 )
		printf( "Module flag MODF_RESERVED1 set\n" );
	if( lx_exe->module_flags & MODF_RESERVED2 )
		printf( "Module flag MODF_RESERVED2 set\n" );
	if( lx_exe->module_flags & MODF_PERPROCLIB )
		printf( "Module flag MODF_PERPROCLIB set\n" );
	if( lx_exe->module_flags & MODF_RESERVED3 )
		printf( "Module flag MODF_RESERVED3 set\n" );
	if( lx_exe->module_flags & MODF_INTERNALFIX )
		printf( "Module flag MODF_INTERNALFIX set\n" );
	if( lx_exe->module_flags & MODF_EXTERNALFIX )
		printf( "Module flag MODF_EXTERNALFIX set\n" );
	if( lx_exe->module_flags & MODF_RESERVED4 )
		printf( "Module flag MODF_RESERVED4 set\n" );
	if( lx_exe->module_flags & MODF_RESERVED5 )
		printf( "Module flag MODF_RESERVED5 set\n" );
	if( lx_exe->module_flags & MODF_NOWINCOMPAT )
		printf( "Module flag MODF_NOWINCOMPAT set\n" );
	if( lx_exe->module_flags & MODF_WINCOMPAT )
		printf( "Module flag MODF_WINCOMPAT set\n" );
	if( lx_exe->module_flags & MODF_USESWINAPIU )
		printf( "Module flag MODF_USESWINAPIU set\n" );
	if( lx_exe->module_flags & MODF_RESERVED6 )
		printf( "Module flag MODF_RESERVED6 set\n" );
	if( lx_exe->module_flags & MODF_RESERVED7 )
		printf( "Module flag MODF_RESERVED7 set\n" );
	if( lx_exe->module_flags & MODF_RESERVED8 )
		printf( "Module flag MODF_RESERVED8 set\n" );
	if( lx_exe->module_flags & MODF_NOTLOADABLE )
		printf( "Module flag MODF_NOTLOADABLE set\n" );
	if( lx_exe->module_flags & MODF_RESERVED9 )
		printf( "Module flag MODF_RESERVED9 set\n" );
	if( lx_exe->module_flags & MODF_PERPROCLIBTERM )
		printf( "Module flag MODF_PERPROCLIBTERM is set.\n" );
	if( lx_exe->module_flags & MODF_TYPEMASK == MODF_TYPPROGRAM )
		printf( "EXE is a PROGRAM\n" );
	if( lx_exe->module_flags & MODF_TYPEMASK == MODF_TYPLIBRARY )
		printf( "EXE is a LIBRARY\n" );
	if( lx_exe->module_flags & MODF_TYPEMASK == MODF_TYPPROTMEMLIB )
		printf( "EXE is a PROTMEMLIB\n" );
	if( lx_exe->module_flags & MODF_TYPEMASK == MODF_TYPPHYSDEV )
		printf( "EXE is a PHYSDEV\n" );
	if( lx_exe->module_flags & MODF_TYPEMASK == MODF_TYPVIRTDEV )
		printf( "EXE is a VIRTDEV\n" );
}
