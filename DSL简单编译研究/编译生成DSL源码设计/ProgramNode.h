#pragma once
#include "Node.h"
#include "CommandNodeList.h"

// ∂‘”¶”Ô∑®£∫<program> ::= program <command list>
class ProgramNode :public Node
{
private:
	Node* commandNode;

public:
	void parse(Context context)
	{
		context.skipToken("program");
		commandNode = new CommandListNode();
		commandNode->parse(context);
	}

	string toString()
	{
		string a = "<program> " + commandNode->toString();
		return a + "</program>";
	}
};