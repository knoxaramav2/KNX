#ifndef KNX_DATATR
#define KNX_DATATR

#include <vector>

using namespace std;

struct ByteChar
{
	char rawFlag : 1;
	char dataType : 7;
	void*data;
};

struct ByteCode
{
	vector <ByteChar> sequence;
};

#endif