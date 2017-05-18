#include "components.h"
#include "handles.h"

#include <string.h>
#include <stdlib.h>
#include <dlfcn.h>
#include <stdio.h>

comp_reg _comp_reg;

void initCompReg()
{
    _comp_reg.handles = malloc(0);
    _comp_reg.count = 0;
}

void loadComponent(char * libpath)
{
    void * handle;
    handle = dlopen(libpath, RTLD_LAZY);

    _comp_reg.handles = realloc(_comp_reg.handles, (_comp_reg.count+1) * sizeof(comp_handle));
    _comp_reg.handles[_comp_reg.count]._handle = handle;
    _comp_reg.handles[_comp_reg.count].name = malloc(strlen(libpath)+1);
    strncpy(
        _comp_reg.handles[_comp_reg.count].name,
        libpath,
        strlen(libpath)+1
    );
    
    ++_comp_reg.count;

    printf(">> %s\r\n", libpath);
}