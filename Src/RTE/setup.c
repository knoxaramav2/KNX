#include <stdlib.h>
#include <dlfcn.h>

#include <stdio.h>

#include "node_reg.h"
#include "../ModuleManager/headers/modmanage.h"

#include "dat_tables.h"
#include "config.h"
#include "node.h"
#include "globals.h"

#include "startup.h"

Config * _config = 0;

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
    _config = loadDefaultConfig();

    return 0;
}

int startRoot()
{
    node * root = createNode();
    registerNode(root, NULL);

    pthread_create(&root->_handle, NULL, _nodeProc, root);
    printf("%d\r\n", pthread_join(root->_handle, NULL));

    return 0;
}

int shutdown()
{

    

    return 0;
}