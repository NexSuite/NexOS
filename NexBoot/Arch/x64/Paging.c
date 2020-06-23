/*
    Paging.c - contains 64 bit paging code
    Distributed with NexOS, licensed under the AGPL v3.0
    See LICENSE
*/

#include <Nexboot.h>

ADDRSPACE* pml4 = 0;
QWORD pdbr;

#define PML4_INDEX 0xFFFFFFFF7FE01000
#define PDPT_INDEX 0xFFFFFFFF7FE02000
#define PDIR_INDEX 0xFFFFFFFF7FE03000
#define PTAB_INDEX 0xFFFFFFFF7FE05000
#define TEMP_MAP_TABLE 0xFFFFFFFF7FE00000

extern VOID SwitchDir();

VOID SetFrame(QWORD* entry, QWORD addr)
{
    *entry = (*entry & ~PG_FRAME) | addr;
}

QWORD GetFrame(QWORD entry)
{
    return entry & PG_FRAME;
}

VOID NbTempMapTable(QWORD* entry, QWORD phys)
{
    *entry = 0;
    *entry = PG_PRESENT | PG_WRITEABLE;
    SetFrame(entry, phys);
}

INT NbMemMapAddr(VIRTUALADDR virt, VIRTUALADDR phys, DWORD flags)
{
    PAGETABLE* map_table = (PAGETABLE*)TEMP_MAP_TABLE;
    QWORD* entry = &map_table->entries[PAGE_TABLE_GET_INDEX(PML4_INDEX)];
    NbTempMapTable(entry, (QWORD)pml4);

    ADDRSPACE* pml4_virt = (ADDRSPACE*)PML4_INDEX;
    entry = &pml4_virt->entries[PML4_GET_INDEX(virt)];
    PDPT* pdpt_phys = 0;
    if((*entry & PG_PRESENT) != PG_PRESENT)
    {
        pdpt_phys = (PDPT*)NbAllocBlock();
        if(!pdpt_phys)
            return 0;
        *entry |= flags;
        SetFrame(entry, (QWORD)pdpt_phys);
    }
    else
    {
        pdpt_phys = GetFrame(*entry);
    }

    entry = &map_table->entries[PAGE_TABLE_GET_INDEX(PDPT_INDEX)];
    PDPT* pdpt = (PDPT*)PDPT_INDEX;
    NbTempMapTable(entry, (QWORD)pdpt_phys);

    entry = &pdpt->entries[PDPT_GET_INDEX(virt)];
    PAGEDIRECTORY* dir_phys = 0;
    if((*entry & PG_PRESENT) != PG_PRESENT)
    {
        dir_phys = (PAGEDIRECTORY*)NbAllocBlock();
        if(!dir_phys)
            return 0;
        *entry |= flags;
        SetFrame(entry, (QWORD)dir_phys);
    }
    else
    {
        dir_phys = GetFrame(*entry);
    }

    entry = &map_table->entries[PAGE_TABLE_GET_INDEX(PDIR_INDEX)];
    PAGEDIRECTORY* dir = (PAGEDIRECTORY*)PDIR_INDEX;
    NbTempMapTable(entry, (QWORD)dir_phys);

    entry = &dir->entries[PAGE_DIR_GET_INDEX(virt)];
    PAGETABLE* table_phys = 0;
    if((*entry & PG_PRESENT) != PG_PRESENT)
    {
        table_phys = (PAGETABLE*)NbAllocBlock();
        if(!table_phys)
            return 0;
        *entry |= flags;
        SetFrame(entry, (QWORD)table_phys);
    }
    else
    {
        table_phys = GetFrame(*entry);
    }
    entry = &map_table->entries[PAGE_TABLE_GET_INDEX(PTAB_INDEX)];
    PAGETABLE* table = (PAGETABLE*)PTAB_INDEX;
    NbTempMapTable(entry, (QWORD)table_phys);

    QWORD* entry2 = &table->entries[PAGE_TABLE_GET_INDEX(virt)];
    *entry2 |= flags;
    SetFrame(entry2, phys);
    return 1;
}

INT NbPagingInit()
{
    pml4 = (ADDRSPACE*)NbAllocBlock();
    if(!pml4)
        return 0;
    NbZeroMemory(pml4, sizeof(PDPT));
    QWORD* pml4e = &pml4->entries[PML4_GET_INDEX(0x0000000000000000)];
    *pml4e = PML4_PRESENT | PML4_WRITEABLE;

    PDPT* pdpt = (PDPT*)NbAllocBlock();
    if(!pdpt)
        return 0;
    NbZeroMemory(pdpt, sizeof(PDPT));
    SetFrame(pml4e, (QWORD)pdpt);

    QWORD* pdpte = &pdpt->entries[PDPT_GET_INDEX(0x0000000000000000)];
    *pdpte = PDPT_PRESENT | PDPT_WRITEABLE | PDPT_1G;
    SetFrame(pdpte, 0x0);

    pdpt = (PDPT*)NbAllocBlock();
    pml4e = &pml4->entries[PML4_GET_INDEX(0xFFFFFFFF7FE00000)];
    *pml4e = PG_PRESENT | PG_WRITEABLE;
    SetFrame(pml4e, (QWORD)pdpt);

    PAGEDIRECTORY* dir = (PAGEDIRECTORY*)NbAllocBlock();
    pdpte = &pdpt->entries[PDPT_GET_INDEX(0xFFFFFFFF7FE00000)];
    *pdpte = PG_PRESENT | PG_WRITEABLE;
    SetFrame(pdpte, (QWORD)dir);

    PAGETABLE* table = (PAGETABLE*)NbAllocBlock();
    pdpte = &dir->entries[PAGE_DIR_GET_INDEX(0xFFFFFFFF7FE00000)];
    *pdpte = PG_PRESENT | PG_WRITEABLE;
    SetFrame(pdpte, (QWORD)table);

    QWORD* pte = &table->entries[PAGE_TABLE_GET_INDEX(0xFFFFFFFF7FE00000)];
    *pte = PG_PRESENT | PG_WRITEABLE;
    SetFrame(pte, table);

    pdbr = (QWORD)&pml4->entries;
    SwitchDir();
    return 1;
}

