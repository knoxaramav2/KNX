#ifndef KDK_SCRIPT
#define KDK_SCRIPT

#include "module.h"
#include "mem.h"

typedef struct script{
    HMODULE hModule;
    tBuffer buffer;
    memTree * scope;
} script;

#endif