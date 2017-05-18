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
    return rCode;
if ((rCode = parseCmd()))
    return rCode;
if ((rCode = startRoot()))
    return rCode;
if ((rCode = shutdown()))
    return rCode;


return rCode;
}