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
	//informations[i].nextInformation werden im Destruktor der "obersten" Informationen gelöscht.
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
	if (keysize >= keysizemax) {
		keysizemax *= 2;
		int* tempList = (int*) malloc(keysizemax * sizeof(int));
		memcpy(tempList, keys, keysizemax / 2 * sizeof(int));
		free(keys);
		keys = tempList;
	}
}

uint16_t Symboltable::newInfo(char* lexem, InfoTyp t) {
	uint16_t derHash = hash(lexem);
	uint16_t key = keysize;
	Information* newInfo = new Information(lexem, key );
	newInfo->setType(t);
	keys[key] = derHash;
	keySizeBigger();
	Information* i_next = informations[derHash];
	if (i_next == '\0') {
		i_next = newInfo;
		informations[derHash] = i_next;
	} else {
		do {
			if (t == i_next->getType() && strcmp(lexem, i_next->getLexem()) == 0) {
				keysize--;
				delete newInfo;
				return i_next->getKey();
			}
			if (i_next->getNextInfo() != '\0') {
				i_next = i_next->getNextInfo();
			}
		} while (i_next->getNextInfo() != '\0');
		i_next->setNextInfo(newInfo);
	}

	return key;
}

void Symboltable::initSymbols() {
	// Keys für reservierte Ausdrücke:
	newInfo((char *)"if", InfoTyp::iftyp);
	newInfo((char *)"IF", InfoTyp::iftyp);
	newInfo((char *)"while", InfoTyp::whiletyp);
	newInfo((char *)"WHILE", InfoTyp::whiletyp);
	newInfo((char *)"else", InfoTyp::elsetyp);
	newInfo((char *)"ELSE", InfoTyp::elsetyp);
	newInfo((char *)"int", InfoTyp::inttyp);
	newInfo((char *)"write", InfoTyp::writetyp);
	newInfo((char *)"read", InfoTyp::readtyp);
}
