/*
    Memory.c - contains NexBoot's physical memory manager
    Distributed with NexOS, licensed under the AGPL v3.0
    See LICENSE
    NOTE: It was taken from NexNix, don't mind the inconsistent styling. I will fix that with time
*/

#include <Nexboot.h>
#include <Multiboot.h>

DWORD* mem_map = 0;
DWORD num_blocks = 0;
DWORD total_mem = 0;
DWORD used_blocks = 0;

void mmap_set(int block)
{
     mem_map[block / 32] |= (1 << (block % 32));
}

void mmap_unset(int block)
{
     mem_map[block / 32] &= (1 << (block % 32));
}

int mmap_test(int block)
{
     return mem_map[block / 32] & (1 << (block % 32));
}

int mmap_first_free()
{
    for (DWORD i = 0; i < num_blocks / 32; i++)
    {
        if(mem_map[i] != 0xffffffff)
        {
            for(DWORD j = 0; j < 32; j++)
            {
                int bit = 1 << j;
                if(!(mem_map[i] & bit))
                {
                    return i * 32 + j;
                }
            }
        }
    }
    return -1;
}

int mmap_first_free_s(DWORD size)
{
    if(size == 0)
        return -1;
    if(size == 1)
        return mmap_first_free();

    for (DWORD i = 0; i < used_blocks / 32; i++)
    {
        if(mem_map[i] != 0xffffffff)
        {
            for(DWORD j = 0; j < 32; j++)
            {
                  int bit = 1 << j;
                  if(!(mem_map[i] & bit))
                  {
                      int start = i * 32;
                      start += bit;
                      DWORD free = 0;
                      for (DWORD count = 0; count <= size; count++)
                      {
                          if(!mmap_test(start + count))
                          {
                              free++;
                          }
                          if(free == size)
                          {
                              return i * 32 + j;
                          }
                      }
                  }
            }
        }
    }
    return -1;
}

void init_region(int base, int size)
{
    int align = base / 4096;
    int block = size / 4096;

    for(; block > 0; block--)
    {
        mmap_unset(align++);
        used_blocks--;
    }
    mmap_set(0);
}

void deinit_region(int base, int size)
{
    int align = base / 4096;
    int block = size / 4096;

    for(; block > 0; block--)
    {
        mmap_set(align++);
        used_blocks++;
    }
}

void* NbAllocBlock()
{
    if((num_blocks - used_blocks) == 0)
        return 0;
    int frame = mmap_first_free();
    mmap_set(frame);
    used_blocks++;
    DWORD base = frame * 4096;
    return (void*)base;
}

void NbFreeBlock(void* p)
{
    DWORD addr = (int)p;
    int frame = addr / 4096;
    mmap_unset(frame);
    used_blocks--;
}

void* NbAllocBlocks(int num)
{
    if((num_blocks - used_blocks) == 0)
        return 0;
    if(num == 0)
        return 0;
    if(num == 1)
        return NbAllocBlock();
    int frame = mmap_first_free_s(num);
    for(int i = 0; i < num; i++)
        mmap_set(frame + i);
    used_blocks += num;
    DWORD base = frame * 4096;
    return (void*)base;
}

void NbFreeBlocks(void* p, int num)
{
    DWORD base = (DWORD)p;
    int frame = base / 4096;
    for(int i = 0; i < num; i++)
        mmap_unset(frame + i);
    used_blocks -= num;
}

void NbInitAllocator(MULTIBOOT_INFO* bootinfo)
{
    total_mem = bootinfo->memLower = bootinfo->memUpper + 1024;
    num_blocks = (total_mem * 1024) / 4096;
    used_blocks = 0;
    mem_map = (DWORD*)0x00000500;
    init_region(0x00000000, 0xFFFFFFFF);
    deinit_region(0x00000000, 0x00200000);
}
