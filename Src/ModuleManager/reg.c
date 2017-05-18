#include "modreg.h"

#include <stdio.h>

mod_reg _modreg;

static void startup() __attribute__((constructor));
static void shutdown() __attribute__((destructor));

void startup()
{
    printf("Module Manager Loaded\r\n");
}

void shutdown()
{
    printf("Module Manager Unloaded\r\n");
}