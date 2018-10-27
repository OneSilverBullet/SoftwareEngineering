#pragma once
#include "Node.h"
#include "PrimitiveCommandNode.h"

class CommandNode : public Node
{
private:
	Node* node;
public:
	void parse(Context context)
	{
			node = new PrimitiveCommandNode();
			node->parse(context);
	}
	string toString()
	{
		return node->toString();
	}
};