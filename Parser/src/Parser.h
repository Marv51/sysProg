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
#include "Node.h"
#include <iostream>
#include <fstream>
using namespace std;

#ifndef PARSER_SRC_PARSER_H_
#define PARSER_SRC_PARSER_H_

class Parser {
public:
	Parser(Scanner* s, char* output);
	virtual ~Parser();
	Node* parse();
	Node* match(InfoTyp typ);
	Node* match(State typ);
	void nextToken();
	void error();
	Node* parseProg();
	Node* parseDecls();
	Node* parseDecl();
	Node* parseArray();
	Node* parseStatements();
	Node* parseStatement();
	Node* parseExp();
	Node* parseExp2();
	Node* parseIndex();
	Node* parseOpExp();
	Node* parseOp();
	Node* createNode(NodeType ntype);
	void typeCheck(Node* node);
	void makeCode(Node* node);
	void errorTypeCheck(const char* message, Token* token);
private:
	Scanner* scanner;
	Token* token;
	ofstream code;
	uint16_t labelcounter;
};

#endif /* PARSER_SRC_PARSER_H_ */
