#include <stdio.h>
#include <dlfcn.h>
#include <stdlib.h>
#include <string.h>

#include "debug.h"

#include "executor.h"

static void startup() __attribute__((constructor));
static void shutdown() __attribute__((destructor));

void startup()
{



    dprint("Executor Loaded\r\n");
}

void shutdown()
{

    dprint("Executor Unloaded\r\n");
}