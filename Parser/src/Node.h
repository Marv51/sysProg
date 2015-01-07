/*
 * Parser.h
 *
 *  Created on: Dec 17, 2014
 *      Author: marvin
 */
#include "../../Scanner/src/Token.h"
#include "../../Scanner/src/Scanner.h"
#include "../../Symboltable/src/Information.h"

#ifndef PARSER_SRC_PARSER_H_
#define PARSER_SRC_PARSER_H_

enum class Nodetypes{
	PROG,
	DECLS,
	DECL,
	ARRAY,
	STATEMENTS,
	STATEMENT,
	EXP,
	EXP2,
	INDEX,
	OP_EXP,
	OP
};

class Node {
public:
	Node(Nodetypes ntype, Scanner* scan);
	virtual ~Node();
	bool insert(Token* t);
private:
	Scanner* scanner;
	bool prog(Token* t);
	bool decls(Token* t);
	bool decl(Token* t);
	bool array(Token* t);
	bool statements(Token* t);
	bool statement(Token* t);
	bool exp(Token* t);
	bool exp2(Token* t);
	bool index(Token* t);
	bool op_exp(Token* t);
	bool op(Token* t);
	Nodetypes nodetype;
	Node* node1;
	Node* node2;
	Node* node3;
	Token* leaf1;
	Token* leaf2;
	Token* leaf3;
	Token* leaf4;
};

#endif /* PARSER_SRC_PARSER_H_ */
