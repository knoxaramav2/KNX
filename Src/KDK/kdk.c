#include "kdk.h"
#include "debug.h"

#include <stdio.h>

static void startup() __attribute__((constructor));
static void shutdown() __attribute__((destructor));

void startup()
{
    generateConfig();
    loadDefaultConfig();
}

void shutdown()
{

}

void init_sdk()
{
    initDbgGlb();
    initDatTable();
}