#pragma once
#include "context.h"

class AbstractExpression
{
public:
	AbstractExpression();
	void virtual interpret(Context* context) = 0;
};