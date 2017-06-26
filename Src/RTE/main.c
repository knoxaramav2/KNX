/*
starting point for KNX interpreter
*/

#include <stdio.h>

#include "KDK.h"
#include "globals.h"
#include "startup.h"

#include "lexeme.h"

comp_handle _info;

#define SYS_DEBUG

int main(int argc, char ** argv)
{
init_sdk();

int rCode = 0;

if ((rCode = initComponents()))
    return rCode |= 0xA;
if ((rCode = parseCmd(argc, argv)))
    return rCode |= 0xB;
if ((rCode = startRoot()))
    return rCode |= 0xC;
if ((rCode = shutdown()))
    return rCode |= 0xD;


return rCode;
}