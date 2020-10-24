#ifndef _coff_h_
#define _coff_h_
#include <stdint.h>
#pragma pack(push,1)
typedef struct {
  uint16_t f_magic; 	/* magic number             */
  uint16_t f_nscns; 	/* number of sections       */
  uint32_t f_timdat; 	/* time &amp; date stamp    */
  uint32_t f_symptr; 	/* file pointer to symtab   */
  uint32_t f_nsyms;	/* number of symtab entries */
  uint16_t f_opthdr; 	/* sizeof(optional hdr)     */
  uint16_t f_flags; 	/* flags                    */
} COFF_HDR;

typedef struct {
  uint16_t magic;         /* type of file                          */
  uint16_t vstamp;        /* version stamp                         */
  uint32_t tsize;         /* text size in bytes, padded to FW bdry */
  uint32_t dsize;         /* initialized data    "  "              */
  uint32_t bsize;         /* uninitialized data  "  "              */
  uint32_t entry;         /* entry pt.                             */
  uint32_t text_start;    /* base of text used for this file       */
  uint32_t data_start;    /* base of data used for this file       */
} COFF_OPT_HDR;

typedef struct {
  char      s_name[8];     /* section name                     */
  uint32_t  s_paddr;       /* physical address, aliased s_nlib */
  uint32_t  s_vaddr;       /* virtual address                  */
  uint32_t  s_size;        /* section size                     */
  uint32_t  s_scnptr;      /* file ptr to raw data for section */
  uint32_t  s_relptr;      /* file ptr to relocation           */
  uint32_t  s_lnnoptr;     /* file ptr to line numbers         */
  uint16_t  s_nreloc;      /* number of relocation entries     */
  uint16_t  s_nlnno;       /* number of line number entries    */
  uint32_t  s_flags;       /* flags                            */
} COFF_SECTION;

typedef struct {
  uint32_t  r_vaddr;       /* address of relocation      */
  uint32_t  r_symndx;      /* symbol we're adjusting for */
  uint16_t r_type;        /* type of relocation         */
} COFF_RELOC;

typedef struct {
  union {
    char         e_name[8];     /* symbol name if length <= 8             */
    struct {
      uint32_t e_zeroes;   /* 0, if sym name's length > 8            */
      uint32_t e_offset;   /* offset of a name into the string table */
    } e;
  } e;
  uint32_t e_value;       /* the value of the symbol                */
  uint16_t e_scnum;       /* section of the symbol (1,2,...)        */
  uint16_t e_type;        /* symbol type                            */
  uint8_t e_sclass;      /* storage class                          */
  uint8_t e_numaux;      /* number of auxiliary entries            */
} COFF_SYM_ENT;
#pragma pack(pop)

// function proto
int is_DJ(unsigned char *ef);
int is_coff(char *ef);
void disp_coff_hdr(char *ef);
#endif
