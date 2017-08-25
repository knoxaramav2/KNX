#include <stdio.h>

#ifdef __LINUX
#include <stdlib.h>
#else
#include <wchar.h>
#include <windows.h>
#endif

#include "KNX_File.h"

#include "debug.h"
#include "dat_tables.h"

DatTable datTable;

void initDatTable()
{
    #ifdef __LINUX
    readlink("/proc/self/exe", &datTable.exeLocation, 256);
    #else
    GetModuleFileName(NULL, datTable.exeLocation, 256);
    #endif

    char * tmp = getPath(datTable.exeLocation);

    strncpy(datTable.exeLocation, tmp, strlen(tmp)+1);

    dprint("Exe at %s\r\n", datTable.exeLocation);
}

DatTable getDatTable()
{
    return datTable;
}