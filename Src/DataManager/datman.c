#include <stdio.h>
#include <dlfcn.h>
#include <stdlib.h>
#include <string.h>

#include "datamanager.h"
#include "node_reg.h"

static void startup() __attribute__((constructor));
static void shutdown() __attribute__((destructor));

void startup()
{



    printf("Data Manager Loaded\r\n");
}

void shutdown()
{

    printf("Data Manager Unloaded\r\n");
}