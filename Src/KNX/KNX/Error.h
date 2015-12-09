#ifndef KNX_ERR
#define KNX_ERR

#include <string>
using namespace std;

#define WARN_MAX	1000

#define ERR_MAX		2000

//Warnings

//Parser
#define TYPE_CAST		201//type autocasted

//Errors

//System----------
#define I_REQ_FAILED	1001//std input handle denied to root
#define I_DEF_FAILED	1002//std input (defualt) denied to root

//Node
#define NODE_GEN_FAIL	1101//fails to generate
#define NODE_DEC_FAIL	1102//fails to deconstruct

//Parser
#define UNDEF_SYMB		1201//undefined symbol
#define ILLEGAL_CAST	1202//incompatible argument

void printError(unsigned, string);

#endif