
#include <stdio.h>

static void startup() __attribute__((constructor));
static void shutdown() __attribute__((destructor));

void startup()
{

}

void shutdown()
{

}

void init_sdk()
{

}