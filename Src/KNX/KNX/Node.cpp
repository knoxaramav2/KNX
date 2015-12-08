#include "Node.h"

//EXTERN
//global node table
Register masterRecord;
unsigned int MAX_NODES = 25;

node::node(node*p)
{
	this->parent = (nodeBase*)p;
	active = false;
	id = 0;
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
	
	printf("Node [%u] created\n",nd->id);


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