#ifndef EXEC
#define EXEC

#include "node.h"

#include "math.h"

int execute(node *);

int runKeyword(node *, lexeme, token *);

#endif