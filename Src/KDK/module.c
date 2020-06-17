#include <stdlib.h>

#include "module.h"

Module * createModule(char * name){

    Module * module = malloc(sizeof(Module));
    module->name = name;

    return module;
}

int destroyModule(Module * module){

    if (module == 0)
        return 1;
    if (module->name != 0)
        free(module->name);
        
    free(module);

    return 0;
}