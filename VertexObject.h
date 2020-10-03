#pragma once
#include "Token.h"
#include <string>
//VertexObject is a complex object contain their active state and value and opertion type
class VertexObject
{
public:
	double contain=0.0f;//value input or calculated value
	bool active=false;//state that tells do with input operation
	std::string op;//Type of operation
	std::string name;
	VertexObject();
};

