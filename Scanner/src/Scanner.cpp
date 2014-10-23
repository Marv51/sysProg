/*
 * Scanner.cpp
 *
 *  Created on: Sep 26, 2012
 *      Author: knad0001
 */

#include "Scanner.h"

Scanner::Scanner() {
	buffer = new Buffer();
	automat = new Automat();
}

Scanner::~Scanner() {
	delete buffer;
	delete automat;
}

void Scanner::nextToken() {
	bool cont;
	char ch;
	int i = 0; // nur nötig solange kein stack oä
	do {
		ch = buffer->getChar();
		word[i] = ch; // TODO durch stack.push() oä ersetzen?
		i++; // nur nötig solange kein Stack oä
		cont = automat->testChar(ch);
	} while (cont);

	for (int j = automat->getStepsSinceLastFinalState(); j > 0; j--) {
		buffer->ungetChar();
		word[i] = '\0'; // TODO durch stack.pop() oä ersetzen?
		i--;  // nur nötig solange kein stack oä
	}
	// TODO Token bauen aus lastFinalState und stack/liste und Zeile und Spalte
}
