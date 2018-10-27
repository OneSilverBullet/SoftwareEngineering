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
		if (token != currentToken)
		{
			cerr << "warning: the token is  different from the current token!!" << endl;
		}
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
int Context::index = 0;
string Context::currentToken;