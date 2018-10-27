#pragma once
#include "Content.h"

class Node {
public:
	virtual void parse(Context context) = 0;
	virtual string toString()  =0;
};