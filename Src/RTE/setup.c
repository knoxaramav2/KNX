#include <stdlib.h>
#include <dlfcn.h>

#include "../ModuleManager/headers/modmanage.h"
#include "dat_tables.h"
#include "config.h"
#include "node.h"

#include "startup.h"

int initComponents()
{
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
    node * root = createNode();

    

    return 0;
}

int shutdown()
{

    

    return 0;
}