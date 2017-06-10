#include "kdk.h"

#include <stdio.h>

static void startup() __attribute__((constructor));
static void shutdown() __attribute__((destructor));

void startup()
{
    printf("Starting kdk\r\n");fflush(stdout);
    generateConfig();
}

void shutdown()
{

}

void init_sdk()
{
    printf("KDK setup\r\n");
    initDbgGlb();
    initDatTable();
}