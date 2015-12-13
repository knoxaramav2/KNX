#include "Debug.h"

#include <Windows.h>

//prints:: symbol : hash : raw : data
void printObj(ByteChar*bc)
{
	if (!bc)
	{
		printf("Invalid bytechar\n");
		return;
	}
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), LIGHTCYAN);

	printf("%s : %llu : %s : ", bc->raw.c_str(), bc->hash, bc->rawFlag ? "RAW" : "SYMBOLIC");

	switch (bc->dataType)
	{
	case KMemory::_unknown_:
		printf("SYMBOL : N/A\n");
		break;
	case KMemory::_int_:
		printf("INTEGER : %d\n", *reinterpret_cast<int*>(bc->data));
		break;
	case KMemory::_dbl_:
		printf("DOUBLE : %f\n", *reinterpret_cast<double*>(bc->data));
		break;
	case KMemory::_char_:
		printf("CHARACTER : %c\n", *reinterpret_cast<char*>(bc->data));
		break;
	case KMemory::_string_:
		printf("STRING : %s\n", reinterpret_cast<string*>(bc->data)->c_str());
		break;
	case KMemory::_add_:
		printf("ADDITION\n");
		break;
	}
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);
}

void printMem(ByteCode&bc)
{
	unsigned len = (unsigned) bc.sequence.size();
	for (unsigned x = 0; x < len; ++x)
		printObj(bc.sequence[x]);
}