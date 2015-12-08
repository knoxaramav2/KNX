#include "Node.h"

//global node table
Register masterRecord;

node::node(node*p)
{
	this->parent = (nodeBase*)p;
	active = false;
	id = 0;
}

node::~node()
{

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
	unsigned ln = (unsigned) table.size();
	for (unsigned x = 0; x < ln; ++x)
	{
		if (!table[x]->id)
			printf("Alert: NULL node found in register table\n");
		else if (cId == table[x]->id)
		{

		}
		else
		{
			table.push_back(new node(t));
			table[ln]->id = cId;
			table[ln]->children.push_back((nodeBase*)table[ln]);
			return table[ln];
		}
	}

	return nullptr;
}

void Register::deregisterNode(node*t)
{
	unsigned ln = (unsigned)table.size();
	for (unsigned x = 0; x < ln; ++x)
		if (!table[ln])
			printf("Alert: NULL node found in register table\n");
		else
		{

		}
}