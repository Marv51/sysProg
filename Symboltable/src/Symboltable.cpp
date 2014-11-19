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
	informations = (Information**) malloc(memsize * sizeof(Information*));
	memset(informations, '\0', memsize * sizeof(Information*));
}

Symboltable::~Symboltable() {
	for (int i = 0; i < memsize; i++) {
		if (informations[i] != '\0') {
			delete (informations[i]);
		}
	}
	free(informations);
}

uint16_t Symboltable::hash(char* ch) {
	uint16_t ergebnis = 0;
	int i = 0;
	while (ch[i] != '\0') {
		ergebnis += (uint16_t) ch[i];
		i++;
	}

	return ergebnis % memsize;
}

Information* Symboltable::getInfo(uint16_t key) {
	return informations[key];
}

uint16_t Symboltable::newInfo(char* lexem) {
	uint16_t key = hash(lexem);
	if (getInfo(key) == '\0') {  // erstellen falls noch nicht existiert
		informations[key] = new Information(lexem);
	}
	return key;
}
