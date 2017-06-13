#include <stdlib.h>
#include <string.h>

#include "token.h"

tBuffer createTBuffer()
{
    tBuffer ret;

    memset(ret.opStack, 0, sizeof ret.opStack);
    ret.oCount = 0;

    ret.head = NULL;
    ret.tokens = NULL;
    ret.tCount = 0;

    return ret;
}