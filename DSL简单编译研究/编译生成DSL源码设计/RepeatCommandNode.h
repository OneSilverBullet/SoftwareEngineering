#pragma once
#include "Node.h"


extern class CommandNode;
class RepeatCommandNode :public Node
{
private:
	int number;
	Node* commandNode;
public:
	void parse(Context context)
	{
		context.skipToken("repeat");   //这里验证是重复操作，并且移动到下一位
		number = context.currentNumber();  //得到当前位的数字形式表达
		context.nextToken(); //继续下一位检测
		commandNode = new CommandNode();
		commandNode->parse(context);
	}

	string toString()
	{
		string a = "[repeat " + number;
		string b = a + " ";
		string c = b + commandNode->toString();
		return (c + "]");
	}
};

