/*
 * Scanner.cpp
 *
 *  Created on: Sep 26, 2012
 *      Author: knad0001
 */

#include "Scanner.h"

Scanner::Scanner() {
	buffer = new Buffer();
	automat = new Automat();
}

Scanner::~Scanner() {
}

void Scanner::nextToken(){
	bool cont;
	do{
		cont = automat->testChar(buffer->getChar());
	}while(cont);
}
