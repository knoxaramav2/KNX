#ifndef EXEC_KEYWORD
#define EXEC_KEYWORD

#include "module.h"

token * runKeyword(HMODULE * module, token * arg, lexeme word);
token * runOperator(token * arg, lexeme word);

#endif