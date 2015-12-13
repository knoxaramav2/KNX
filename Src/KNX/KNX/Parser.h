#ifndef KNX_PARSER
#define KNX_PARSER

#include <string>
#include <vector>

#include "Error.h"
#include "Node.h"

extern Register masterRecord;
extern unsigned int MAX_NODES;
extern string globalBuffer;
extern systemState sysState;

using namespace std;

void interpret(string, node*);
void tokenize(string&, node*);

#endif