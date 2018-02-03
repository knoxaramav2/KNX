#include <stdlib.h>

#include "module.h"

Module * createModule(){

    Module * module = malloc(sizeof(Module));

    return module;
}

int destroyModule(Module * module){

    free(module);

    return 0;
}