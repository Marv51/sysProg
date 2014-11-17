/*
 * Symboltable.cpp
 *
 *  Created on: Sep 26, 2012
 *      Author: knad0001
 */

#include "Symboltable.h"
#include <stdlib.h>
#include <string.h>
#include <stdint.h> //TODO verwenden

Symboltable::Symboltable() {
	memsize = sizeof(int);
	keys = (uint32_t*) malloc(memsize * sizeof(uint32_t));
	informations = (Information**) malloc(memsize * sizeof(Information*));
}

Symboltable::~Symboltable() {
	free (keys);
	free(informations);
}

int Symboltable::hash(char* ch) {
	int ergebnis = 0;
	int i = 0;
	while (ch[i] != '\0') {
		i += (int) ch[i];
		i++;
	}

	return ergebnis;
}

Information* Symboltable::getInfo(char* lexem) {
	int key = hash(lexem);
	for (int i = memsize; i > 0; i--) {
		if (keys[i] == key) {
			return informations[i];
		}
	}
	return '\0';
}

void Symboltable::newInfo(char* lexem) {
	//TODO implement newInfo

}
