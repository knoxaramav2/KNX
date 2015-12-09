#include "Node.h"
#include "Error.h"

#include <iostream>
#include <string>

using namespace std;

//EXTERN
//global databases and settings
extern Register masterRecord;
extern unsigned int MAX_NODES;
extern string globalBuffer;
extern systemState sysState;

node::node(node*p)
{
	if (p != nullptr)
	{
		this->parent = (nodeBase*)p;
		global = p->parent->global;
	}
	else
	{
		parent = nullptr;
		global = new memCore();
	}
	
	active = true;
	id = 0;
	usrInput = false;
}

node::~node()
{
	//deactivate children
	unsigned ln = (unsigned) children.size();
	for (unsigned x = 0; x < ln; ++x)
		if (children[x] != nullptr)
			children[x]->active = false;
}

void node::removeChild(node*nb)
{
	unsigned ln = (unsigned)nb->children.size();

	for (unsigned x = 0; x < ln; ++x)
		if (children[x] == nb)
		{
			children.erase(children.begin()+x);
			return;
		}
}


int nodeThread(node*parent, string cmd)
{
	node*nd = masterRecord.registerNode(parent);
	if (nd == nullptr)
	{
		printf("Error: Node failed to register\n");
		return -1;
	}
	
	printError(3000,"Hello world\n");
	printf("Node [%u] created\n",nd->id);

	while (nd->active)
	{
		if (nd->usrInput && sysState.I_hndle==nd)
		{
			printf("%d >> ",nd->id);
			string input;
			getline(cin, input);
		}
	}

	printf("Node [%u] destroyed\n", nd->id);
	masterRecord.deregisterNode(nd);

	return 0;
}


node*Register::registerNode(node*t)
{
	unsigned short cId = 0;

	if ((unsigned short)table.size() == MAX_NODES)
		return nullptr;

	unsigned ln = (unsigned) table.size();
	for (unsigned x = 0; x < ln; ++x)
	{
		if (!table[x])
		{
			printf("Alert: NULL node found in register table\n");
			table.erase(table.begin() + ln);
			--ln;
			--x;
		}
		else if (cId == table[x]->id)
		{
			++cId;
			x = 0;
		}
		else
			break;
	}

	table.push_back(new node(t));
	table[ln]->id = cId;
	if (cId == 0)//is root
	{
		if (!sysState.requestInput(table[ln]))
			printError(I_REQ_FAILED,"");
		if (!sysState.assignDefault((nodeBase*)table[ln]))
			printError(I_DEF_FAILED,"");
		table[ln]->usrInput = true;
	}	
	if (table[ln]->parent != nullptr)
		table[ln]->parent->children.push_back((nodeBase*)table[ln]);
	return table[ln];
}

void Register::deregisterNode(node*t)
{
	if (t == nullptr)
		return;
	unsigned ln = (unsigned)table.size();
	for (unsigned x = 0; x < ln; ++x)
		if (!table[x])
		{
			printf("Alert: NULL node found in register table\n");
			table.erase(table.begin()+ln);
			--ln;
			--x;
		}
		else if (table[x]->id == t->id)
		{
			if (table[x]->parent != nullptr)
				static_cast<node*>(table[x]->parent)->removeChild(table[x]);
			table[x] = nullptr;
			delete table[x];
			table.erase(table.begin()+x);
			return;
		}
}

bool Register::isEmpty()
{
	return table.size() == 0;
}