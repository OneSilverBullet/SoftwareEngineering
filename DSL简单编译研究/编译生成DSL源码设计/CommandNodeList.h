#pragma once
#include "Node.h"
#include "CommandNode.h"

class CommandListNode :public Node
{
private:
	vector<Node*> CommandNodeList;

public:
	void parse(Context context)
	{
		while (true)
		{
			if (context.CurrentToken() == "end")
			{
				break;
			}
			else
			{
				Node* commandNode = new CommandNode();
				commandNode->parse(context);
				CommandNodeList.push_back(commandNode);
			}
		}
	}
	string toString()
	{
		//return list.toString();
		string result = "";
		for (int i = 0; i < CommandNodeList.size(); i++)
		{
			result = result +  CommandNodeList[i]->toString();
		}
		return result;
	}
};
