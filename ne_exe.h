// NE_EXE.h - The format of the NE Executable type is described here.
//
//	History:
//		JVRodley	6/1/1990	Initial coding
//
//
#ifndef __NE_EXE_H__
#define __NE_EXE_H__

#include <stdint.h>
#include "dos_exe.h"
#define CHAIN_END 0xFFFF

typedef struct SEG_DESC 
{
   uint16_t number;  // the segment number, 1-based
   uint32_t file_start;  // The File location.
   uint32_t file_end;    //
   unsigned size;
   unsigned num_relocs;
}SEG_DESC;


typedef struct relseg_tag 
{
   uint32_t lFileStart;
   uint32_t lFileEnd;
   unsigned uSize;
   unsigned uNumRecs;
}  RELOCATION_SEGMENT;

extern RELOCATION_SEGMENT *RelSegmentList[];

// an entry in a NE Fixup Record Table
struct NEW_REL 
{
   uint8_t target;   // The type of target (see targets below)
   uint8_t source; // The type of source (see sources below)
   unsigned offset;  // Offset in this segment of target.
   unsigned module_num;  // Module number (see Module Reference entry) 
                        // if source = 1 or 2, segment number if source = 0
   unsigned ordinal;    // target offset if source = 0, function ordinal
                        // if source = 1 and function name offset in 
                        // Imported Name Table if source = 2
};

// Possible values for target
#define NE_TARG_16SEG   2     // 16-bit segment
#define NE_TARG_16SEGOFS   3  // 16-bit segment, 16-bit offset
#define NE_TARG_16OFS   5  // 16-bit offset
#define NE_TARG_16SEG32OFS   11  // 16-bit segment, 32-bit offset
#define NE_TARG_32OFS   13 // 32-bit offset

// Possible values for source
#define NE_DEST_THISEXE 0     // Source is in this executable.
#define NE_DEST_DLLBYORDINAL 1   // Source is imported by ordinal.
#define NE_DEST_DLLBYNAME  2     // Source is imported by name.

// structure of NE header.  Follows magic bytes "NE" in file.
typedef struct {
   uint16_t sig;     // signature "NE"
   uint8_t ver;   // Version.
   uint8_t rev;   // Revision
   uint16_t enttab;  // File offset of Entry Table from lfanew.
   uint16_t cbenttab;  // Entry Table byte count.
   uint32_t crc;               // CRC checksum of entire file.
   uint16_t flags;   // Exe flags (such as ERROR ...)
   uint16_t autodata;   // Segment number of Auto-DS segment, 1-based.
   uint16_t heap; // Segment number of heap, 1-based.
   uint16_t stack;   // Segment number of stack, 1-based.
   uint16_t ip;   // Initial value of IP register.
   uint16_t cs;   // Initial value of CS register.
   uint16_t sp;   // Initial value of SP register.
   uint16_t ss;   // Initial value of SS register.
   uint16_t nseg; // Number of segments in Segment Table.
   uint16_t nmod; // Number of modules in Module Reference Table.
   uint16_t cbnrestab;  // Byte count of Non-Resident Name Table.
   uint16_t segtab;  // File offset of Segment Table from lfanew.
   uint16_t rsrctab; // File offset of Resource Table from lfanew.
   uint16_t restab;  // File offset of Resident Name Table from lfanew.
   uint16_t modtab;  // File offset of Module Reference Table from lfanew.
   uint16_t imptab;  // File offset of Imported Name Table from lfanew.
   uint32_t nrestab;  // File offset of Non-Resident Name Table from beginning of file.
   uint16_t nmovent; // Number of movable entries.
   uint16_t align;   // File sector size, Segments are aligned on boundaries of this value.
   uint16_t res_count; // Item count of Resource Table.
   //char resv[10]; // reserved.
   uint8_t  exetyp;	  /* 36 Target operating system */
   uint8_t  addflags;	  /* 37 Additional flags */
   uint16_t reserced[3];      /* 38 3 reserved words */
   uint8_t  sdkrev;	  /*(windows only) 3E Windows SDK revison number */
   uint8_t  sdkver;	  /*(windows only) 3F Windows SDK version number */
} NE_EXE, ne_hdr;

extern NE_EXE newexe;
/*
   *  Format of NE_FLAGS(x):
   *
   *  p 				  Not-a-process
   *   x				  Unused
   *	e				  Errors in image
   *	 x				  Unused
   *	  b				  Bound as family app
   *	   ttt				  Application type
   *	      f 			  Floating-point instructions
   *	       3			  386 instructions
   *		2			  286 instructions
   *		 0			  8086 instructions
   *		  P			  Protected mode only
   *		   p			  Per-process library initialization
   *		    i			  Instance data
   *		     s			  Solo data
   */
   /* flags */
#define NENOTP	  0x8000	  /* Not a process */
#define NEIERR	  0x2000	  /* Errors in image */
#define NEBOUND	  0x0800	  /* Bound as family app */
#define NEAPPTYP	  0x0700	  /* Application type mask */
#define NENOTWINCOMPAT  0x0100	  /* Not compatible with P.M. Windowing */
#define NEWINCOMPAT	  0x0200	  /* Compatible with P.M. Windowing */
#define NEWINAPI	  0x0300	  /* Uses P.M. Windowing API */
#define NEFLTP	  0x0080	  /* Floating-point instructions */
#define NEI386	  0x0040	  /* 386 instructions */
#define NEI286	  0x0020	  /* 286 instructions */
#define NEI086	  0x0010	  /* 8086 instructions */
#define NEPROT	  0x0008	  /* Runs in protected mode only */
#define NEPPLI	  0x0004	  /* Per-Process Library Initialization */
#define NEINST	  0x0002	  /* Instance data */
#define NESOLO	  0x0001	  /* Solo data */

   /* resv */
   #define NEUNK 0x00
   #define NE_OS2 0x01
   #define NEWIND 0x02
   #define DOS_4  0x03
   #define WIN_386 0x04
   

// an entry in the NE Segment Table
struct SEG 
{
   uint16_t ns_sector;  // The file sector segment starts at.
   uint16_t ns_cbseg;   // The number of bytes in segment image.
   uint16_t ns_flags;   // Type of segment (code,data ...)
   uint16_t ns_minalloc;   // Minimum size in memory.
};

#define RELOCATION_AVAIL 0x0100



#define NSTYPE 0x0007
#define NSCODE 0
#define NSDATA 1
#define NSITER 0x0008
#define NSMOVE 0x0010
#define NSPURE 0x0020
#define NSPRELOAD 0x0040
#define NSEXRD 0x0080
#define NSRELOC 0x0100
#define NSCONFORM 0x0200
#define NSDPL 0x0c00
#define SHIFTDPL 10
#define NSDISCARD 0x1000
#define NS32BIT 0x2000
#define NSHUGE 0x4000

struct IMP_NAME {
   unsigned index;
   uint16_t offset;
   char name[255];
   };

// an entry in NE Module Reference Table.
struct MOD_REF {
   unsigned index;   // An index into the Imported Name Table.
   unsigned uModNum; // The module number used by Fixup Records trying to use this Module Reference.
   };

struct RES_NAME {
   unsigned ordinal;
   char name[255];
   };

struct NONRES_NAME { 
   unsigned ordinal;
   char name[255];
   };

struct ENTRY_BUNDLE {
   uint8_t num;
   uint8_t type;
   char placeholder;
   };
// bundle types
#define EB_MOVEABLE_SEGMENT   0xFF
#define EB_NULL_BUNDLE   0x00

struct ENTRY_FIXED {
   uint8_t flags;
   uint16_t offset;
   };
      
struct ENTRY_MOVEABLE {
   uint8_t flags;
   char signature[2];   // == 0xCD, 0x3F
   uint8_t seg;
   uint16_t offset;
   };
      
struct ENTRY {
      unsigned seg;
      unsigned offset;
      unsigned flags;
      unsigned ordinal;
       };

struct RESOURCE {
int dummy;
};

#define MAX_SEGMENTS 300
#define MAX_MODREFS 300
#define MAX_IMPNAMES 300
#define MAX_RESNAMES 300
#define MAX_NONRESNAMES 600
#define MAX_ENTRIES 600
#define MAX_RELOCATIONS 300
#define MAX_RESOURCES 300

// functions 
ne_hdr *read_ne_hdr_old(FILE *efile, ext_header *exh);
void dump_ne_header_old(ne_hdr *neh);
ne_hdr *read_ne_hdr(unsigned char *buffer);
void dump_ne_header(unsigned char *buffer);
#endif
