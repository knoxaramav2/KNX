#include <stdio.h>
#include <dlfcn.h>
#include <stdlib.h>
#include <string.h>

#include "executor.h"

static void startup() __attribute__((constructor));
static void shutdown() __attribute__((destructor));

void startup()
{



    printf("Executor Loaded\r\n");
}

void shutdown()
{

    printf("Executor Unloaded\r\n");
}