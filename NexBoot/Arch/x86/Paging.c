/*
    Paging.c - contains 32 bit paging code
    Distributed with NexOS, licensed under the AGPL v3.0
    See LICENSE
*/

#include <Nexboot.h>

extern VOID SwitchDir();
extern VOID EnablePaging();

ADDRSPACE* dir = 0;
DWORD pdbr = 0;

VOID SetFrame(DWORD* entry, DWORD addr)
{
    *entry = (*entry & ~PG_FRAME) | addr;
}

INT NbMemMapAddr(VIRTUALADDR virt, VIRTUALADDR phys, DWORD flags)
{
    ADDRSPACE* dir_virt = (ADDRSPACE*)0xFFFFF000;
    PDE* e = &dir_virt->entries[PAGE_DIRECTORY_INDEX(virt)];
    PAGETABLE* table = 0;
    if((*e & PG_PRESENT) != PG_PRESENT)
    {
        PAGETABLE* table_phys = (PAGETABLE*)NbAllocBlock();
        if(!table_phys)
            return 0;
        *e |= flags;
        SetFrame(e, (DWORD)table_phys);
    }
    table = (PAGETABLE*)(0xFFC00000 + (PAGE_DIRECTORY_INDEX(virt) * 4096));
    PTE* page = &table->entries[PAGE_TABLE_INDEX(virt)];
    *page |= flags;
    SetFrame(page, phys);
    return 1;
}

INT NbPagingInit()
{
    dir = (ADDRSPACE*)NbAllocBlock();
    if(!dir)
        return 0;
    PDE* e = &dir->entries[1023];
    *e = PG_PRESENT | PG_WRITEABLE;
    SetFrame(e, (DWORD)dir);
    e = &dir->entries[PAGE_DIRECTORY_INDEX(0x00000000)];
    *e = PG_PRESENT | PG_WRITEABLE | PG_LARGE;
    SetFrame(e, 0x0);
    e = &dir->entries[PAGE_DIRECTORY_INDEX(0x00400000)];
    *e = PG_PRESENT | PG_WRITEABLE | PG_LARGE;
    SetFrame(e, 0x400000);
    e = &dir->entries[PAGE_DIRECTORY_INDEX(0x00800000)];
    *e = PG_PRESENT | PG_WRITEABLE | PG_LARGE;
    SetFrame(e, 0x800000);
    e = &dir->entries[PAGE_DIRECTORY_INDEX(0x00C00000)];
    *e = PG_PRESENT | PG_WRITEABLE | PG_LARGE;
    SetFrame(e, 0xC00000);
    pdbr = (DWORD)&dir->entries;
    SwitchDir();
    EnablePaging();
    return 1;
}
