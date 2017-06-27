#ifndef EXEC
#define EXEC

#include "node.h"

#include "mathx.h"

token * execute(node *);

int runKeyword(node *, lexeme, token *);

#endif