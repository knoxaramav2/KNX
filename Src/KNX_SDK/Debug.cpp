#include "Debug.h"

#include <Windows.h>

//prints:: symbol : hash : raw : data
void printObj(ByteChar&bc)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), LIGHTBLUE);

	printf("%s : %llu : %s : ", bc.raw.c_str(), bc.hash, bc.rawFlag ? "RAW" : "SYMBOLIC");

	switch (bc.dataType)
	{
	case KMemory::_unknown_:
		printf("SYMBOL : N/A\n");
		break;
	case KMemory::_sint_:
		printf("SIGNED INTEGER : %d\n",*static_cast<int*>(bc.data));
		break;
	case KMemory::_int_:
		printf("UNSIGNED INTEGER : %u\n", *static_cast<unsigned*>(bc.data));
		break;
	case KMemory::_lint_:
		printf("LONG INTEGER : %llu\n", *static_cast<size_t*>(bc.data));		break;
	case KMemory::_dbl_:
		printf("DOUBLE : %f\n", *static_cast<double*>(bc.data));		break;
	case KMemory::_char_:
		printf("CHAR: %c\n", *static_cast<char*>(bc.data));		break;
	case KMemory::_string_:
		printf("STRING : %s\n", static_cast<string*>(bc.data)->c_str());break;//TODO: free string pointer
	case KMemory::_arr_:
		break;
	case KMemory::_port_:
		break;
	case KMemory::_pipe_:
		break;
	case KMemory::_struct_:
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