#ifndef KNX_DATATR
#define KNX_DATATR

#include "KMem.h"

#include <vector>

using namespace std;

struct ByteChar
{
	unsigned char rawFlag : 1;
	unsigned char dataType : 7;
	void*data;
};

struct ByteCode
{
	vector <ByteChar> sequence;
};

#endif