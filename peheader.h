#ifndef __PEHEADERS_H
#define __PEHEADERS_H

#include <stdint.h>

#pragma pack(push,1)
typedef struct rel_itm
{
    uint16_t offset;
    uint16_t seg;
}rel_itm;
#pragma pack(pop)
#pragma pack(push,1)
typedef struct pe_header
{
    uint16_t sig;  //sig[2]; // PE
    uint16_t zero; //00
    uint16_t machine_id;
    uint16_t num_sections; // number of sections in PE image
    uint32_t date_time_stamp;
    uint32_t symtab_pointer; // symbol table pointer
    uint32_t num_symbols; // total number of symbols
    uint16_t opt_header_size; // size of optional header
    uint16_t characteristic; // characteristic of the file
}pe_hdr;
#pragma pack(pop)
#pragma pack(push, 1)
struct data_directory
 {
    uint32_t VirtualAddress;
    uint32_t Size;
 };
typedef struct PEOptHeader
{
/*
char is 1 byte
short is 2 bytes
long is 4 bytes
*/
    uint16_t signature; //decimal number 267 for 32 bit, 523 for 64 bit, and 263 for a ROM image.
    uint8_t MajorLinkerVersion;
    uint8_t MinorLinkerVersion;
    uint32_t SizeOfCode;            //The size of the code section, in bytes, or the sum of all such sections if there are multiple code
                                //sections.
    uint32_t SizeOfInitializedData; //The size of the initialized data section, in bytes, or the sum of all such sections if there are
                                //multiple initialized data sections.
    uint32_t SizeOfUninitializedData;//The size of the uninitialized data section, in bytes, or the sum of all such sections if there are
                                 //multiple uninitialized data sections.
    uint32_t AddressOfEntryPoint;    //The RVA of the code entry point A pointer to the entry point function, relative to the image base
                                 //address. For executable files, this is the starting address. For device drivers, this is the address
                                 //of the initialization function. The entry point function is optional for DLLs. When no entry point
                                 //is present, this member is zero.
    uint32_t BaseOfCode;             //A pointer to the beginning of the code section, relative to the image base.
    uint32_t BaseOfData;             //A pointer to the beginning of the data section, relative to the image base.
    /*The next 21 fields are an extension to the COFF optional header format*/
    uint32_t ImageBase;              //The preferred address of the first byte of the image when it is loaded in memory. This value is a
                                 //multiple of 64K bytes. The default value for DLLs is 0x10000000. The default value for applications
                                 //is 0x00400000, except on Windows CE where it is 0x00010000.
    uint32_t SectionAlignment;       //The alignment of sections loaded in memory, in bytes. This value must be greater than or equal
                                 //to the FileAlignment member. The default value is the page size for the system.
    uint32_t FileAlignment;          //The alignment of the raw data of sections in the image file, in bytes. The value should
                                 //be a power of 2 between 512 and 64K (inclusive). The default is 512. If the SectionAlignment member
                                 //is less than the system page size, this member must be the same as SectionAlignment.
    uint16_t MajorOSVersion;        //    The major version number of the required operating system.
    uint16_t MinorOSVersion;        //    The minor version number of the required operating system.
    uint16_t MajorImageVersion;     //    The major version number of the image.
    uint16_t MinorImageVersion;     //    The minor version number of the image.
    uint16_t MajorSubsystemVersion; //    The major version number of the subsystem.
    uint16_t MinorSubsystemVersion; //    The minor version number of the subsystem.
    uint32_t Win32VersionValue;      //    This member is reserved and must be 0.
    uint32_t SizeOfImage;            //    The size of the image, in bytes, including all headers. Must be a multiple of SectionAlignment.
    uint32_t SizeOfHeaders;          //The combined size of the following items, rounded to a multiple of the value specified in the
                                 //FileAlignment member(    e_lfanew member of DOS_Header
                                                          //4 byte signature
                                                          //size of COFFHeader
                                                          //size of optional header
                                                          //size of all section headers

    uint32_t Checksum;               //The image file checksum. The following files are validated at load time: all drivers,
                                 //any DLL loaded at boot time, and any DLL loaded into a critical system process.
    uint16_t Subsystem;             //The Subsystem that will be invoked to run the executable
    uint16_t DLLCharacteristics;
    uint32_t SizeOfStackReserve;     //The number of bytes to reserve for the stack. Only the memory specified by
                                 //the SizeOfStackCommit member is committed at load time; the rest is made available
                                 //one page at a time until this reserve size is reached.
    uint32_t SizeOfStackCommit;      //The number of bytes to commit for the stack.
    uint32_t SizeOfHeapReserve;      //The number of bytes to reserve for the local heap. Only the memory specified by
                                 //the SizeOfHeapCommit member is committed at load time; the rest is made available one page
                                 //at a time until this reserve size is reached.
    uint32_t SizeOfHeapCommit;       //The number of bytes to commit for the local heap.
    uint32_t LoaderFlags;            //This member is obsolete.
    uint32_t NumberOfRvaAndSizes;    //The number of directory entries in the remainder of the optional header. Each entry describes
                                 //a location and size.
    //data_directory DataDirectory[16];     //Can have any number of elements, matching the number in NumberOfRvaAndSizes.
    /*                                     //However, it is always 16 in PE files.
    // hardcoded Data directory entries bellow
    uint32_t ExportTableRVA;
    uint32_t ExportDataSize;
    uint32_t ImportTableRVA;
    uint32_t ImportDataSize;
    uint32_t ResourceTableRVA;
    uint32_t ResourceDataSize;
    uint32_t ExceptionTableRVA;
    uint32_t ExceptionDataSize;
    uint32_t SecurityTableRVA;
    uint32_t SecurityDataSize;
    uint32_t FixupTableRVA;
    uint32_t FixupDataSize;
    uint32_t DebugTableRVA;
    uint32_t DebugDataSize;
    uint32_t ImageDescriptionRVA;
    uint32_t DescriptionDataSize;
    uint32_t MachineSpecificRVA;
    uint32_t MachnineDataSize;
    uint32_t TLSRVA;
    uint32_t TLSDataSize;
    uint32_t LoadConfigRVA;
    uint32_t LoadConfigDataSize;
    uint8_t  Reserved01[8];
    uint32_t IATRVA;
    uint32_t IATDataSize;
    uint8_t  Reserved02[8];
    uint8_t  Reserved03[8];
    uint8_t  Reserved04[8];*/
}PEoptheader,pe_opt_hdr;

typedef struct section_header
{ // size 40 bytes
    uint8_t mName[8];
    uint32_t mVirtualSize;
    uint32_t mVirtualAddress;
    uint32_t mSizeOfRawData;
    uint32_t mPointerToRawData;
    uint32_t mPointerToRealocations;
    uint32_t mPointerToLinenumbers;
    uint16_t mNumberOfRealocations;
    uint16_t mNumberOfLinenumbers;
    uint32_t mCharacteristics;
}section_header;
#pragma pack(pop)

struct machineid
{
    uint16_t val;
    uint8_t  name[45];
};

struct subsystem
{
    int id;
    char sname[45];
};

//machine id from PE
static struct machineid    m_id[26]={
        {0x14c,"Intel 386"},
        {0x8664 	,"x64"},
        {0x162 	,"MIPS R3000"},
        {0x168 	,"MIPS R10000"},
        {0x169 	,"MIPS little endian WCI v2"},
        {0x183 	,"old Alpha AXP"},
        {0x184 	,"Alpha AXP"},
        {0x1a2 	,"Hitachi SH3"},
        {0x1a3 	,"Hitachi SH3 DSP"},
        {0x1a6 	,"Hitachi SH4"},
        {0x1a8 	,"Hitachi SH5"},
        {0x1c0 	,"ARM little endian"},
        {0x1c2 	,"Thumb"},
        {0x1d3 	,"Matsushita AM33"},
        {0x1f0 	,"PowerPC little endian"},
        {0x1f1 	,"PowerPC with floating point support"},
        {0x200 	,"Intel IA64"},
        {0x266 	,"MIPS16"},
        {0x268 	,"Motorola 68000 series"},
        {0x284 	,"Alpha AXP 64-bit"},
        {0x366 	,"MIPS with FPU"},
        {0x466 	,"MIPS16 with FPU"},
        {0xebc 	,"EFI Byte Code"},
        {0x8664 ,"AMD AMD64"},
        {0x9041 ,"Mitsubishi M32R little endian"},
        {0xc0ee ,"clr pure MSIL"}
};
//sub system
static struct subsystem subsys[13]={
    {0,"Unknown subsystem"},
    {1,"Device drivers and native system processes"},
    {2,"Windows (GUI) subsystem"},
    {3,"Windows (CUI) subsystem"},
    {5,"OS/2 CUI subsystem"},
    {7,"POSIX CUI subsystem"},
    {9,"Windows CE system"},
    {10,"EFI application"},
    {11,"EFI driver with boot services"},
    {12,"EFI driver with run-time services"},
    {13,"EFI ROM image"},
    {14,"Xbox system"},
    {16,"Boot application"}
};

// function proto
int is_PE(unsigned char *efile);
pe_hdr *get_pe_header(unsigned char *efile);
void dump_pe_header_info(unsigned char *efile);
pe_opt_hdr *get_opt_hdr(unsigned char *efile);
void dump_opt_header_info(pe_opt_hdr *opthdr);
#endif // HEADERS_H
