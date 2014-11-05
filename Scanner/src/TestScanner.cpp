#include "Scanner.h"
#include <stdio.h>

int main(int argc, char **argv) {
	printf("TestScanner:\n");
	Scanner* scanner;

	bool moreTokens;

	scanner = new Scanner();
	Token* t = new Token();
	do {
		delete t;
		t = new Token();
		moreTokens = scanner->nextToken(t);
		printf("Typ: %i\t", t->getTokenType());
		printf("Zeile: %i\t ", t->getZeile());
		printf("Spalte: %i\t", t->getSpalte());
		printf("Inhalt: %s\n", t->content->getString());
	} while (moreTokens);

	printf("Ende\n");

}

