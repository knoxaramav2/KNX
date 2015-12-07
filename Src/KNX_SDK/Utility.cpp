#include "Utility.h"

//FNV-1a algorithm
__int64 FNV(string input)
{
	//start at x64 prime offset
	__int64 hash = 14695981039346656037;

	unsigned length = input.length();
	for (unsigned x = 0; x < length; ++x)
	{
		hash = hash^input[x];
		//x64 FNV-prime
		hash *= 1099511628211;
	}

	return hash;
}