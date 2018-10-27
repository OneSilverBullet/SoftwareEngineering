#pragma once
#include <vector>
#include <string>
#include <iostream>
#include <sstream>
using namespace std;

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
	static string currentToken;
	vector<string> commandList;
	static int index;
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
		if (token != currentToken)
		{
			cerr << "warning: the token is  different from the current token!!" << endl;
		}
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
int Context::index = 0;
string Context::currentToken;