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
		//��ʼ����ʱ��ͽ�ֵ����ʼ����
		commandList = ReadCommand(text);
		nextToken(); 
	} // ��ȡ��һ����� 

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

	// ���ʵ�ǰ��� 
	string CurrentToken() 
	{ 
		return currentToken; 
	} 

	//�ȼ�鵱ǰ��ǣ�Ȼ���ȡ��һ����� 
    string skipToken(string token)
	{ 
		return nextToken(); 
	}

	//��ȡ��ǰ��Ƕ�Ӧ����ֵ 
	int currentNumber() {
		int number = 0; 
		char* end;
		//��stringת��Ϊint
		number = static_cast<int>(strtol(currentToken.c_str(), &end, 10));
		return number; 
	} 
};


// ��Ӧ�﷨ <command list> ::= <command>* end 
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

// ��Ӧ�﷨��<program> ::= program <command list>
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