#include "Error.h"

#include <NodeCore.h>

#include <stdio.h>
#include <Windows.h>
#include <iostream>

using namespace std;

extern systemState sysState;

#ifdef _WIN64
#define BLACK	0
#define BLUE	1
#define GREEN	2
#define RED		4
#define YELLOW	14
#define WHITE	15
void printWrn(string str,unsigned cd)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),YELLOW);
	if (cd > 0)
		printf(str.c_str(), cd);
	else
		printf(str.c_str());
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);
}

void printErr(string str, unsigned cd)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), RED);
	if (cd > 0)
		printf(str.c_str(), cd);
	else
		printf(str.c_str());
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);
}
#endif
#ifdef __linux__//may add support for linux
void printWrn(string str)
{

}

void printErr(string str)
{

}
#endif

void printError(unsigned tp, string input)
{
	if (tp == 0)
		return;

	if (tp < WARN_MAX)
		if (!sysState.prntWarnings)
			return;
		else
			printWrn("Warning <%d>\n", tp);
	else if (!sysState.prntErrors)
		return;
	else
		printErr("Error <%d>\n", tp);

	switch (tp)
	{
	case 0:
		break;
		//warning
	case TYPE_CAST:printf("Implicit type conversion :%s\n",input.c_str()); break;

		//error
	case I_REQ_FAILED:printf("Input stream priority request denied");break;
	case I_DEF_FAILED:printf("Input stream default request denied"); break;

	case UNDEF_SYMB:printf(""); break;
	case ILLEGAL_CAST:printf(""); break;
	default:
		break;
	}

	printf("\n");
}