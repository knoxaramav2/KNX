#include <stdio.h>

#ifdef __LINUX
#include <stdlib.h>
#else
#include <wchar.h>
#include <windows.h>
#endif

#include "dat_tables.h"

DatTable datTable;

void initDatTable()
{
    #ifdef __LINUX
    readlink("/proc/self/exe", &datTable.exeLocation, 256);
    #else
    HMODULE hmod = GetModuleHandleW(NULL);
    WCHAR wpath[256];
    GetModuleFileName(NULL, datTable.exeLocation, 256);
    printf("|| %s\r\n", datTable.exeLocation);
    //wctomb(datTable.exeLocation, *wpath);
    #endif
     
}

DatTable getDatTable()
{
    return datTable;
}