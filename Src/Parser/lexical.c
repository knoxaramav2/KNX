#include <stdio.h>
#include <string.h>

#include "parser.h"

//TODO implement modified shunting yard as in docs
int tokenize(node * node, char * raw)
{

    printf("Input: %s from node %d\r\n", raw, node->id_index);

    return TK_COMPLETE;
}