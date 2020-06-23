/*
    Kernel.h - contains global kernel functions
    Distributed with NexOS, licensed under the AGPL v3.0
    See LICENSE
*/

#ifndef _KERNEL_H
#define _KERNEL_H

#include <nexdef.h>

// Boot info

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
