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
	size = 0;
	memsize = 8;
	lexems = (char*) malloc(memsize * sizeof(char));
	informations = (Information**) malloc(memsize * sizeof(Information*));
}

Symboltable::~Symboltable() {
	free(lexems);
	free(informations);
}

Information* Symboltable::getInfo(char* lexem) {
	for (int i = size; i > 0; i--) {
		if (lexems[i] == lexem) { //TODO nachforschen warum Fehler
			return informations[i];
		}
	}
	return '\0';
}

void Symboltable::newInfo(char* lexem) {
	//TODO implement newInfo
	size++;
	if (size >= memsize) {
		memsize *= 2;

		char* tempList = (char*) malloc(memsize * sizeof(char));
		memcpy(tempList, lexems, memsize / 2 * sizeof(char));
		free(lexems);
		lexems = tempList;

		Information** tempList2 = (Information**) malloc(memsize * sizeof(Information*));
		memcpy(tempList2, informations, memsize / 2 * sizeof(Information**));
		free(informations);
		informations = tempList2;
	}

	lexems[size] = lexem;
	// TODO lexems muss wohl zu keys werden
	informations[size] = new Information(lexem);

}
