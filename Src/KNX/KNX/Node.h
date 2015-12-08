#ifndef NODE
#define NODE

#include <NodeCore.h>
#include <thread>
#include <string>

using namespace std;

class node : public nodeBase
{

};

//node loop
int nodeThread(node*,string);

#endif