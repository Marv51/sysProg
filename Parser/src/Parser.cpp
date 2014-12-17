/*
 * Parser.cpp
 *
 *  Created on: Dec 17, 2014
 *      Author: marvin
 */

#include "Parser.h"

Parser::Parser(char* input) {
	scanner = new Scanner(input);
	tree = new ParseTree();
}

Parser::~Parser() {
delete(scanner);
}

ParseTree* Parser::parse(){
	Token* t = new Token();
	while(scanner->nextToken(t)){
		t = new Token();
	}

return tree;
}
