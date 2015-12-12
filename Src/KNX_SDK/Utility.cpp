#include "Utility.h"

#include <Windows.h>
#include <string>

using namespace std;

//FNV-1a algorithm
__int64 FNV(string input)
{
	//start at x64 prime offset
	__int64 hash = 14695981039346656037;

	unsigned length = (unsigned) input.size();
	for (unsigned x = 0; x < length; ++x)
	{
		hash = hash^input[x];
		//x64 FNV-prime
		hash *= 1099511628211;
	}

	return hash;
}

string nextScope(string&input)
{
	string loScope;

	unsigned len = (unsigned) input.size();
	for (unsigned x = len - 1; x >= 0; ++x)
		if (input[x] == '.')
		{
			loScope=string(input.begin()+x+1,input.end());
			input.erase(input.begin() + x, input.end());
			return loScope;
		}
	//if no scope found, already lowest
	loScope = input;
	input = "";
	return loScope;
}

short getNumberType(string&input)
{
	bool parity = false;
	bool decimal = false;
	unsigned len = (unsigned)input.size();
	for (unsigned x = 0; x < len; ++x)
		if (input[x] == '.')
		{
			if (decimal)
				return -1;
			decimal = true;
		}
		else if (input[x] == '-')
		{
			if (x == 0)
				parity = true;
			else
				return -1;
		}
		else if (input[x]<'0' || input[x]>'9')
			return -1;
	
		if (decimal)
			return 2;
		if (parity)
			return 1;
		return 0;
}

#ifdef _WIN64
void printCLRMessage(string str, unsigned cd)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), YELLOW);
	if (cd > 0)
		printf(str.c_str(), cd);
	else
		printf(str.c_str());
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);
}
#endif
#ifdef __linux__//may add support for linux
void printCLRMessage(string str, unsigned cd)
{

}
#endif