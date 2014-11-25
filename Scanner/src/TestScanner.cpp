#include "Scanner.h"
#include <stdio.h>



int main(int argc, char **argv) {
	printf("TestScanner:\n");



	Scanner* scanner;

	bool moreTokens;

	scanner = new Scanner();
	Token* t = new Token();
	printf("Typ:\tZeile:\tSpalte:\tInhalt:       \t\tTypString:\n");
	do {
		delete t;
		t = new Token();
		moreTokens = scanner->nextToken(t);
		printf("%i\t", t->getTokenType());
		printf("%i\t", t->getZeile());
		printf("%i\t", t->getSpalte());
		printf("%s       \t\t", t->content->getString());
		printf("%s\n", t->getTokenTypeString());
	} while (moreTokens);

	// TODO evtl Ausgabe in Datei schreiben
	printf("Ende\n");

}

