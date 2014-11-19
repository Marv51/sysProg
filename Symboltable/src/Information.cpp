/*
 * Information.cpp
 *
 *  Created on: Nov 6, 2014
 *      Author: marius
 */

#include "Information.h"

Information::Information(char* lex) {
	lexem = lex;
}

Information::~Information() {

}

bool Information::compareLexem(char* lex) {
	bool ret = true;
	int i = -1;
	do {
		i++;
		if (lexem[i] != lex[i]) {
			ret = false;
		}
	} while (lexem[i] != '\0' && lex[i] != '\0');
	return ret;
}

char* Information::getLexem() {
	return lexem;
}

void Information::setLexem(char* lex) {
	lexem = lex;
}
