#include "Parser.h"

#include <Debug.h>

extern Register masterRecord;
extern unsigned int MAX_NODES;
extern string globalBuffer;
extern systemState sysState;


void resolveSymbol(string raw, node*loc, ByteCode&seq)
{
	ByteChar bc;
	bc.data = nullptr;
	bc.dataType = KMemory::_unknown_;
	bc.rawFlag = true;
	bc.hash = FNV(raw);

	switch (getNumberType(raw))
	{
	case 2://double
	{
		bc.data = (void*)new double(atof(raw.c_str()));
		bc.dataType = KMemory::_dbl_;
		bc.rawFlag = true;
	}
		break;
	case 1://signed
	{
		bc.data = (void*)new int(atoi(raw.c_str()));
		bc.dataType = KMemory::_sint_;
		bc.rawFlag = true;
	}
		break;
	case 0://unsigned
	{
		bc.data = (void*)new unsigned((unsigned)stol(raw.c_str()));
		bc.dataType = KMemory::_int_;
		bc.rawFlag = true;
	}
		break;
	}


	//if nothing else, undefined explicit symbol
	bc.raw = raw;
	seq.sequence.push_back(bc);
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
					ByteChar bc;
					bc.rawFlag = true;
					bc.dataType = KMemory::_string_;
					bc.data = new string(raw.begin() + lIndex, raw.begin() + loop);
					byteSequence.sequence.push_back(bc);
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
					{
						ByteChar bc;
						bc.rawFlag = true;
						bc.dataType = KMemory::_char_;
						bc.data = new string(raw.begin() + lIndex, raw.begin() + loop);
						byteSequence.sequence.push_back(bc);
					}
					mode = rMode::_normal;
					break;
			}
			break;
		}

		if (mode == rMode::_strlit)
		{
			if (raw[loop] == '\"')
			{
				mode = rMode::_normal;
				ByteChar bc;
				bc.rawFlag = true;
				bc.dataType = KMemory::_string_;
				bc.data = static_cast<void*>(new string(raw.begin()+lIndex, raw.begin()+loop));
				byteSequence.sequence.push_back(bc);
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
				{
					ByteChar bc;
					bc.data = new string(raw.begin() + lIndex, raw.begin() + loop);
					bc.dataType = KMemory::_char_;
					bc.rawFlag = true;
					byteSequence.sequence.push_back(bc);
				}
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
				ByteChar bc;
				bc.raw = '+';
				bc.dataType = KMemory::_add_;
				bc.rawFlag = true;
				lIndex = loop + 1;
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
}