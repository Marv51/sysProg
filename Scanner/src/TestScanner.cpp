#include "Scanner.h"
#include <stdio.h>
#include <fstream>

int main(int argc, char **argv) {
	printf("TestScanner:\n");
	char* input;
	char* output;
	if (argc == 3) {
		input = argv[1];
		output = argv[2];
	} else {
		printf("Bitte Dateipfad als Argument übertragen.");
	}
	//printf("%s", input);
	Scanner* scanner;

	bool moreTokens;

	scanner = new Scanner(input);
	Token* t = new Token();
	std::fstream fs;
	fs.open(output, std::fstream::out | std::fstream::trunc);
	do {
		delete t;
		t = new Token();
		moreTokens = scanner->nextToken(t);
		if (t->getTokenType() == 2) { // Integer
			fs << "Token " << t->getTokenTypeString() << " \t Line: "
					<< t->getZeile() << "\tColumn: " << t->getSpalte()
					<< "\tValue: "
					<< scanner->getSymboltable()->getInfo(t->getKey())->getValue()
					<< "\n";
		} else if (t->getTokenType() == 3) { // Identifier
			fs << "Token " << t->getTokenTypeString() << " Line: "
					<< t->getZeile() << "\tColumn: " << t->getSpalte()
					<< "\tLexem: " << t->content->getString() << "\n";
		} else if (t->getTokenType() == Fehler) {
			printf("Unknown Token: Line: %i\tColumn: %i\tSymbol: %s\n",
					t->getZeile(), t->getSpalte(), t->content->getString());
		} else {
			fs << "Token " << t->getTokenTypeString() << " \t\t Line: "
					<< t->getZeile() << "\tColumn: " << t->getSpalte() << "\n";
		}
	} while (moreTokens);

	fs.close();

	// TODO evtl Ausgabe in Datei schreiben
	printf("Ende\n");

}

