#include <stdio.h>
#include <dlfcn.h>
#include <stdlib.h>
#include <string.h>

#include "KwDecl.h"

func_reg * keyword_registry = NULL;

static void startup() __attribute__((constructor));
static void shutdown() __attribute__((destructor));

void startup()
{
    keyword_registry = getKeywordRegistry();

    //REGISTER CONTROL KW's
    registerFunction(keyword_registry, kw_if, "if");
}

void shutdown()
{

}