#ifndef LEXER_H
#define LEXER_H
#include "Token.h"
#include <vector>
class Lexer
{
	
	public:
		Lexer(const char* program);
		~Lexer();
		std::vector<Token*> _tokens(){return this->tokens;}
	protected:
		void initStart(char* program);
		std::vector<Token*> tokens;
		int line;
		int col;
};

#endif
