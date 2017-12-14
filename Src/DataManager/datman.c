#include <stdio.h>
#include <dlfcn.h>
#include <stdlib.h>
#include <string.h>

#include "datamanager.h"

static void startup() __attribute__((constructor));
static void shutdown() __attribute__((destructor));

//Constructor/Destructor
void startup()
{

}

void shutdown()
{

}