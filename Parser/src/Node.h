/*
 * Node.h
 *
 *  Created on: Dec 2, 2015
 *      Author: marvin
 */

#ifndef PARSER_SRC_NODE_H_
#define PARSER_SRC_NODE_H_

#include "Parser.h"

class Node {
public:
	Node(NodeType type);
	virtual ~Node();
private:
	NodeType type;
};

#endif /* PARSER_SRC_NODE_H_ */
