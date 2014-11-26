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
		t->setTokenType((int)lastFinal);
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
	makeInfo(t);
	return buffer->hasCharLeft();
}

Symboltable* Scanner::getSymboltable(){
	return symtable;
}

void Scanner::makeInfo(Token* t){
	uint8_t type = 0;
	int toktype = t->getTokenType();
	if (toktype == Number){
		type = 2;
	}else if (toktype == Identifier){
		type = 3;
	}else if(toktype >= 4 && toktype <= 23){ // Sign
		type = 1;
	}else if(toktype == Fehler){
		type = 7;
	}
	uint16_t key = symtable->newInfo(t->getContent(), type);
	t->setKey(key);
}
