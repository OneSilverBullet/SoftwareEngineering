#include <iostream>
#include <string>
#include <list>
#include <vector>
#include <sstream>
using namespace std;

#include "ProgramNode.h"
#include "Content.h"


int main()
{
	string inputStr;
	getline(cin, inputStr); //����õ�һ���ַ�����
	Context context(inputStr);
	Node* node = new ProgramNode();
	node->parse(context);
	cout << node->toString() << endl;
	system("pause");
}