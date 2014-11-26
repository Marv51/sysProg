/*
 * Scanner.h
 *
 *  Created on: Sep 26, 2012
 *      Author: knad0001
 */

#include "../../Automat/src/Automat.h"
#include "../../Buffer/src/Buffer.h"
#include "Token.h"
#include "../../Symboltable/src/Symboltable.h"
#include <stdint.h>

#ifndef SCANNER_H_
#define SCANNER_H_

class Scanner {
public:
	Scanner(char* input);
	virtual ~Scanner();
	bool nextToken(Token *);
	Symboltable* getSymboltable();

private:
	bool ignoreChar(char ch);
	void makeInfo(Token* t);
	Automat* automat;
	Buffer* buffer;
	Symboltable* symtable;
};

#endif /* SCANNER_H_ */
