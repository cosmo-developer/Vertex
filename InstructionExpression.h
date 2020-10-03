#pragma once
#include "Token.h"
#include "VertexObject.h"
class InstructionExpression
{
public:
	VertexObject vo;
	double dval;
	TT type;
	InstructionExpression* next=NULL;
public:
	InstructionExpression(VertexObject, TT);
	InstructionExpression(double,TT);
};

