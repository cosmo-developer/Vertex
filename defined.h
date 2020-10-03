#ifndef DEFINED_H
#define DEFINED_H
enum ET{ //Error type
	SYNTAX_ERROR=0xff,
	ILLEGAL_NUMBER=0xfe,
	ILLEGAL_CHAR=0xfd,
	EXCEPTED_CURLY=0xfc,//if forget to close curly braces}
	EXCEPTED_PAREN=0xfb,//if forget to close paren),
	EXCEPTED_SEMICOLON=0xfa,//if forget to write semicolon
};
enum PE{//From which phase error come from Lexer or Parser
	LEXICAL_ERROR=1,
	PARSER_ERROR=2,
};

#endif
