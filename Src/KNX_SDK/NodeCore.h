#ifndef KNX_NODECORE
#define KNX_NODECORE

#define GLOBAL_INPUT	nullptr
#define INTERRUPT		0x4

#include "DataTrns.h"
#include "KMem.h"

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
	vector <ByteCode> stack;
	memCore*global;
	memCore local;
};

//controls resource allocation such as I/O streams,
//system options
struct systemState
{
	systemState();

	nodeBase*def_hndle;//handle to default to after release
	nodeBase*I_hndle;//keyboard input stream target handle

	bool requestInput(nodeBase*);
	bool releaseInput(nodeBase*);
	bool assignDefault(nodeBase*);

	//option flags
	unsigned prntErrors : 1;
	unsigned prntWarnings : 1;
};

#endif