#include "Scanner.h"
#include <stdio.h>
#include <fstream>

int main(int argc, char **argv) {
	char* input;
	char* output;
	if (argc == 3) {
		input = argv[1];
		output = argv[2];
	} else {
		printf("Bitte Dateipfad als Argument übertragen.");
	}
	Scanner* scanner;

	bool moreTokens;

	scanner = new Scanner(input);
	Token* t = new Token();
	std::fstream fs;
	fs.open(output, std::fstream::out | std::fstream::trunc);
	printf("Processing ...\n");
	do {
		delete t;
		t = new Token();
		moreTokens = scanner->nextToken(t);
		if (t->getTokenType() == Fehler
				|| scanner->getSymboltable()->getInfo(t->getKey())->getType()
						== 6) {
			printf("Unknown Token: Line: %i\tColumn: %i\tSymbol: %s\n",
					t->getZeile(), t->getSpalte(), t->content->getString());
		} else if (t->getTokenType() == Identifier) { // Identifier
			char* ident[] = { "", "", "", "Identifier", "If\t\t", "While\t\t" };
			fs << "Token "
					<< ident[scanner->getSymboltable()->getInfo(t->getKey())->getType()]
					<< " Line: " << t->getZeile() << "\tColumn: "
					<< t->getSpalte() << "\tLexem: " << t->content->getString()
					<< "\n";
		} else if (t->getTokenType() == Number) { // Integer
			fs << "Token " << t->getTokenTypeString() << " \t Line: "
					<< t->getZeile() << "\tColumn: " << t->getSpalte()
					<< "\tValue: "
					<< scanner->getSymboltable()->getInfo(t->getKey())->getValue()
					<< "\n";
		} else {
			fs << "Token " << t->getTokenTypeString() << " \t\t Line: "
					<< t->getZeile() << "\tColumn: " << t->getSpalte() << "\n";
		}
	} while (moreTokens);

	fs.close();
	printf("stop\n");

}

