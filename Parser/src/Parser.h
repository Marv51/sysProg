/*
 * Parser.h
 *
 *  Created on: Nov 18, 2015
 *      Author: marius
 */

#include "../../Scanner/src/Scanner.h"
#include "../../Scanner/src/Token.h"
#include "../../Symboltable/src/Information.h"
#include <stdio.h>

#ifndef PARSER_SRC_PARSER_H_
#define PARSER_SRC_PARSER_H_

enum class NodeType {
	PROG,
	DECLS,
	DECL,
	ARRAY,
	STATEMENT,
	STATEMENTS,
	EXP,
	EXP2,
	INDEX,
	OP_EXP,
	OP
};

class Parser {
public:
	Parser(Scanner* s);
	virtual ~Parser();
	void parse();
	void match(InfoTyp typ);
	void match(State typ);
	void nextToken();
	void error();
	void parseProg();
	void parseDecls();
	void parseDecl();
	void parseArray();
	void parseStatements();
	void parseStatement();
	void parseExp();
	void parseExp2();
	void parseIndex();
	void parseOpExp();
	void parseOp();
	private:
	Scanner* scanner;
	Token* token;
};

#endif /* PARSER_SRC_PARSER_H_ */