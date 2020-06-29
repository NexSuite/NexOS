/*
    Loader.c - contains PE kernel loader
    Distributed with NexOS, licensed under the AGPL v3.0
    See LICENSE
*/

#include <Nexboot.h>
#include <Multiboot.h>

INT NbKernelExec(MULTIBOOT_INFO* bootinfo)
{
    MULTIBOOT_MODULE* modules = (MULTIBOOT_MODULE*)bootinfo->moduleAddress;
    DWORD kernelPhysBase = modules[0].modStart;
    DWORD kernelSize = modules[0].modEnd - modules[0].modStart;

    for(int i = 0; i < kernelSize; i += 4096)
    {
        INT res = NbMemMapAddr(KERNEL_VIRTUAL_BASE + i, kernelPhysBase + i, PG_PRESENT | PG_WRITEABLE);
        if(!res)
        {
            NbDebug("Out of memory!\r\n");
            asm("int $0x19");
        }
    }

    IMAGE_DOS_HEADER* dosHeader = (IMAGE_DOS_HEADER*)KERNEL_VIRTUAL_BASE;
    
    if(dosHeader->e_magic != 0x5A4D)
    {
        NbDebug("Kernel is corrupted!\r\n");
        asm("int $0x19");
    }

    IMAGE_PE_HEADERS* peHeader = (IMAGE_PE_HEADERS*)(dosHeader->e_lfanew + KERNEL_VIRTUAL_BASE);
    if(peHeader->magic != 0x00004550)
    {
        NbDebug("Kernel is corrupted!\r\n");
        asm("int $0x19");
    }
    if(peHeader->optHeader.Magic != ARCH_PE_MAGIC)
    {
        NbDebug("You are using the wrong kernel\r\n");
        asm("int $0x19");
    }

    DWORD entry = peHeader->optHeader.AddressOfEntryPoint;
    PE_VA entryPoint = entry + KERNEL_VIRTUAL_BASE;
    VOID (*Kernel)(NEXBOOTINFO*) = (VOID(*)(NEXBOOTINFO*))(entryPoint);

    NEXBOOTINFO nexinfo;
    nexinfo.sig[0] = 'N';
    nexinfo.sig[1] = 'e';
    nexinfo.sig[2] = 'x';
    nexinfo.sig[3] = 'O';
    nexinfo.sig[4] = 'S';
    nexinfo.sig[5] = '\0';
    nexinfo.bootDevice = bootinfo->bootDevice;
    nexinfo.cmdLine = bootinfo->cmdline;
    nexinfo.memInfo.memCount = bootinfo->memLower + bootinfo->memUpper + 1024;
    nexinfo.memInfo.memMapAddr = bootinfo->memMapAddress;
    nexinfo.memInfo.memMapLength = bootinfo->memMapLength;
    nexinfo.modInfo.moduleAddress = bootinfo->moduleAddress;
    nexinfo.modInfo.moduleCount = bootinfo->moduleCount;
    nexinfo.vidInfo.framebufferAddr = bootinfo->framebufferAddr;
    nexinfo.vidInfo.framebufferBpp = bootinfo->framebufferBpp;
    nexinfo.vidInfo.framebufferHeight = bootinfo->framebufferHeight;
    nexinfo.vidInfo.framebufferPitch = bootinfo->framebufferPitch;
    nexinfo.vidInfo.framebufferWidth = bootinfo->framebufferWidth;
    nexinfo.vidInfo.framebufferType = bootinfo->framebufferType;

    Kernel(&nexinfo);

    return 1;
}
