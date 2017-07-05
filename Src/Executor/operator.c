#include "token.h"
#include "node.h"

#include "executor.h"

token * runOperator(token * arg, lexeme word)
{

    if (isMath(word))
        return math(arg, arg->right, word);

    return NULL;
}