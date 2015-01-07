/*
 * ParseTree.h
 *
 *  Created on: Dec 17, 2014
 *      Author: marius
 */

#include "Node.h"

#ifndef PARSER_SRC_PARSETREE_H_
#define PARSER_SRC_PARSETREE_H_

class ParseTree {
public:
	ParseTree(Scanner* scanner);
	virtual ~ParseTree();
	void parse();
private:
	Scanner* scanner;
	Node* root;
};

#endif /* PARSER_SRC_PARSETREE_H_ */
