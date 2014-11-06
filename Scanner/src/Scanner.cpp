/*
 * Scanner.cpp
 *
 *  Created on: Sep 26, 2012
 *      Author: knad0001
 */

#include "Scanner.h"
#include <stdio.h>

Scanner::Scanner() {
	buffer = new Buffer();
	automat = new Automat();
}

Scanner::~Scanner() {
	delete buffer;
	delete automat;
}

bool Scanner::ignoreChar(char ch){
	return !(ch != ' ' && ch != '\n' && ch != '\t');
}

bool Scanner::nextToken(Token* t) {
	bool cont;
	char ch;
	while (t->content->isEmpty() ||  t->getTokenType() == SchraegstrichSternSternSchraegstrich) {
		automat->clean();
		t->content->clear();
		do {
			ch = buffer->getChar();
			if (!ignoreChar(ch)) {
				t->content->push(ch);
			}
			cont = automat->testChar(ch);
		} while (cont);

		State lastFinal = automat->getLastFinalState();
		if (lastFinal == Start){
			lastFinal = Fehler;
		}
		t->setTokenType((State)(int)lastFinal);
		if (lastFinal != Fehler && lastFinal){
			for (int j = automat->getStepsSinceLastFinalState(); j > 0; j--) {
				if (!ignoreChar(ch)) {
					automat->SpalteZurueck();
					buffer->ungetChar();
				}
				t->content->pop();

			}
		}
	}
	t->setSpalte(automat->getSpalte());
	t->setZeile(automat->getZeile());
	return buffer->hasCharLeft();
}
