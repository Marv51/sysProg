/*
 * Node.cpp
 *
 *  Created on: Dec 2, 2015
 *      Author: marvin
 */

#include "Node.h"

Node::Node(NodeType type) :
		infoKey(0), subnodes_count(0), infoLexem() {
	this->type = type;
}

Node::~Node() {
}

void Node::addNode(Node* node) {
	subnodes[subnodes_count] = node;
	subnodes_count++;
}

void Node::setKey(uint16_t key, char* lexem) {
	infoKey = key;
	infoLexem = lexem;
}

void Node::print(uint16_t level) {
	for (int i = 0; i < level; i++) {
		printf("-");
	}
	printf("%i", type);
	if (infoKey != 0) {
		printf("\t %s", infoLexem);
	}
	printf("\n");
	for (int i = 0; i < subnodes_count; i++) {
		subnodes[i]->print(level + 1);
	}
}
