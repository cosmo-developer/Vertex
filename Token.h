#ifndef TOKEN_H
#define TOKEN_H
#include <iostream>
enum class TT{
	INPUT_VAR,
	IDENTIFIER,
	NUMBER,
	VERTEX,
	PLUS,
	MINUS,
	DIVIDE,
	TIMES,
	EQUAL,
	COMMA,
	SEMI_COLON,
	DASH,
	RIGHT_ANGULAR_BRACKET,
	WRITE,
	EOFS,
	DUMMY,
	RPAREN,
	LPAREN,
	OPTYPE,
};
class Token
{
	public:
		Token(const char value,TT type,int line,int column);
		Token(std::string value, TT type, int line, int column);
		~Token();
		std::string val() { return this->value; }
		int l(){return this->line;}
		int c(){return this->column;}
		TT t(){return this->type;}
	protected:
		std::string value;
		int line;
		int column;
		TT type;
};

#endif
