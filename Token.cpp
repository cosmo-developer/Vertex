#include "Token.h"
#include <string.h>
#include <stdlib.h>
#include <iostream>
Token::Token(const char value,TT type,int line,int column)
{
	this->line=line;
	this->column=column;
	this->value += value;
	this->type=type;
}
Token::Token(std::string value, TT type, int line, int column) {
	this->value = value;
	this->type = type;
	this->line = line;
	this->column = column;
}

Token::~Token()
{
   this->value.clear();
}
