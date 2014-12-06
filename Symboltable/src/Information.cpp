/*
 * Information.cpp
 *
 *  Created on: Nov 6, 2014
 *      Author: marius
 */

#include "Information.h"
#include <string.h>
#include <stdlib.h>

Information::Information(char* lex, uint16_t k) {
	setLexem(lex);
	nextInfo = '\0';
	key = k;
	value = -1;
	type = 0;
	/*
	 * Typen:
	 * 0 = unknown
	 * 1 = sign
	 * 2 = integer
	 * 3 = identifier
	 * 4 = if
	 * 5 = while
	 * 6 = fehler
	 */
}

Information::~Information() {
	delete (nextInfo);
}

bool Information::compareLexem(char* lex) {
	return strcmp(lex, lexem) == 0;
}

char* Information::getLexem() {
	return lexem;
}

void Information::setLexem(char* lex) {
	lexem = lex;
}

Information* Information::getNextInfo() {
	return nextInfo;
}

void Information::setNextInfo(Information* info) {
	nextInfo = info;
}

uint16_t Information::getKey() {
	return key;
}

int Information::getValue() {
	if (value == -1) {
		long int longInt = strtol(lexem, NULL, 10);
		if (longInt > INT_MAX || longInt < 0) {
			error(0, EOVERFLOW, "Bereichsüberschreitung!");
			value = 0;
			return -1;
		}
		value = (int) longInt;
	}
	return value;
}

uint8_t Information::getType() {
	return type;
}

void Information::setType(uint8_t t) {
	type = t;
}
