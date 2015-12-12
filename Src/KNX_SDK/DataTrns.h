#ifndef KNX_DATATR
#define KNX_DATATR

#include "KMem.h"

#include <vector>

using namespace std;

struct ByteChar
{
	ByteChar();
	ByteChar(string, unsigned, bool, void*);
	~ByteChar();

	string raw;
	unsigned char rawFlag : 1;
	unsigned char dataType : 7;
	void*data;
	size_t hash;
};

struct ByteCode
{
	vector <ByteChar> sequence;
};

#endif