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

enum class CheckType {
	emptyType,
	intType,
	intArrayType,
	arrayType,
	noType,
	errorType,
	opPlus,
	opMinus,
	opMult,
	opDiv,
	opLess,
	opGreater,
	opEqual,
	opUnequal,
	opAnd
};

class Node {
public:
	Node(NodeType type);
	virtual ~Node();
	void addNode(Node* node);
	void setKey(uint16_t, char* lexem);
	void print(uint16_t level);
	NodeType getType();
	Node* getNode(uint16_t index);
	CheckType getCheckType() const;
	void setCheckType(CheckType checkType);
	uint16_t getSubnodesCount() const;
	uint16_t getKey() const;

private:
	NodeType type;
	uint16_t infoKey;
	uint16_t subnodes_count;
	Node* subnodes[7];
	char* infoLexem;
	CheckType checkType;
};

#endif /* PARSER_SRC_NODE_H_ */
