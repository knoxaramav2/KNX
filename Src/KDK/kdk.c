
#include <stdio.h>
#include <stdlib.h>

#include "config.h"

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

//General

Config * getDefaultConfig(){
    Config * config = malloc(sizeof(Config));

    config->suppressWarning = 0;
    config->pendantic = 0;
    config->fatalWarn = 0;

    config->maxNodes = 256;
    config->maxThreads = 512;

    return config;
}