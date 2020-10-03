#include "Lexer.h"
#include <string.h>
#include <string>
#include <stdlib.h>
#include <iostream>
#include "InstanceManager.h"
#include "defined.h"
Lexer::Lexer(const char* program)
{
	this->line=1;
	this->col=0;
	this->tokens.clear();
	this->initStart((char*)program);
}

Lexer::~Lexer()
{
	this->tokens.clear();
}
void Lexer::initStart(char* src){
	while (true){
		if (*src==' ' || *src == '\t' || *src=='\f' || *src == '\b' || *src == '\r'){
			this->col++;
			src++;
		}else if (*src == ' '){
			this->col++;
			src++;
		}else if(*src == '\n'){
			this->col=0;
			this->line++;
			src++;
		}else if(*src == '\0'){
			this->col++;
			this->tokens.push_back(new Token(' ',TT::EOFS,line,col));
			this->tokens.push_back(new Token(' ', TT::EOFS, line, col));
			break;
		}else if(*src == '/' && *(src+1) == '/'){
		    while (*src!='\n'){ 
			if (*src=='\0')break;
			src++;
			}
		}else if(*src == '-'){
			col++;
			this->tokens.push_back(new Token(*src, TT::DASH,line,col));
			src++;
		}else if(*src == ';'){
			col++;
			this->tokens.push_back(new Token(*src, TT::SEMI_COLON,line,col));
			src++;
		}else if(*src == ','){
			col++;
			this->tokens.push_back(new Token(*src, TT::COMMA,line,col));
			src++;
		}else if(*src == '='){
			col++;
			this->tokens.push_back(new Token(*src, TT::EQUAL,line,col));
			src++;
		}
		else if (*src == '(') {
			col++;
			this->tokens.push_back(new Token(*src, TT::LPAREN, line, col));
			src++;
		}
		else if (*src == ')') {
			col++;
			this->tokens.push_back(new Token(*src, TT::RPAREN, line, col));
			src++;
		}
		else if (*src == '>') {
			col++;
			this->tokens.push_back(new Token(*src, TT::RIGHT_ANGULAR_BRACKET, line, col));
			src++;
		}
		else{
			col++;
			if (*src == '.' || isdigit(*src)){
				int cur=col;
				std::string digit="";
				int ndot=0;
				while ((isdigit(*src)||*src=='.') && *src !=' '){
					if (*src=='.')ndot++;
					if (ndot>1){
						InstanceManager::handler->addError(ILLEGAL_NUMBER,LEXICAL_ERROR,new Token(*src, TT::DUMMY,line,col));
						InstanceManager::handler->throwError();
					}
					digit+=*src;
					src++;
					col++;
					if (!isdigit(*src) && (*src!='.'))break;
				}
				digit.append("");
				this->tokens.push_back(new Token(digit.c_str(), TT::NUMBER,line,cur));
			}else if(*src == '_' || isalpha(*src)){
				int c=col;
				std::string identifier("");
				while (isalpha(*src) || *src == '_' || isdigit(*src)){
					identifier+=*src;
					src++;
					if (!isdigit(*src) && *src!='_' && isalpha(*src)==false && *src != '\0')break;
					col++;
				}
				
				if (strcmp(identifier.c_str(),"input_var")==0){
					this->tokens.push_back(new Token("input_var", TT::INPUT_VAR, line, c));
				}
				else if (strcmp(identifier.c_str(), "vertex") == 0) {
					this->tokens.push_back(new Token("vertex",TT::VERTEX,line,c));
				}
				else if (strcmp(identifier.c_str(), "DIVIDE") == 0) {
					this->tokens.push_back(new Token("DIVIDE", TT::OPTYPE, line, c));
				}
				else if (strcmp(identifier.c_str(), "PLUS") == 0) {
					this->tokens.push_back(new Token("PLUS", TT::OPTYPE, line, c));
				}
				else if (strcmp(identifier.c_str(), "TIMES") == 0) {
					this->tokens.push_back(new Token("TIMES", TT::OPTYPE, line, c));
				}
				else if (strcmp(identifier.c_str(), "MINUS") == 0) {
					this->tokens.push_back(new Token("MINUS", TT::OPTYPE, line, c));
				}
				else if (strcmp(identifier.c_str(), "write") == 0) {
					this->tokens.push_back(new Token("write", TT::WRITE, line, c));
				}
				else{
				    this->tokens.push_back(new Token(identifier, TT::IDENTIFIER,line,c));
				}
				identifier.clear();
			}else{
				InstanceManager::handler->addError(ILLEGAL_CHAR,LEXICAL_ERROR,new Token(*src, TT::DUMMY,line,col));
				src++;
			}
		}
	}
}
