#include <string>

#include "Node.h"

//stores input directly into 
Register masterRecord;
unsigned int MAX_NODES = 25;
string globalBuffer;
extern systemState sysState;

using namespace std;

void parseCMD(string cmd)
{

}

int main(int argc, char**argv)
{
	string cmd;
	if (argc > 1)
		cmd = argv[1];
	parseCMD(cmd);
	//create root node
	thread node0(nodeThread,nullptr, cmd);
	node0.join();

	//grab user input to store in global buffer
	/*
	while (masterRecord.isEmpty() && sysState.I_hndle==GLOBAL_INPUT)
	{
		char c=getchar();
		switch (c)
		{
		case '\n':
			printf(">> %s\n",globalBuffer.c_str());
			globalBuffer.clear();
			break;
		case '\b\b':
			if (globalBuffer.size() == 0)
				break;
			globalBuffer.erase(globalBuffer.end());
			break;
		default:
			globalBuffer += c;
			break;
		}
		printf("%s\n",globalBuffer.c_str());
	}*/

	return 0;
}