#include <iostream>
#include "context.h"
#include "TerminalExpression.h"
#include "NonterminalExpression.h"

using namespace std;

int main()
{
	cout << "Interpreter test" << endl;
	Context * context = new Context();
	AbstractExpression* t = new TerminalExpression();
	AbstractExpression* n = new NonterminalExpression();
	t->interpret(context);
	n->interpret(context);
	system("pause");
}