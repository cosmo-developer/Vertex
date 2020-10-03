#ifndef ERRORHANDLER_H
#define ERRORHANDLER_H
#include "defined.h"
#include "Token.h"
#include <vector>
class ErrorHandler
{
	std::vector<const char*> errors;
	public:
		void addError(ET errortype,PE haseerror,Token* t);
		void throwHazardas(const char* msg);
		void undefinedIdentifier(Token* t);
		void redeclared(Token* previous,Token* now);
		void throwError();
		void eofException(Token* at);
	protected:
};

#endif
