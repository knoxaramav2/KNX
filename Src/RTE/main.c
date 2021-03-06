/*
starting point for KNX interpreter
*/

#include <stdio.h>

#include "KDK.h"
#include "globals.h"
#include "startup.h"
#include "lexeme.h"

#include "type.h"

comp_handle _info;

#define SYS_DEBUG

typedef int (*testfunc)();

int main(int argc, char ** argv)
{

init_sdk();

int rCode = 0;

nodeArg * arg = createNodeArg();

if ((rCode = initComponents()))
    return rCode |= 0xA;
if ((rCode = parseCmd(argc, argv, arg)))
    return rCode |= 0xB;
if ((rCode = startRoot(arg)))
    return rCode |= 0xC;
if ((rCode = shutdown()))
    return rCode |= 0xD;


return rCode;
}