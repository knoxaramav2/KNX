#ifndef UTIL
#define UTIL

#include <string>

using namespace std;

/*
Defines convenient functions for common operations 
*/

//FNV-1a algorithm
__int64 FNV(string input);

//split member/scope reference
string nextScope(string&);

//-1 not valid number, 0 int_16, 1 int_32, 2 int_64, 3 double
short getNumberType(string&);

//---------------OUTPUTS----------------//
#define BLACK	0
#define BLUE	1
#define GREEN	2
#define RED		4
#define YELLOW	14
#define WHITE	15

#ifdef _WIN64
void printCLRMessage(string,unsigned);
#endif
#ifndef __linux__
void printCLRMessage(string, unsigned);
#endif
#endif