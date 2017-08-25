#include <stdio.h>
#include <dlfcn.h>
#include <stdlib.h>
#include <string.h>

#include "debug.h"

#include "parser.h"
#include "node_reg.h"

static void startup() __attribute__((constructor));
static void shutdown() __attribute__((destructor));

void startup()
{
    dprint("Parser Loaded\r\n");
}

void shutdown()
{

    dprint("Parser Unloaded\r\n");
}