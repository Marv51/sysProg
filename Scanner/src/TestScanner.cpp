#include "Scanner.h"
#include <stdio.h>
#include <fstream>
#include <string.h>

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
		if (t->getTokenType() == State::Fehler	|| scanner->getInfo(t->getKey())->getType() == InfoTyp::Fehler) {
			printf("Unknown Token: Line: %i\tColumn: %i\tSymbol: %s\n",
					t->getZeile(), t->getSpalte(), t->content->getString());
		} else if (t->getTokenType() == State::Identifier) { // Identifier
			const char* ident[] = { "1Unk\t", "2Sig\t", "3Num\t", "Identifier", "If\t\t",
					"While\t\t", "Else\t\t", "Int\t\t", "Write\t\t", "Read\t\t" };

			fs << "Token "
					<< ident[(int)scanner->getInfo(t->getKey())->getType()]
					<< " Line: " << t->getZeile() << "\tColumn: "
					<< t->getSpalte() << "\tLexem: " << t->content->getString()
					<< "\n";
		} else if (t->getTokenType() == State::Number) { // Integer
			fs << "Token " << t->getTokenTypeString() << " \t Line: "
					<< t->getZeile() << "\tColumn: " << t->getSpalte()
					<< "\tValue: "
					<< scanner->getInfo(t->getKey())->getValue()
					<< "\n";
		} else {
			fs << "Token " << t->getTokenTypeString() << " \t\t Line: "
					<< t->getZeile() << "\tColumn: " << t->getSpalte() << "\n";
		}
	} while (moreTokens);

	fs.close();
	printf("stop\n");

}

