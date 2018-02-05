#ifndef PRS_PARSER
#define PRS_PARSER

#include "module.h"

#include "token.h"

#define TK_COMPLETE     0
#define TK_PENDING      1
#define TK_FAIL         2

int tokenize(Module *, char*);

#endif