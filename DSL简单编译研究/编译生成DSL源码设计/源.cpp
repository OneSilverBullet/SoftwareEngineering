#include <iostream>
#include <string>
#include <list>
#include <vector>
#include <sstream>
using namespace std;

class Context;

class CommandListNode;

class Node {
public:
	virtual void parse(Context context) = 0;
};

vector<string> ReadCommand(string str)
{
	vector<string> commandList;
	stringstream ss(str);
	string word;
	while (ss >> word)
	{
		commandList.push_back(word);
		word.clear();
	}
	return commandList;
}

class Context {
private:
	string currentToken; 
	vector<string> commandList;
	int index = 0;
public:
	Context(string text) 
	{
		//初始化的时候就将值都初始化好
		commandList = ReadCommand(text);
		nextToken(); 
	} // 获取下一个标记 

	string nextToken() 
	{ 
		if (index < commandList.size()) 
		{
			currentToken = commandList[index];
			index++;
		} 
		else
		{
			cerr << "out of the commandList range!!" << endl;
		}
		return currentToken; 
	}

	// 访问当前标记 
	string CurrentToken() 
	{ 
		return currentToken; 
	} 

	//先检查当前标记，然后获取下一个标记 
    string skipToken(string token)
	{ 
		return nextToken(); 
	}

	//获取当前标记对应的数值 
	int currentNumber() {
		int number = 0; 
		char* end;
		//将string转化为int
		number = static_cast<int>(strtol(currentToken.c_str(), &end, 10));
		return number; 
	} 
};


// 对应语法 <command list> ::= <command>* end 
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
	}
};

// 对应语法：<program> ::= program <command list>
class ProgramNode:public Node
{ 
private:
	Node* commandListNode;

public:
	void parse(Context context) 
	{ 
		context.skipToken("program"); 
		commandListNode = new CommandListNode(); 
		commandListNode->parse(context);
	} 
	
	string toString() 
	{ 
		return "[ program " + commandListNode + ']';
	} 
};

class RepeatCommandNode:public Node 
{ 
private:
	int number; 
	Node* commandListNode; 
public :
	void parse(Context context)
	{
		context.skipToken("repeat"); 
		number = context.currentNumber(); 
		context.nextToken();
		commandListNode = new CommandListNode(); 
		commandListNode->parse(context); 
	}

    string toString() 
	{ 
		return "[repeat " + number + " " + commandListNode + "]";
	}
};


class CommandNode:public Node 
{ 
private:
		Node* node;
public:
		void parse(Context context)
		{ 
			if (context.CurrentToken()=="repeat")
			{ 
				node = new RepeatCommandNode(); 
				node->parse(context); 
			} 
			else 
			{ 
				node = new PrimitiveCommandNode(); 
				node->parse(context);
			} 
		} 
		string toString() 
		{ 
			return node->toString();
		} 
};


class PrimitiveCommandNode:public Node
{
private:
	string name;
public:
	void parse(Context context) 
	{ 
		name = context.CurrentToken(); 
		context.skipToken(name); 
		if (!(name=="go") && !(name=="right") && !(name=="left")) 
		{ 
			cerr<<"there is no such expression"
		} 
	} 
	string toString() 
	{ 
		return name; 
	}
};

int main()
{
	try {
		BufferedReader reader = new BufferedReader(new FileReader("file/interpreter/program.txt"));
		String text;
		while ((text = reader.readLine()) != null)
		{
			System.out.println("text = \"" + text + "\"");
			Node node = new ProgramNode();
			node.parse(new Context(text));
			System.out.println("node = " + node);
		}
		reader.close();
	}
	catch (Exception e)
	{
		e.printStackTrace();
	}
}