/*
 * Parser.cpp
 *
 *  Created on: Dec 17, 2014
 *      Author: marvin
 */

#include "Node.h"

Node::Node(Nodetypes ntype, Scanner* scan) {
	node1 = nullptr;
	node2 = nullptr;
	node3 = nullptr;
	leaf1 = nullptr;
	leaf2 = nullptr;
	leaf3 = nullptr;
	leaf4 = nullptr;
	nodetype = ntype;
	scanner = scan;
}

Node::~Node() {
}

bool Node::insert(Token* t) {
	if (nodetype == Nodetypes::PROG) {
		return prog(t);
	} else if (nodetype == Nodetypes::DECLS) {
		return decls(t);
	} else if (nodetype == Nodetypes::DECL) {
		return decl(t);
	} else if (nodetype == Nodetypes::ARRAY) {
		return array(t);
	} else if (nodetype == Nodetypes::STATEMENTS){
		return statements(t);
	}
}

bool Node::prog(Token* t) {
	node1 = new Node(Nodetypes::DECLS, scanner);
	node2 = new Node(Nodetypes::STATEMENTS, scanner);
	if (node1->insert(t)) {
		return true;
	} else {
		return node2->insert(t);
	}
}

bool Node::decls(Token* t) {
	if (scanner->getInfo(t->getKey())->getType() == InfoTyp::inttyp
			|| t->getTokenType() == State::EckigeKlammerAuf
			|| t->getTokenType() == State::EckigeKlammerZu
			|| t->getTokenType() == State::Number
			|| scanner->getInfo(t->getKey())->getType()
					== InfoTyp::Identifier) {
		node1 = new Node(Nodetypes::DECL, scanner);
		node2 = new Node(Nodetypes::DECLS, scanner);
		return node1->insert(t);
	} else if (t->getTokenType() == State::Semikolon) {
		leaf1 = t;
		return true;
	} else {
		return false;
	}
}

bool Node::decl(Token* t) {
	if (scanner->getInfo(t->getKey())->getType() == InfoTyp::inttyp) {
		leaf1 = t;
		node1 = new Node(Nodetypes::ARRAY, scanner);
		return true;
	} else if (scanner->getInfo(t->getKey())->getType()
			== InfoTyp::Identifier) {
		leaf2 = t;
		return true;
	} else if (t->getTokenType() == State::EckigeKlammerAuf
			|| t->getTokenType() == State::EckigeKlammerZu
			|| t->getTokenType() == State::Number) {
		return node1->insert(t);
	} else {
		return false;
	}
}

bool Node::array(Token* t) {
	if (t->getTokenType() == State::EckigeKlammerAuf) {
		leaf1 = t;
		return true;
	} else if (t->getTokenType() == State::Number) {
		leaf2 = t;
		return true;
	} else if (t->getTokenType() == State::EckigeKlammerZu) {
		leaf3 = t;
		return true;
	} else {
		return false;
	}
}

bool Node::statements(Token* t){
	return true;
}
