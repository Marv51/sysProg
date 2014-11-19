/*
 * Information.cpp
 *
 *  Created on: Nov 6, 2014
 *      Author: marius
 */

#include "Information.h"
#include <string.h>

Information::Information(char* lex) {
	lexem = lex;
	nextInfo = '\0';
}

Information::~Information() {
	delete(nextInfo);
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

Information* Information::getNextInfo(){
	return nextInfo;
}

void Information::setNextInfo(Information* info){
	nextInfo = info;
}
