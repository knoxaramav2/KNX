#include <stdio.h>
#include <dlfcn.h>
#include <stdlib.h>
#include <string.h>

#include "TypeDecl.h"

static void startup() __attribute__((constructor));
static void shutdown() __attribute__((destructor));

void startup()
{

}

void shutdown()
{

}