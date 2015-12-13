#include "DataTrns.h"

ByteChar::ByteChar()
{
	rawFlag = false;
	dataType = 0;
	data = nullptr;
	hash = 0;
}

ByteChar::ByteChar(const ByteChar&bc)
{
	printf("Copy\n");
	raw = bc.raw;
	rawFlag = bc.rawFlag;
	dataType = bc.dataType;
	hash = bc.hash;
	//copy data pointer
	switch (dataType)
	{
	case KMemory::_unknown_:
		data = nullptr;
		break;
	case KMemory::_sint_:
		if (rawFlag)
			data = new short((short)bc.data);
		break;
	case KMemory::_int_:
		if (rawFlag)
			data = new int((int)bc.data);
		printf(">DBG> %d\n",(int)data);
		break;
	case KMemory::_lint_:
		if (rawFlag)
			data = new long((long)bc.data);
		break;
	case KMemory::_char_:
		if (rawFlag)
			data = new char((char)bc.data);
		break;
	case KMemory::_string_:
		if (rawFlag)
			data = new string((string&)bc.data);
		break;
	default://should never happen
		data = nullptr;
		break;
	}
}

ByteChar::~ByteChar()
{
	//printf("Deconstructing\n");
	if (data != nullptr)
	{
		if (dataType == KMemory::_int_)
			delete reinterpret_cast<int*>(data);
		else if (dataType == KMemory::_dbl_)
			delete reinterpret_cast<double*>(data);
		else if (dataType == KMemory::_char_)
			delete reinterpret_cast<char*>(data);
		else if (dataType == KMemory::_string_)
			delete reinterpret_cast<string*>(data);
		data = nullptr;
	}
}


void ByteCode::add(ByteChar*bc)
{
	sequence.push_back(bc);
}

ByteCode::~ByteCode()
{
	for (unsigned x = 0; x < sequence.size(); ++x)
		sequence[x]->~ByteChar();
}