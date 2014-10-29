#include "Scanner.h"
#include <stdio.h>

int main(int argc, char **argv) {
	printf("TestScanner:\n");
	Scanner* scanner;


	scanner = new Scanner();
	Token* t = new Token();
	for (int i = 0; i < 20;i++){
		delete t;
		t = new Token();
		scanner->nextToken(t);
		printf("Typ: %i\t", t->getTokenType());
		printf("Zeile: %i\t ", t->getZeile());
		printf("Spalte: %i\t", t->getSpalte());
		printf("Inhalt: %s\n", t->content);
	}

	printf("Ende\n");

}

