// LX file include header
#ifndef __LX_FILE_HDR__
#define __LX_FILE_HDR__
#include <stdint.h>
#ifdef __DJGPP__
// Possible values for both ByteOrder and WordOrder
#define LITTLE_ENDIAN 0x00
#define BIG_ENDIAN 0x01
#endif
//CPU types in LX header
#define CPU_286 0x01
#define CPU_386 0x02
#define CPU_486 0x03
#define CPU_PENTIUM 0x04

//OS types
#define OS_UNKNOWN	0x00
#define OS_OS2		0x01
#define OS_WIN		0x02
#define OS_DOS4		0x03
#define OS_WIN386	0x04

// Possible values for ModFlags
#define MODF_RESERVED1	0x00000001L
#define MODF_RESERVED2	0x00000002L
#define MODF_PERPROCLIB	0x00000004L
#define MODF_RESERVED3	0x00000008L
#define MODF_INTERNALFIX	0x00000010L
#define MODF_EXTERNALFIX	0x00000020L
#define MODF_RESERVED4	0x00000040L
#define MODF_RESERVED5	0x00000080L
#define MODF_NOWINCOMPAT	0x00000100L
#define MODF_WINCOMPAT	0x00000200L
#define MODF_USESWINAPIU	0x00000300L
#define MODF_RESERVED6	0x00000400L
#define MODF_RESERVED7	0x00000800L
#define MODF_RESERVED8	0x00001000L
#define MODF_NOTLOADABLE	0x00002000L
#define MODF_RESERVED9	0x00004000L
#define MODF_TYPEMASK	0x00038000L
#define MODF_TYPPROGRAM	0x00000000L
#define MODF_TYPLIBRARY	0x00080000L
#define MODF_TYPPROTMEMLIB	0x00018000L
#define MODF_TYPPHYSDEV	0x00020000L
#define MODF_TYPVIRTDEV	0x00028000L
#define MODF_PERPROCLIBTERM	0x40000000L


typedef uint8_t uint8;
typedef uint16_t uint16;
typedef uint32_t uint32;

#pragma pack(push, 1)
//LX Header
typedef struct LxHeader
{
    //uint8 magic_l;
    //uint8 magic_x;
    uint16_t sig;
    uint8_t byte_order;
    uint8_t word_order;
    uint32_t lx_version;
    uint16_t cpu_type;
    uint16_t os_type;
    uint32_t module_version;
    uint32_t module_flags;
    uint32_t module_num_pages;
    uint32_t eip_object;
    uint32_t eip;
    uint32_t esp_object;
    uint32_t esp;
    uint32_t page_size;
    uint32_t page_offset_shift;
    uint32_t fixup_section_size;
    uint32_t fixup_section_checksum;
    uint32_t loader_section_size;
    uint32_t loader_section_checksum;
    uint32_t object_table_offset;
    uint32_t module_num_objects;
    uint32_t object_page_table_offset;
    uint32_t object_iter_pages_offset;
    uint32_t resource_table_offset;
    uint32_t num_resource_table_entries;
    uint32_t resident_name_table_offset;
    uint32_t entry_table_offset;
    uint32_t module_directives_offset;
    uint32_t num_module_directives;
    uint32_t fixup_page_table_offset;
    uint32_t fixup_record_table_offset;
    uint32_t import_module_table_offset;
    uint32_t num_import_mod_entries;
    uint32_t import_proc_table_offset;
    uint32_t per_page_checksum_offset;
    uint32_t data_pages_offset;
    uint32_t num_preload_pages;
    uint32_t non_resident_name_table_offset;
    uint32_t non_resident_name_table_len;
    uint32_t non_resident_name_table_checksum;
    uint32_t auto_ds_object_num;
    uint32_t debug_info_offset;
    uint32_t debug_info_len;
    uint32_t num_instance_preload;
    uint32_t num_instance_demand;
    uint32_t heapsize;
    uint32_t stacksize;
} LxHeader, lx_hdr;

//LX object table entry
typedef struct LxObjectTableEntry
{
    uint32_t virtual_size;
    uint32_t reloc_base_addr;
    uint32_t object_flags;
    uint32_t page_table_index;
    uint32_t num_page_table_entries;
    uint32_t reserved;
} LxObjectTableEntry;

//LX page table entry
typedef struct LxObjectPageTableEntry
{
    uint32_t page_data_offset;
    uint16_t data_size;
    uint16_t flags;
} LxObjectPageTableEntry;

// LX resource table entry
typedef struct LxResourceTableEntry
{
    uint16_t type_id;
    uint16_t name_id;
    uint32_t resource_size;
    uint16_t object;
    uint32_t offset;
} LxResourceTableEntry;
//FixUp section
typedef struct {
   uint16_t object;
   uint32_t target_ofs;
   uint16_t srcofs[1];
} LX_FU_INTERNAL;

typedef struct {
   uint16_t module;
   uint32_t proc_nm_ofs;
   uint32_t additive;
   uint16_t srcofs[1];
} LX_FU_IMPBYNAME;

typedef struct {
   uint16_t module;
   uint16_t ordinal;
   uint32_t additive;
   uint16_t srcofs[1];
} LX_FU_IMPBYORD;

typedef struct {
   uint16_t ordinal;
   uint32_t additive;
   uint16_t srcofs[1];
} LX_FU_VIAENTRY;

// FIXUP structure definitions
typedef struct 
{
   uint8_t source;
   uint8_t flags;
   union 
   {
      uint8_t cnt;
      uint16_t ofs;
   } sc;

   union 
   {
      LX_FU_INTERNAL i;
      LX_FU_IMPBYORD o;
      LX_FU_IMPBYNAME   n;
      LX_FU_VIAENTRY e;
   } targ;
   uint32_t offset;
   uint16_t *list;
} LX_FIXUP;


#pragma pack(pop)
// possible bit values for obj_flags
#define OF_READABLE	0x0001
#define OF_WRITABLE	0x0002
#define OF_EXECUTABLE	0x0004
#define OF_RESOURCE	0x0008
#define OF_DISCARDABLE	0x0010
#define OF_SHARED	0x0020
#define OF_PRELOAD	0x0040
#define OF_INVALID	0x0080
#define OF_ZEROFILLED	0x0100
#define OF_RESIDENT	0x0200
#define OF_RESLONGLOCK	0x0400
#define OF_RESERVED1	0x0800
#define OF_16	0x1000
#define OF_BIGDEFAULT	0x2000
#define OF_CONFORMING	0x4000
#define OF_IOPRIV	0x8000
// bit combo
#define OF_RESCONTIGUOUS	0x0300

// function proto
int is_LX(unsigned char *efile);
lx_hdr *read_lx_header_old(FILE *efile, ext_header *exh);
void dump_lx_header_old(lx_hdr *lx_exe);
lx_hdr *read_lx_header(unsigned char *buffer);
void dump_lx_header(unsigned char *buffer);

#endif

// end of lx_loader.h ...

