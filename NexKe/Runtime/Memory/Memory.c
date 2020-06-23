/*
    Memory.c - contains memory manipulation functions
    Distributed with NexOS, licensed under the AGPL v3.0
    See LICENSE
*/

#include <Kernel/Runtime.h>

VOID* RtlCopyMemory(VOID* dest, VOID* src, DWORD count)
{
	const char* sp = (const char*)src;
	char* dp = (char*)dest;
	for (; count != 0; count--) *dp++ = *sp++;
	return dest;
}

VOID RtlZeroMemory(VOID* block, DWORD count)
{
    unsigned char* temp = (unsigned char*)block;
	for (; count != 0; count--, temp[count] = 0);
}
