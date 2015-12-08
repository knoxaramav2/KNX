#ifndef KNX_NODECORE
#define KNX_NODECORE

#include <vector>

using namespace std;

//node super class
struct nodeBase
{
	unsigned short id;
	nodeBase*parent;
	vector <nodeBase*> children;
	bool active;
};

#endif