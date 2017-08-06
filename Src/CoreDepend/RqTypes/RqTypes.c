#include <stdio.h>
#include <dlfcn.h>
#include <stdlib.h>
#include <string.h>

#include "TypeDecl.h"

static void startup() __attribute__((constructor));
static void shutdown() __attribute__((destructor));

void startup()
{
    printf("###################\r\n");

    type_reg * type_registry = getTypeRegistry();

    int fail = 0;
    
    fail += registerInt(type_registry);
    fail += registerUInt(type_registry);
}

void shutdown()
{

}