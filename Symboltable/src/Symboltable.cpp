/*
 * Symboltable.cpp
 *
 *  Created on: Sep 26, 2012
 *      Author: knad0001
 */

#include "Symboltable.h"
#include <stdlib.h>
#include <string.h>

Symboltable::Symboltable() {
	memsize = 128;
	keysizemax = memsize;
	informations = (Information**) malloc(memsize * sizeof(Information*));
	memset(informations, '\0', memsize * sizeof(Information*));
	keys = (int*) malloc(memsize * sizeof(int));
	keysize = 0;
	initSymbols();
}

Symboltable::~Symboltable() {
	for (uint16_t i = 0; i < memsize; i++) {
		if (informations[i] != '\0') {
			delete (informations[i]);
		}
	}
	free(informations);
	free(keys);
}

uint16_t Symboltable::hash(char* ch) {
	uint16_t ergebnis = 0;
	uint16_t i = 0;
	while (ch[i] != '\0') {
		ergebnis += (uint16_t) ch[i];
		i++;
	}

	return ergebnis % memsize;
}

Information* Symboltable::getInfo(uint16_t key) {
	if (key >= keysize) { // Also ist key auf jeden Fall in der Symboltabelle
		return '\0';
	}
	uint16_t derHash = keys[key];

	Information* i = informations[derHash];
	while (i->getKey() != key) {
		i = i->getNextInfo();
	}
	return i;
}

void Symboltable::keySizeBigger() {
	keysize++;
	if (keysize > keysizemax) {
		keysizemax *= 2;
		int* tempList = (int*) malloc(keysizemax * sizeof(int));
		memcpy(tempList, keys, keysizemax / 2 * sizeof(int));
		free(keys);
		keys = tempList;
	}
}

uint16_t Symboltable::newInfo(char* lexem) {
	// TODO Bei Typ Integer value bestimmen
	// TODO Konzept für Typ ausdenken/nachschauen und implementieren (Typen nach Skript: sign, integer, identifier, if, while)
	uint16_t derHash = hash(lexem);
	uint16_t key = keysize;
	keys[key] = derHash;
	keySizeBigger();
	Information* i_next = informations[derHash];
	if (i_next == '\0') {
		i_next = new Information(lexem, key);
		informations[derHash] = i_next;
	} else {
		do {
			if (strcmp(lexem, i_next->getLexem()) == 0) {
				keysize--;
				return i_next->getKey();
			}
			if (i_next->getNextInfo() != '\0') {
				i_next = i_next->getNextInfo();
			}
		} while (i_next->getNextInfo() != '\0');
		i_next->setNextInfo(new Information(lexem, key));
	}

	return key;
}

void Symboltable::initSymbols() {
	// Keys für reservierte Ausdrücke:
	newInfo("if");		// 0
	newInfo("IF");		// 1
	newInfo("while");	// 2
	newInfo("WHILE");	// 3
}
