#ifndef EXEC
#define EXEC

#include "node.h"

int execute(node *);

int runKeyword(node *, lexeme, token *);

#endif