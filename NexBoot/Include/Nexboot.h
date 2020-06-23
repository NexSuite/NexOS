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
void NbInitAllocator(MULTIBOOT_INFO* bootinfo);
void NbFreeBlocks(void* p, int num);
void* NbAllocBlocks(int num);
void* NbAllocBlock();
void NbFreeBlock(void* p);
INT NbPagingInit();
VOID NbZeroMemory(VOID* block, DWORD count);
VOID NbLongToStr(ULONGLONG i, PSTR str, INT base);

#if defined(ARCH_X86)
#define PG_PRESENT 1
#define PG_WRITEABLE 2
#define PG_USER 4
#define PG_LARGE 0x80
#define PG_NXE PG_PRESENT
#define PG_FRAME 0x7FFFF000

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
#else
#error "No architecture specified!"
#endif

INT NbMemMapAddr(VIRTUALADDR virt, VIRTUALADDR phys, DWORD flags);

#endif
