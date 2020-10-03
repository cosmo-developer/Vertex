#include "InstructionExpression.h"
InstructionExpression::InstructionExpression(VertexObject t, TT tt) {
	this->vo = t;
	this->type = tt;
}
InstructionExpression::InstructionExpression(double val, TT t) {
	this->dval = val;
	this->type = t;
}
