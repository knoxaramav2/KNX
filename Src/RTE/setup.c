#include "startup.h"
#include "handles.h"

#include <stdlib.h>
#include <dlfcn.h>

comp_reg _comp_reg;

int initComponents()
{
    initCompReg();

    loadComponent("libMDM.so");
    loadComponent("libDTM.so");
    loadComponent("libPRS.so");
    loadComponent("libEXC.so");

    return 0;
}

int parseCmd()
{

    return 0;
}

int startRoot()
{

    return 0;
}

int shutdown()
{

    for(int i = 0; i < _comp_reg.count; ++i){
        dlclose(_comp_reg.handles[i]._handle);
    }

    return 0;
}