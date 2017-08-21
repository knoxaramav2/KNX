#ifndef PSR_PARSER
#define PSR_PARSER

#include "node.h"
#include "module.h"

#define TK_COMPLETE     0
#define TK_PENDING      1
#define TK_FAIL         2

int tokenize(HMODULE *, char*);

#endif