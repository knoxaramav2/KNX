#include "DataTrns.h"

ByteChar::ByteChar()
{
	rawFlag = false;
	dataType = 0;
	data = nullptr;
	hash = 0;
}

ByteChar::ByteChar(string r, unsigned t, bool f, void*d)
{
	raw = r;
	dataType = t;
	rawFlag = f;
	data = d;
	hash = FNV(r);
}


ByteChar::~ByteChar()
{
	if (data != nullptr)
	{
		delete data;
		data = nullptr;
	}
}