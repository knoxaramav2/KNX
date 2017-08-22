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
    
    //IMPORTANT!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    //Must be in order described in lexeme.h
    fail += registerSInt(type_registry);
    fail += registerUSInt(type_registry);
    fail += registerInt(type_registry);
    fail += registerUInt(type_registry);
    fail += registerLInt(type_registry);
    fail += registerULInt(type_registry);
    
    fail += registerFloat(type_registry);
    fail += registerDouble(type_registry);

    fail += registerChar(type_registry);
    fail += registerUChar(type_registry);
    fail += registerWChar(type_registry);
    fail += registerString(type_registry);
    fail += registerWString(type_registry);

    fail += registerArray(type_registry);
    fail += registerList(type_registry);
    fail += registerClass(type_registry);
    fail += registerByte(type_registry);
    fail += registerFunction(type_registry);
    fail += registerVoid(type_registry);
    fail += registerException(type_registry);
    fail += registerScript(type_registry);
}

void shutdown()
{

}