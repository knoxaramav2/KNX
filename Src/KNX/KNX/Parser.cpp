#include "Parser.h"

#include <Debug.h>

extern Register masterRecord;
extern unsigned int MAX_NODES;
extern string globalBuffer;
extern systemState sysState;


void resolveSymbol(string raw, node*loc, ByteCode&seq)
{
	switch (getNumberType(raw))
	{
	case 2://double
	{
		seq.sequence.push_back(*(new ByteChar(raw, KMemory::_dbl_, true, new double(atof(raw.c_str())))));
		return;
	}
	case 1://signed
	{
		seq.sequence.push_back(*(new ByteChar(raw, KMemory::_sint_, true, new int(atoi(raw.c_str())))));
		return;
	}
	case 0://unsigned
	{
		seq.sequence.push_back(*(new ByteChar(raw, KMemory::_int_, true, new unsigned((unsigned)stol(raw.c_str())) )));
		return;
	}
	}
}

void interpret(string raw, node*loc)
{
	ByteCode byteSequence;
	enum rMode{_normal,_strlit,_comment,_charlit};
	rMode mode = rMode::_normal;
	unsigned ln = (unsigned)raw.size();

	//Tokenize
	unsigned lIndex = 0;
	for (unsigned loop = 0; loop <= ln; ++loop)
	{
		if (loop == ln)//end point
		{
			if (lIndex!=loop)
				switch (mode)
			{
				case rMode::_normal:
					resolveSymbol(string(raw.begin() + lIndex, raw.end()), loc, byteSequence);
					break;
				case rMode::_strlit:
				{
					byteSequence.sequence.push_back(*(new ByteChar(string(raw.begin() + lIndex, raw.begin() + loop), KMemory::_string_, true, (void*)&string(raw.begin() + lIndex, raw.begin() + loop))));
				}
					break;
				case rMode::_comment:
					break;
				case rMode::_charlit:
					if (loop - lIndex == 0)
						printError(EMPTY_CHAR, to_string(lIndex));
					else if (loop - lIndex>1)
						printError(EXCESS_CHAR, to_string(lIndex) + " : " + string(raw.begin() + lIndex, raw.begin() + loop));
					else
						byteSequence.sequence.push_back(*(new ByteChar(string(raw.begin() + lIndex, raw.begin() + loop), KMemory::_char_, true, new char (raw[loop-1]))));
					mode = rMode::_normal;
					break;
			}
			break;
		}

		if (mode == rMode::_strlit)
		{
			if (raw[loop] == '\"')
			{
				byteSequence.sequence.push_back(*(new ByteChar(string(raw.begin() + lIndex, raw.begin() + loop), KMemory::_string_, true, new string(raw.begin() + lIndex, raw.begin() + loop))));
				mode = rMode::_normal;
				lIndex = loop + 1;
			}
		}
		else if (mode == rMode::_charlit)
		{
			if (raw[loop] == '\'')
			{
				if (loop - lIndex == 0)
					printError(EMPTY_CHAR, to_string(loop));
				else if (loop-lIndex>1)
					printError(EXCESS_CHAR, to_string(loop) + " : " + string(raw.begin() + lIndex, raw.begin() + loop));
				else
					byteSequence.sequence.push_back(*(new ByteChar(string(raw.begin() + lIndex, raw.begin() + loop), KMemory::_char_, true, new char(raw[loop - 1]))));
				mode = rMode::_normal;
				lIndex = loop + 1;
			}
		}
		else if (mode == rMode::_comment)
		{
			if (raw[loop] == '#')
			{
				lIndex = loop + 1;
				mode = rMode::_normal;
			}
		}
		else
		{
			switch (raw[loop])
			{
				//text operators
			case '\"':
				if (lIndex<loop)
					resolveSymbol(string(raw.begin() + lIndex, raw.end()), loc, byteSequence);
				mode = rMode::_strlit;
				lIndex = loop + 1;
				break;
			case '\'':
				if (lIndex<loop)
					resolveSymbol(string(raw.begin() + lIndex, raw.end()), loc, byteSequence);
				mode = rMode::_charlit;
				lIndex = loop + 1;
				break;
				//comment
			case '#':
				if (lIndex<loop)
					resolveSymbol(string(raw.begin() + lIndex, raw.end()), loc, byteSequence);
				mode = rMode::_comment;
				lIndex = loop + 1;
				break;
				//arithematic operators
			case '+':{
				if (lIndex < loop)
					resolveSymbol(string(raw.begin() + lIndex, raw.end()), loc, byteSequence);
				lIndex = loop + 1;
				byteSequence.sequence.push_back(*(new ByteChar("+",KMemory::_add_,true,nullptr)));
				break; }
			case '-':
				if (lIndex<loop)
					resolveSymbol(string(raw.begin() + lIndex, raw.end()), loc, byteSequence);
				if (loop + 1 < ln)
					if (raw[loop + 1] >= '0' && raw[loop + 1] <= '9')
						continue;
				lIndex = loop + 1;
				break;
			case '/':
				if (lIndex<loop)
					resolveSymbol(string(raw.begin() + lIndex, raw.end()), loc, byteSequence);
				lIndex = loop + 1;
				break;
			case '^':
				if (lIndex<loop)
					resolveSymbol(string(raw.begin() + lIndex, raw.end()), loc, byteSequence);
				lIndex = loop + 1;
				break;
			case '%':
				if (lIndex<loop)
					resolveSymbol(string(raw.begin() + lIndex, raw.end()), loc, byteSequence);
				lIndex = loop + 1;
				break;
			case '*':
				if (lIndex<loop)
					resolveSymbol(string(raw.begin() + lIndex, raw.end()), loc, byteSequence);
				lIndex = loop + 1;
				break;
			case (char)-5://root
				if (lIndex<loop)
					resolveSymbol(string(raw.begin() + lIndex, raw.end()), loc, byteSequence);
				lIndex = loop + 1;
				break;
				//escape character
			case '\\':
				++loop;
				break;
			default:

				break;
			}
		}
	}

	if (sysState.prntDebug)
		printMem(byteSequence);
	printf("");
}