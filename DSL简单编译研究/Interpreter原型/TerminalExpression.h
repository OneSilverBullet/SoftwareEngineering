#pragma once
#include "context.h"
#include "AbstractExpression.h"

using namespace std;

class TerminalExpression :public AbstractExpression
{
public:
	TerminalExpression();
	void interpret(Context* context);
};