#ifndef KNX_DATATR
#define KNX_DATATR

#include "KMem.h"

#include <vector>

using namespace std;

struct ByteChar
{
	ByteChar();
	ByteChar(const ByteChar&);//copy constructor
	~ByteChar();

	string raw;
	unsigned char rawFlag : 1;
	unsigned char dataType : 7;
	void*data;//only assign with 'new' operator
	size_t hash;
};

struct ByteCode
{
	~ByteCode();
	vector <ByteChar*> sequence;
	void add(ByteChar*);
};

#endif