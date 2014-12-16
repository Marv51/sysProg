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
			|| t->getTokenType() == State::SchraegstrichSternSternSchraegstrich) {
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
		if (lastFinal == State::Start) {
			lastFinal = State::Fehler;
		}
		t->setTokenType(lastFinal);
		int stepBack = automat->getStepsSinceLastFinalState();
		if (lastFinal == State::Fehler) {
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
	InfoTyp type = InfoTyp::Unknown;
	// TODO Bug bei dem der type 2 oder 1 wird obwohl es ein Identifier ist fixen
	State toktype = t->getTokenType();
	if (toktype == State::Number) {
		type = InfoTyp::Integer;
	} else if (toktype == State::Identifier) {
		type = InfoTyp::Identifier;
	} else if ((int)toktype >= 4 && (int)toktype <= 23) { // Sign
		type = InfoTyp::Sign;
	} else if (toktype == State::Fehler) {
		type = InfoTyp::Fehler;
	}
	uint16_t key = symtable->newInfo(t->getContent(), type);
	if (symtable->getInfo(key)->getValue() == -1) {
		symtable->getInfo(key)->setType(InfoTyp::Fehler);
	}
	t->setKey(key);
}
