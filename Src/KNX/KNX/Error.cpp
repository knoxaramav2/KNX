#include "Error.h"
#include <Utility.h>

#include <NodeCore.h>

#include <stdio.h>
#include <Windows.h>
#include <iostream>

using namespace std;

extern systemState sysState;

void printError(unsigned tp, string input)
{
	if (tp == 0)
		return;

	if (tp < WARN_MAX)
		if (!sysState.prntWarnings)
			return;
		else
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), YELLOW);
			printf("Warning <%d> ", tp);
		}
	else if (!sysState.prntErrors)
		return;
	else if (tp < ERR_MAX)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), RED);
		printf("Error <%d> ", tp);
	}

	switch (tp)
	{
	case 0:
		break;
		//warning
	case TYPE_CAST:printf("Implicit type conversion :%s\n",input.c_str()); break;

		//error
	case I_REQ_FAILED:printf("Input stream priority request denied"); break;
	case I_DEF_FAILED:printf("Input stream default request denied"); break;

	case NODE_GEN_FAIL:printf("Node failed to initialize"); break;
	case NODE_DEC_FAIL:printf("Node %s failed to deconstruct", input.c_str());

	case UNDEF_SYMB:printf("Symbol %s undefined", input.c_str()); break;
	case ILLEGAL_CAST:printf("Illegal type cast %s", input.c_str()); break;//use formate "of type1 to type2 : line"
	case EMPTY_CHAR:printf("Empty character: <%s>",input.c_str()); break;
	case EXCESS_CHAR:printf("Excessive input in character <%s>",input.c_str()); break;
	case RESOLVE_FAIL:printf("Symbol could not be resolved <%s>",input.c_str()); break;//symbol:line
		//MISC
	case MISC_ERR_WRN:printf("%s",input.c_str()); break;
	default:
		break;
	}
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);
	printf("\n");
}