#include "Lexer.h"
#include "Token.h"
#include <vector>
#include "InstanceManager.h"
#include <fstream>
#include <iostream>
#include "Interpretor.h"
#include <string>
using namespace std;
int main(int argc, char** argv) {
	std::string filename = "sample.txt";
	if (argc > 1)filename = argv[1];
	std::ifstream infile(filename);
	if (!infile.is_open()) {
		std::cout << "Error file not found:"<<argv[1] << std::endl;
		exit(-1);
	}
	std::string temp;
	std::string buffer("");
	while (getline(infile, temp)) {
		buffer.append(temp);
		buffer.append("\n");
	}
	infile.close();
	Lexer* lexer = new Lexer(buffer.c_str());
	InstanceManager::handler->throwError();
	std::vector<Token*> tokens = lexer->_tokens();
	Interpretor* interpretor = new Interpretor(tokens);
	interpretor->interpret();
	delete lexer;
	delete interpretor;
	return 0;
}