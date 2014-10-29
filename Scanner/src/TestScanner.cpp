#include "Scanner.h"
#include <stdio.h>

int main(int argc, char **argv) {

	Scanner* scanner;


	scanner = new Scanner();
	Token* t = new Token();
	scanner->nextToken(t);

}

