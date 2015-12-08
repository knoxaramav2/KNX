#include <string>

#include "Node.h"

using namespace std;


int main(int argc, char**argv)
{

	string cmd;
	if (argc > 1)
		cmd = argv[1];
	//create root node
	thread node0(nodeThread,nullptr, cmd);
	node0.join();

	return 0;
}