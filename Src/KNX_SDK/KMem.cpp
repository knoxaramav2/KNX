#include "KMem.h"

#include <string>
using namespace std;

_short_integer::_short_integer(string ttl, short v)
{
	this->mType = KMemory::_sint_;
	this->value = v;
	this->hash = FNV(ttl);
	available = true;
}