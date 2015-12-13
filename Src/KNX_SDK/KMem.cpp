#include "KMem.h"

#include <string>
using namespace std;

_boolean::_boolean(string ttl, bool v)
{
	this->mType = KMemory::_bool_;
	this->value = v;
	this->hash = FNV(ttl);
	available = true;
}

_short_integer::_short_integer(string ttl, short v)
{
	this->mType = KMemory::_sint_;
	this->value = v;
	this->hash = FNV(ttl);
	available = true;
}

_integer::_integer(string ttl, int v)
{
	this->mType = KMemory::_int_;
	this->value = v;
	this->hash = FNV(ttl);
	available = true;
}

_long_integer::_long_integer(string ttl, __int64 v)
{
	this->mType = KMemory::_lint_;
	this->value = v;
	this->hash = FNV(ttl);
	available = true;
}


_double::_double(string ttl, double v)
{
	this->mType = KMemory::_dbl_;
	this->value = v;
	this->hash = FNV(ttl);
	available = true;
}


_char::_char(string ttl, char v)
{
	this->mType = KMemory::_char_;
	this->value = v;
	this->hash = FNV(ttl);
	available = true;
}

_string::_string(string ttl, string v)
{
	this->mType = KMemory::_string_;
	this->value = v;
	this->hash = FNV(ttl);
	available = true;
}


_port::_port(string ttl, string trg)
{
	this->target = trg;
	this->mType = KMemory::_port_;
	this->hash = FNV(ttl);
	available = true;
}

_pipe::_pipe(string ttl)
{
	this->mType = KMemory::_port_;
	this->hash = FNV(ttl);
	available = true;
}


_array::_array(string ttl, KMemory km)
{
	this->targetType = km;
	this->mType = KMemory::_string_;
	this->hash = FNV(ttl);
	available = true;
}

_struct::_struct(string ttl)
{
	this->mType = KMemory::_struct_;
	this->hash = FNV(ttl);
	available = true;
}