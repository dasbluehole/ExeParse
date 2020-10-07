//
#ifndef __DOS_EXE_H__
#define __DOS_EXE_H__

#include <stdint.h>

//signatures
#define MZ 0x5a4d
#define NE 0x454e
#define LX 0x584c
#define PE 0x4550

#pragma pack(push,1)
typedef struct generic_exe_header
{
    uint16_t signature;//char id[2]; 'MZ'
    uint16_t bytes_in_last_block;
    uint16_t blocks_in_file;
    uint16_t num_relocs;
    uint16_t header_paragraphs;
    uint16_t min_extra_paragraphs;
    uint16_t max_extra_paragraphs;
    uint16_t ss;
    uint16_t sp;
    uint16_t checksum;
    uint16_t ip;
    uint16_t cs;
    uint16_t reloc_table_offset;
    uint16_t overlay_number;
}generic_header;
#pragma pack(pop)
#pragma pack(push,1)
typedef struct ext_header
{
    uint16_t reserved[4];
    uint16_t oemid;		// OEM id
    uint16_t oeminfo;		// OEM info
    uint16_t reserved2[10];	// reserved
    uint32_t e_lfanew;	// address of new EXE header
}ext_header;
// the dos header bello is just concatenation of generic heder
// and exttra header for newer executable. "NOT NE"
typedef struct dos_header
{
	uint16_t signature;//char id[2]; 'MZ'
    uint16_t bytes_in_last_block;
    uint16_t blocks_in_file;
    uint16_t num_relocs;
    uint16_t header_paragraphs;
    uint16_t min_extra_paragraphs;
    uint16_t max_extra_paragraphs;
    uint16_t ss;
    uint16_t sp;
    uint16_t checksum;
    uint16_t ip;
    uint16_t cs;
    uint16_t reloc_table_offset;
    uint16_t overlay_number;
    uint16_t reserved[4];
    uint16_t oemid;		// OEM id
    uint16_t oeminfo;		// OEM info
    uint16_t reserved2[10];	// reserved
    uint32_t e_lfanew;	// address of new EXE header
} dos_header;
#pragma pack(pop)
#pragma pack(push,1)
typedef struct NE_sig
{
    uint8_t unk[4];
    uint16_t behaviour;
    uint8_t unk1[26];
    uint32_t p_ne; // 0 if plain executable else offset
}ne_sig;
#pragma pack(pop)
#pragma pack(push,1)
typedef struct tlink_sig
{
    uint8_t unk[2];
    uint8_t BID;
    uint8_t ver; // tlink version major in high nibble
    uint8_t unk1[2];
}borland_sig;
#pragma pack(pop)
#pragma pack(push,1)
typedef struct old_arj
{
    uint8_t arj_sig[4]; //RJSX
}arj_sig;
#pragma pack(pop)
#pragma pack(push,1)
typedef struct lz_sig
{
    uint8_t id[2]; // LZ
    uint8_t ver[2];// 09->0.90, 91->0.91
}lz_sig;
#pragma pack(pop)
#pragma pack(push,1)
typedef struct pklite_sig
{
    uint8_t ver_minor;
    uint8_t bit_map; // 0-3 major version bit 4 extra compression 5 multisegment file
    uint8_t id[6];   // PKLITE
}pklite_sig;
#pragma pack(pop)
#pragma pack(push,1)
typedef struct lharc_sig
{
    uint8_t unk[4];
    uint8_t jmp[3]; // jump to execution code for extracting
    uint8_t unk1[2];
    uint8_t id[12];
}lharcv1_sig;
#pragma pack(pop)
#pragma pack(push,1)
typedef struct lharcv2_sig
{
    uint8_t unk[8];
    uint8_t id[10];
}lharcv2_sig;
#pragma pack(pop)
#pragma pack(push,1)
typedef struct lh_sfx
{
    uint8_t unk[8];
    uint8_t id[8];
}lhsfx;
#pragma pack(pop)
#pragma pack(push,1)
typedef struct TSC30
{
    uint32_t	id1; //018A0001h
    uint16_t  id2; //1565h
}TSC30_sig;
#pragma pack(pop)
#pragma pack(push,1)
typedef struct pkarc
{
    uint32_t   id1; //00020001h
    uint16_t id2;//=0700h
}pkarc_sig;
#pragma pack(pop)
#pragma pack(push,1)
typedef struct bsa
{
    uint16_t ID1; //000Fh
    uint8_t  ID2; //A7h
}bsa_sig;
#pragma pack(pop)
#pragma pack(push,1)
typedef struct larc
{
    uint8_t unk[4];
    uint8_t id[11]; // "SFX by LARC "
}larc_sig;
#pragma pack(pop)

void error_msg(char* msg, char *source_file,const char *funcnam,int line_num);
generic_header *read_exe_header(FILE* efile);
ext_header *read_ext_header(FILE *efile);
void display_hdr_info(generic_header *e);
void display_ext_hdr_info( ext_header *eh);
int is_borland(ext_header *eh);
char get_borland_version(ext_header *eh);
int is_modern_exe_old(ext_header *eh);
unsigned int file_size_old(char *fname);
unsigned int file_size(FILE *efile);
void rpt_print(char *field, long val);
unsigned short read_signature_old(FILE *efile, ext_header *exh);
void display_dos_hdr_info(unsigned char *buffer);
int is_modern_exe(unsigned char *buffer);
int is_valid_exe(unsigned char * buffer);
unsigned short read_signature(unsigned char *buffer);
#endif
