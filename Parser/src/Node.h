/*
 * Node.h
 *
 *  Created on: Dec 2, 2015
 *      Author: marvin
 */

#ifndef PARSER_SRC_NODE_H_
#define PARSER_SRC_NODE_H_

#include <stdint.h>
#include <stdio.h>

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
	OP,
	LEAF
};

class Node {
public:
	Node(NodeType type);
	virtual ~Node();
	void addNode(Node* node);
	void setKey(uint16_t, char* lexem);
	void print(uint16_t level);
private:
	NodeType type;
	uint16_t infoKey;
	uint16_t subnodes_count;
	Node* subnodes[7];
	char* infoLexem;
};

#endif /* PARSER_SRC_NODE_H_ */
