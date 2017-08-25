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
    registerFunction(keyword_registry, kw_if, "else");
    registerFunction(keyword_registry, kw_if, "elif");
    registerFunction(keyword_registry, kw_if, "do");
    registerFunction(keyword_registry, kw_if, "while");
    registerFunction(keyword_registry, kw_if, "for");
    registerFunction(keyword_registry, kw_if, "switch");
    registerFunction(keyword_registry, kw_if, "case");
    registerFunction(keyword_registry, kw_if, "break");
    registerFunction(keyword_registry, kw_if, "continue");

    //REGISTER UTIL KW's
    registerFunction(keyword_registry, kw_typeof, "typeof");
    registerFunction(keyword_registry, kw_if, "delete");
    registerFunction(keyword_registry, kw_if, "cast");
    registerFunction(keyword_registry, kw_if, "import");
    registerFunction(keyword_registry, kw_run, "run");
    registerFunction(keyword_registry, kw_if, "release");
    registerFunction(keyword_registry, kw_quit, "quit");
    registerFunction(keyword_registry, kw_print, "print");
    registerFunction(keyword_registry, kw_if, "throw");
    registerFunction(keyword_registry, kw_if, "try");
    registerFunction(keyword_registry, kw_if, "catch");
}

void shutdown()
{

}