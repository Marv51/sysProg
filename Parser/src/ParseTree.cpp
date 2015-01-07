/*
 * ParseTree.cpp
 *
 *  Created on: Dec 17, 2014
 *      Author: marius
 */

#include "ParseTree.h"

ParseTree::ParseTree(Scanner* scan) {
	scanner = scan;
	root = new Node(Nodetypes::PROG, scanner);
}

ParseTree::~ParseTree() {
}

void ParseTree::parse() {
	Token* t = new Token();
	scanner->nextToken(t);
	root->insert(t);
}
