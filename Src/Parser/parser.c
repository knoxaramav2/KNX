#include <stdio.h>
#include <dlfcn.h>
#include <stdlib.h>
#include <string.h>

#include "l_queue.h"

L_QUEUE _L_QUEUE;

static void startup() __attribute__((constructor));
static void shutdown() __attribute__((destructor));

void initQueue();

void startup()
{
    initQueue();
}

void shutdown()
{

}


void initQueue(){
    _L_QUEUE.opIdx      = 0;
    _L_QUEUE.outIdx     = 0;
    _L_QUEUE.encapLevel = 0;
    _L_QUEUE.cntInput   = 0;
}