#ifndef KNX_NODECORE
#define KNX_NODECORE

#define INTERRUPT		0x4

#include <vector>

using namespace std;

//node super class
struct nodeBase
{
	unsigned short id;
	nodeBase*parent;
	vector <nodeBase*> children;
	bool active;
	bool usrInput;//wait for user input in loop;
	void interrupt();//interrupts if waiting for input, forces continue
};

#endif