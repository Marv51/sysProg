/*
 * Symboltable.h
 *
 *  Created on: Sep 26, 2012
 *      Author: knad0001
 */
#include "Information.h"

#ifndef SYMBOLTABLE_H_
#define SYMBOLTABLE_H_

class Symboltable {
public:
	Symboltable();
	virtual ~Symboltable();
	Information* getInfo(char* lexem);
	void newInfo(char* lexem);
	int hash(char* ch);
private:
	int* keys;
	int memsize;
	Information** informations;
};

#endif /* SYMBOLTABLE_H_ */
