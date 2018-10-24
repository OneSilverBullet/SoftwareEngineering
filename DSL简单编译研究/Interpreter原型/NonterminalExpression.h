#pragma once

#include "AbstractExpression.h"
#include "context.h"
using namespace std;

class NonterminalExpression :public AbstractExpression
{
public:
	NonterminalExpression();
	void interpret(Context* context);
};