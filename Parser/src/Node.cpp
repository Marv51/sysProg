/*
 * Node.cpp
 *
 *  Created on: Dec 2, 2015
 *      Author: marvin
 */

#include "Node.h"

Node::Node(NodeType type) :
		infoKey(0), subnodes_count(0), infoLexem(), token() {
	this->type = type;
	this->checkType = CheckType::emptyType;
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
	printf(" - CheckType: %i\n", checkType);
	for (int i = 0; i < subnodes_count; i++) {
		subnodes[i]->print(level + 1);
	}
}

NodeType Node::getType() {
	return this->type;
}

Node* Node::getNode(uint16_t index) {
	return subnodes[index];
}

CheckType Node::getCheckType() const {
	return checkType;
}

void Node::setCheckType(CheckType checkType) {
	this->checkType = checkType;
}

uint16_t Node::getSubnodesCount() const {
	return subnodes_count;
}

uint16_t Node::getKey() const {
	return infoKey;
}

Token* Node::getToken() {
	return token;
}

void Node::setToken(Token* token) {
	this->token = token;
}
