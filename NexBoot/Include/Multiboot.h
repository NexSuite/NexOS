/*
    Multiboot.h - contains multiboot headers
    Distributed with NexOS, licensed under the AGPL v3.0
    See LICENSE
*/

#ifndef _MULTIBOOT_H
#define _MULTIBOOT_H

#include <nexdef.h>

#define MULTIBOOT_BOOTLOADER_MAGIC              0x2BADB002

typedef struct tagMULTIBOOT_INFO
{
	DWORD flags;
	DWORD memLower;
	DWORD memUpper;
	DWORD bootDevice;
	DWORD cmdline;
	DWORD moduleCount;
	DWORD moduleAddress;
	DWORD num;
	DWORD size;
	DWORD addr;
	DWORD shndx;
	DWORD memMapLength;
	DWORD memMapAddress;
	DWORD drivesLength;
	DWORD drivesAddr;
	DWORD configTable;
	DWORD bootloaderName;
	DWORD apmTable;

	DWORD vbeControlInfo;
	DWORD vbeModeInfo;
	WORD vbeMode;
	WORD vbeInterfaceSeg;
	WORD vbeInterfaceOff;
	WORD vbeInterfaceLen;

	QWORD framebufferAddr;
	DWORD framebufferPitch;
	DWORD framebufferWidth;
	DWORD framebufferHeight;
	BYTE framebufferBpp;
	BYTE framebufferType;
}__attribute__ ((packed)) MULTIBOOT_INFO;

typedef struct tagMULTIBOOT_MODULE
{
    DWORD modStart;
    DWORD modEnd;
    PSTR string;
    DWORD reserved;
}MULTIBOOT_MODULE;

typedef struct tagMEMINFO
{
	QWORD memCount;
	DWORD memMapAddr;
	DWORD memMapLength;
}MEMINFO;

typedef struct tagMODULEINFO
{
	DWORD moduleCount;
	DWORD moduleAddress;
}MODULEINFO;

typedef struct tagVIDINFO
{
	QWORD framebufferAddr;
	DWORD framebufferPitch;
	DWORD framebufferWidth;
	DWORD framebufferHeight;
	BYTE framebufferBpp;
	BYTE framebufferType;
}VIDINFO;

typedef struct tagNEXBOOTINFO
{
	CHAR sig[6];
	DWORD cmdLine;
	DWORD bootDevice;
	MEMINFO memInfo;
	MODULEINFO modInfo;
	VIDINFO vidInfo;
}NEXBOOTINFO;

#endif
