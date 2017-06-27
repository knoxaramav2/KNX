#ifndef EXEC
#define EXEC

#include "node.h"

#include "mathx.h"

token * execute(node *);

token * runKeyword(node *, lexeme, token *);
token * runOperator(node *, lexeme, token *);

#endif