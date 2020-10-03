#include "ErrorHandler.h"
#include <stdio.h>
#include <stdlib.h>
void ErrorHandler::addError(ET et,PE pe,Token* t){
	char* err=new char[100];
	switch(pe){
		case LEXICAL_ERROR:{
			switch(et){
				case ILLEGAL_NUMBER:
#ifdef _MSC_VER
					sprintf_s(err,100,"Illegal Number:{'%s',at line:%d, of col:%d}\n",t->val().c_str(),t->l(),t->c());
#else
					sprintf(err, "Illegal Number:{'%s',at line:%d, of col:%d}\n", t->val().c_str(), t->l(), t->c());
#endif
					errors.push_back(err);
					break;
				case ILLEGAL_CHAR:
#ifdef _MSC_VER
					sprintf_s(err,100,"Illegal Char at:{'%s' at line:%d, of col:%d}\n",t->val().c_str(),t->l(),t->c());
#else
					sprintf(err, "Illegal Char at:{'%s' at line:%d, of col:%d}\n", t->val().c_str(), t->l(), t->c());
#endif
					errors.push_back(err);
					break;
			}
			break;
		}
		case PARSER_ERROR:{
			switch(et){
				case SYNTAX_ERROR:
#ifdef _MSC_VER
					sprintf_s(err,100,"Syntax Error '%s' line:%d col:%d\n",t->val().c_str(),t->l(),t->c());
#else
					sprintf(err,"Syntax Error '%s' line:%d col:%d\n", t->val().c_str(), t->l(), t->c());
#endif
					errors.push_back(err);
					break;
				case EXCEPTED_CURLY:
#ifdef _MSC_VER
					sprintf_s(err,100,"Expected } after '%s' at line:%d on column:%d\n",t->val().c_str(),t->l(),t->c());
#else
					sprintf(err, "Expected } after '%s' at line:%d on column:%d\n", t->val().c_str(), t->l(), t->c());
#endif
					errors.push_back(err);
					break;
				case EXCEPTED_PAREN:
#ifdef _MSC_VER
					sprintf_s(err,100,"Expected ) after '%s' at line:%d on column:%d\n",t->val().c_str(),t->l(),t->c());
#else
					sprintf(err, "Expected ) after '%s' at line:%d on column:%d\n", t->val().c_str(), t->l(), t->c());
#endif
					errors.push_back(err);
					break;
				case EXCEPTED_SEMICOLON:
#ifdef _MSC_VER
					sprintf_s(err,100,"Expected ; after '%s' at line:%d on column:%d\n",t->val().c_str(),t->l(),t->c());
#else
					sprintf(err, "Expected ; after '%s' at line:%d on column:%d\n", t->val().c_str(), t->l(), t->c());
#endif
					errors.push_back(err);
					break;
			}
			break;
		}
	}
//	delete err;
}
void ErrorHandler::undefinedIdentifier(Token* t){
	char* err=new char[100];
#ifdef _MSC_VER
	sprintf_s(err,100,"Undefined identifier '%s' at line:%d on column:%d\n",t->val().c_str(),t->l(),t->c());
#else
	sprintf(err, "Undefined identifier '%s' at line:%d on column:%d\n", t->val().c_str(), t->l(), t->c());
#endif
	errors.push_back(err);
	this->throwError();
}
void ErrorHandler::redeclared(Token* previous,Token* now){
	char* err=new char[100];
#ifdef _MSC_VER
	sprintf_s(err,100,"Redeclare ['%s',line:%d,col:%d] Previousely Declared at:['%s',line:%d,col:%d]\n",
	  now->val().c_str(),
	  now->l(),
	  now->c(),
	  previous->val().c_str(),
	  previous->l(),
	  previous->c()
	);
#else
	sprintf(err, "Redeclare ['%s',line:%d,col:%d] Previousely Declared at:['%s',line:%d,col:%d]\n",
		now->val().c_str(),
		now->l(),
		now->c(),
		previous->val().c_str(),
		previous->l(),
		previous->c()
	);
#endif
	errors.push_back(err);
	this->throwError();
}
void ErrorHandler::throwError(){
	if (!this->errors.empty()){
		for (int i=0;i<this->errors.size();i++){
			printf("%d: Error:%s",i+1,this->errors[i]);
		}
	    printf("Error in Parsing and exited with return code:-1");
//	    errors.clear();
		exit(-1);
	}
}
void ErrorHandler::throwHazardas(const char* msg){
	errors.push_back(msg);
	this->throwError();
}
void ErrorHandler::eofException(Token* t) {
	char* err = new char[100];
#ifdef _MSC_VER
	sprintf_s(err, 100, "EOF Exception at: '%s' at line:%d on column:%d\n",t->val().c_str(), t->l(), t->c());
#else
	sprintf(err, "EOF Exception at: '%s' at line:%d on column:%d\n", t->val().c_str(), t->l(), t->c());
#endif
	errors.push_back(err);
	this->throwError();
}
