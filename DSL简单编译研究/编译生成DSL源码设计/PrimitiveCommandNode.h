#pragma once
#include "Node.h"

class PrimitiveCommandNode :public Node
{
private:
	string name;
public:
	void parse(Context context)
	{
		name = context.CurrentToken();
		context.skipToken(name);
		if (!(name == "object") && !(name == "height") && !(name == "width"))
		{
			cerr << "there is no such expression";
		}
	}
	string toString()
	{
		string a = "<" + name + ">" + "</" + name + ">";
		return a;
	}
};