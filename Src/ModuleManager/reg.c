#include <stdio.h>
#include <dlfcn.h>
#include <stdlib.h>
#include <string.h>

#include "debug.h"

#include "modreg.h"

mod_reg _modreg;

static void startup() __attribute__((constructor));
static void shutdown() __attribute__((destructor));

void startup()
{
    _modreg.count = 0;
    _modreg.handles = malloc(0);

    dprint("Module Manager Loaded\r\n");
}

void shutdown()
{
    for(int i = 0; i < _modreg.count; ++i){
        dlclose(_modreg.handles[i]->handle);
    }

    dprint("Module Manager Unloaded\r\n");
}

void register_module(char * libpath)
{
    void * handle;
    handle = dlopen(libpath, RTLD_LAZY);

    _modreg.handles = realloc(_modreg.handles, (_modreg.count+1) * sizeof(comp_handle*));
    _modreg.handles[_modreg.count] = malloc(sizeof(comp_handle));
    _modreg.handles[_modreg.count]->handle = handle;
    _modreg.handles[_modreg.count]->name = malloc(strlen(libpath)+1);
    strncpy(
        _modreg.handles[_modreg.count]->name,
        libpath,
        strlen(libpath)+1
    );
    
    ++_modreg.count;
}

void * getModuleHandle(char * name)
{
    for(int i = 0; i < _modreg.count; ++i)
    {
        if (strncmp(name, _modreg.handles[i]->name, 256) == 0)
            return _modreg.handles[i]->handle;
    }

    return NULL;
}