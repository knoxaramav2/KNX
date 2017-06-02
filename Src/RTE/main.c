/*
starting point for KNX interpreter
*/

#include <stdio.h>

#include "globals.h"
#include "startup.h"

comp_handle _info;

int main(int argc, char ** argv)
{

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