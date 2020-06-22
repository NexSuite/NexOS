/*
    nexdef.h - contains standard defintions for types
    Distributed with NexOS, licensed under the AGPL v3.0
    See LICENSE
*/

#ifndef _NEXDEF_H
#define _NEXDEF_H

// Integer types

typedef char CHAR;
typedef short SHORT;
typedef int INT;
typedef long LONG;
typedef long long LONGLONG;
typedef unsigned char UCHAR;
typedef unsigned short USHORT;
typedef unsigned int UINT;
typedef unsigned long ULONG;
typedef unsigned long long ULONGLONG;

// Fixed width types

typedef UCHAR BYTE;
typedef USHORT WORD;
typedef UINT DWORD;
typedef ULONGLONG QWORD;

typedef CHAR* PSTR;

// Other defines
#define CONST const
#define EXPORT _declspec(dllexport)
#define IMPORT _declspec(dllimport)

typedef void VOID;

#endif
