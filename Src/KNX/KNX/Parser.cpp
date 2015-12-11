#include "Parser.h"


void resolveSymbol(string raw, node*loc, ByteCode&seq)
{
	ByteChar bc;
	bc.data = nullptr;
	bc.dataType = 0;
	bc.rawFlag = true;

	switch (getNumberType(raw))
	{
	case 2://double

		break;
	case 1://unsigned

		break;
	case 0://signed

		break;
	}

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
					ByteChar bc;
					bc.rawFlag = true;
					bc.dataType = KMemory::_string_;
					bc.data = new string(raw.begin() + lIndex, raw.begin() + loop);
					byteSequence.sequence.push_back(bc);
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
				bc.data = new string(raw.begin()+lIndex,raw.begin()+loop);
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
				mode = rMode::_strlit;
				lIndex = loop + 1;
				break;
			case '\'':
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
			case '+':
				if (lIndex<loop)
					resolveSymbol(string(raw.begin() + lIndex, raw.end()), loc, byteSequence);
				mode = rMode::_comment;
				lIndex = loop + 1;
				break;
			case '-':
				if (lIndex<loop)
					resolveSymbol(string(raw.begin() + lIndex, raw.end()), loc, byteSequence);
				mode = rMode::_comment;
				lIndex = loop + 1;
				break;
			case '/':
				if (lIndex<loop)
					resolveSymbol(string(raw.begin() + lIndex, raw.end()), loc, byteSequence);
				mode = rMode::_comment;
				lIndex = loop + 1;
				break;
			case '^':
				if (lIndex<loop)
					resolveSymbol(string(raw.begin() + lIndex, raw.end()), loc, byteSequence);
				mode = rMode::_comment;
				lIndex = loop + 1;
				break;
			case '%':
				if (lIndex<loop)
					resolveSymbol(string(raw.begin() + lIndex, raw.end()), loc, byteSequence);
				mode = rMode::_comment;
				lIndex = loop + 1;
				break;
			case '*':
				if (lIndex<loop)
					resolveSymbol(string(raw.begin() + lIndex, raw.end()), loc, byteSequence);
				mode = rMode::_comment;
				lIndex = loop + 1;
				break;
			case (char)-5://root
				if (lIndex<loop)
					resolveSymbol(string(raw.begin() + lIndex, raw.end()), loc, byteSequence);
				mode = rMode::_comment;
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

	for (ByteChar bc : byteSequence.sequence)
		printCLRMessage(to_string((int)bc.dataType) + ' ' + to_string((int)bc.rawFlag)+'\n',GREEN);
}