#ifndef EXEC_KEYWORD
#define EXEC_KEYWORD

#include "module.h"
#include "function.h"

token * runKeyword(HMODULE * module, token * arg, function fnc);
token * runOperator(token * arg, lexeme word);

#endif