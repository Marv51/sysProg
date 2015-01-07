/*
 * ParserTest.cpp
 *
 *  Created on: Dec 17, 2014
 *      Author: marvin
 */
#include <stdio.h>
#include "../../Scanner/src/Scanner.h"
#include "ParseTree.h"

int main(int argc, char** argv){
	printf("test");
	Scanner* scanner = new Scanner("testfile.txt");
	ParseTree* tree = new ParseTree(scanner);
	tree->parse();

	return 0;
}
