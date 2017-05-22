#include "../ModuleManager/headers/modmanage.h"
#include "../KDK/headers/dat_tables.h"
#include "../KDK/headers/config.h"

#include "startup.h"

#include <stdlib.h>
#include <dlfcn.h>

int initComponents()
{
    initDatTable();

    register_module("libMDM.so");
    register_module("libDTM.so");
    register_module("libPRS.so");
    register_module("libEXC.so");

    return 0;
}

int parseCmd(int argc, char ** argv)
{
    loadDefaultConfig();

    return 0;
}

int startRoot()
{

    return 0;
}

int shutdown()
{

    

    return 0;
}