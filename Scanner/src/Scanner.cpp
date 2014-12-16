/*
 * Scanner.cpp
 *
 *  Created on: Sep 26, 2012
 *      Author: knad0001
 */

#include "Scanner.h"
#include <stdio.h>

Scanner::Scanner(char* input) {
	buffer = new Buffer(input);
	automat = new Automat();
	symtable = new Symboltable();
}

Scanner::~Scanner() {
	delete buffer;
	delete automat;
	delete symtable;
}

bool Scanner::ignoreChar(char ch) {
	return !(ch != ' ' && ch != '\n' && ch != '\t');
}

bool Scanner::nextToken(Token* t) {
	bool cont;
	char ch;
	while (t->content->isEmpty()
			|| t->getTokenType() == SchraegstrichSternSternSchraegstrich) {
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
		if (lastFinal == Start) {
			lastFinal = Fehler;
		}
		t->setTokenType((int) lastFinal);
		int stepBack = automat->getStepsSinceLastFinalState();
		if (lastFinal == Fehler) {
			stepBack--;
		}
		for (int j = stepBack; j > 0; j--) {
			if (!ignoreChar(ch)) {
				automat->spalteZurueck();
				buffer->ungetChar();
			}
			t->content->pop();
		}
	}
	t->setSpalte(automat->getSpalte());
	t->setZeile(automat->getZeile());
	makeInfo(t);
	return buffer->hasCharLeft();
}

//TODO diese Methode sollten wir durch eine ernsthaft nützliche Funktion ersetzen, eventuell mal in der Anleitung schauen. (vlt. getInfoForToken, oder so?)
Symboltable* Scanner::getSymboltable() {
	return symtable;
}

void Scanner::makeInfo(Token* t) {
	uint8_t type = 0;
	// TODO Bug bei dem der type 2 oder 1 wird obwohl es ein Identifier ist fixen
	int toktype = t->getTokenType();
	if (toktype == Number) {
		type = 2;
	} else if (toktype == Identifier) {
		type = 3;
	} else if (toktype >= 4 && toktype <= 23) { // Sign
		type = 1;
	} else if (toktype == Fehler) {
		type = 6;
	}
	uint16_t key = symtable->newInfo(t->getContent(), type);
	if (symtable->getInfo(key)->getValue() == -1) {
		symtable->getInfo(key)->setType(6);
	}
	t->setKey(key);
}
