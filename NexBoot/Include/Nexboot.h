/*
    Nexboot.h - contains functions for Nexboot
    Distributed with NexOS, licensed under the AGPL v3.0
    See LICENSE
    Partialy taken from the LemonOS project. Portions from LemonOS are copyright JJ Roberts-White, licensed under the BSD 2 clause license
*/

#ifndef _NEXBOOT_H
#define _NEXBOOT_H

#include <nexdef.h>
#include <Multiboot.h>

INT NbStrLen(PSTR str);
VOID NbIntToStr(UINT i, PSTR str, INT base);
VOID NbIntToStrSigned(INT i, PSTR str, INT base);
VOID* NbCopyMemory(VOID* dest, VOID* src, DWORD count);
INT NbCmpStr(PSTR str1, PSTR str2);
VOID NbSerialInit();
VOID NbSerialWriteChar(CHAR c);
VOID NbSerialWriteString(PSTR s);
VOID NbDebug(PSTR s);
BYTE NbInByte(WORD port);
VOID NbOutByte(WORD port, BYTE val);
void* NbAllocBlock();
INT NbPagingInit();
VOID NbZeroMemory(VOID* block, DWORD count);
VOID NbLongToStr(ULONGLONG i, PSTR str, INT base);
INT NbKernelExec(MULTIBOOT_INFO* bootinfo);

#if defined(ARCH_X86)
#define PG_PRESENT 1
#define PG_WRITEABLE 2
#define PG_USER 4
#define PG_LARGE 0x80
#define PG_NXE PG_PRESENT
#define PG_FRAME 0x7FFFF000
#define PAGE_CACHE_DISABLED 0x10

#define PAGE_SIZE 4194304

typedef DWORD VIRTUALADDR;

typedef struct tagADDRSPACE
{
    DWORD entries[1024];
}ADDRSPACE;

#define PAGE_DIRECTORY_INDEX(x) (((x) >> 22) & 0x3ff)
#define PAGE_TABLE_INDEX(x) (((x) >> 12) & 0x3ff)

typedef struct tagPAGETABLE
{
    DWORD entries[1024];
}PAGETABLE;
typedef DWORD PTE;
typedef PTE PDE;
typedef DWORD VIRTUALADDR;
#define ARCH_PE_MAGIC 0x010B
#define KERNEL_VIRTUAL_BASE 0xC0000000
#elif defined(ARCH_X64)
#define PML4_GET_INDEX(addr) (((addr) >> 39) & 0x1FF)
#define PDPT_GET_INDEX(addr) (((addr) >> 30) & 0x1FF)
#define PAGE_DIR_GET_INDEX(addr) (((addr) >> 21) & 0x1FF)
#define PAGE_TABLE_GET_INDEX(addr) (((addr) >> 12) & 0x1FF)

#define PML4_PRESENT 1
#define PML4_WRITEABLE (1 << 1)
#define PML4_FRAME 0xFFFFFFFFFF000

#define PDPT_PRESENT 1
#define PDPT_WRITEABLE (1 << 1)
#define PDPT_1G (1 << 7)
#define PDPT_USER (1 << 2)
#define PDPT_FRAME 0xFFFFFFFFFF000

#define PDE_PRESENT 1
#define PDE_WRITEABLE (1 << 1)
#define PDE_USER (1 << 2)
#define PDE_2M (1 << 7)
#define PDE_FRAME 0xFFFFFFFFFF000

#define PG_PRESENT 1
#define PG_WRITEABLE (1 << 1)
#define PG_USER (1 << 2)
#define PAGE_WRITETHROUGH (1 << 3)
#define PAGE_CACHE_DISABLED (1 << 4)
#define PG_FRAME 0xFFFFFFFFFF000
#define PG_NX 0x8000000000000000

typedef struct tagPAGETABLE
{
    QWORD entries[512];
}PAGETABLE;

typedef struct tagPAGEDIRECTORY
{
    QWORD entries[512];
}PAGEDIRECTORY;

typedef struct tagPDPT
{
    QWORD entries[512];
}PDPT;

typedef struct tagADDRSPACE
{
    QWORD entries[512];
}ADDRSPACE;
typedef QWORD VIRTUALADDR;
#define KERNEL_VIRTUAL_BASE 0xFFFFFFFF80000000
#define ARCH_PE_MAGIC 0x020B
#else
#error "No architecture specified!"
#endif

#ifdef ARCH_I686
typedef DWORD PE_VA;
#else
typedef QWORD PE_VA;
#endif

typedef struct tagIMAGE_DOS_HEADER
{
    USHORT e_magic;
    USHORT e_cblp;
    USHORT e_cp;
    USHORT e_crlc;
    USHORT e_cparhdr;
    USHORT e_minalloc;
    USHORT e_maxalloc;
    USHORT e_ss;
    USHORT e_sp;
    USHORT e_csum;
    USHORT e_ip;
    USHORT e_cs;
    USHORT e_lfarlc;
    USHORT e_ovno;
    USHORT e_res[4];
    USHORT e_oemid;
    USHORT e_oeminfo;
    USHORT e_res2[10];
    DWORD e_lfanew;
}IMAGE_DOS_HEADER, *PIMAGE_DOS_HEADER;

typedef struct tagIMAGE_FILE_HEADER 
{
    USHORT  Machine;
    USHORT  NumberOfSections;
    DWORD   TimeDateStamp;
    DWORD   PointerToSymbolTable;
    DWORD   NumberOfSymbols;
    USHORT  SizeOfOptionalHeader;
    USHORT  Characteristics;
}IMAGE_FILE_HEADER, *PIMAGE_FILE_HEADER;

#define IMAGE_NUMBEROF_DIRECTORY_ENTRIES 14

typedef struct tagIMAGE_DATA_DIRECTORY 
{
    DWORD VirtualAddress;
    DWORD Size;   
}IMAGE_DATA_DIRECTORY, *PIMAGE_DATA_DIRECTORY;

typedef struct tagIMAGE_OPTIONAL_HEADER 
{
    USHORT Magic;
    BYTE MajorLinkerVersion;
    BYTE MinorLinkerVersion;
    DWORD SizeOfCode;
    DWORD SizeOfInitializedData;
    DWORD SizeOfUninitializedData;
    DWORD AddressOfEntryPoint;
    DWORD BaseOfCode;
    #ifdef ARCH_X86
    DWORD BaseOfData;
    #endif
    PE_VA ImageBase;
    DWORD SectionAlignment;
    DWORD FileAlignment;
    WORD MajorOperatingSystemVersion;
    WORD MinorOperatingSystemVersion;
    WORD MajorImageVersion;
    WORD MinorImageVersion;
    WORD MajorSubsystemVersion;
    WORD MinorSubsystemVersion;
    DWORD Win32VersionValue;
    DWORD SizeOfImage;
    DWORD SizeOfHeaders;
    DWORD CheckSum;
    WORD Subsystem;
    WORD DllCharacteristics;
    PE_VA SizeOfStackReserve;
    PE_VA SizeOfStackCommit;
    PE_VA SizeOfHeapReserve;
    PE_VA SizeOfHeapCommit;
    DWORD LoaderFlags;
    DWORD NumberOfRvaAndSizes;
}IMAGE_OPTIONAL_HEADER, *PIMAGE_OPTIONAL_HEADER;

typedef struct tagIMAGE_PE_HEADERS
{
    DWORD magic;
    IMAGE_FILE_HEADER fileHeader;
    IMAGE_OPTIONAL_HEADER optHeader;
}IMAGE_PE_HEADERS, *PIMAGE_PE_HEADERS;

INT NbMemMapAddr(VIRTUALADDR virt, VIRTUALADDR phys, DWORD flags);

#endif
