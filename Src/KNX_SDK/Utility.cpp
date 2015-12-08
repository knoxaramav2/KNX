#include "Utility.h"

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