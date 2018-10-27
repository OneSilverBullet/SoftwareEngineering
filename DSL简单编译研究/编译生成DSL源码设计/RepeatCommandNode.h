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
		context.skipToken("repeat");   //������֤���ظ������������ƶ�����һλ
		number = context.currentNumber();  //�õ���ǰλ��������ʽ���
		context.nextToken(); //������һλ���
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

