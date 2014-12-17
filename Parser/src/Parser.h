/*
 * Parser.h
 *
 *  Created on: Dec 17, 2014
 *      Author: marvin
 */

#ifndef PARSER_SRC_PARSER_H_
#define PARSER_SRC_PARSER_H_

#include "../../Scanner/src/Token.h"
#include "../../Scanner/src/Scanner.h"
#include "ParseTree.h"

class Parser {
public:
	Parser(char* input);
	virtual ~Parser();
	ParseTree* parse();
private:
	Scanner* scanner;
	ParseTree* tree;

};

#endif /* PARSER_SRC_PARSER_H_ */
