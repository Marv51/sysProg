/*
 * Symboltable.h
 *
 *  Created on: Sep 26, 2012
 *      Author: knad0001
 */
#include "Information.h"

#ifndef SYMBOLTABLE_H_
#define SYMBOLTABLE_H_

#include <stdint.h>
#include <error.h>
#include <errno.h>

class Symboltable {
public:
	Symboltable();
	virtual ~Symboltable();
	Information* getInfo(uint16_t key);
	uint16_t newInfo(char* lexem, InfoTyp t);
	uint16_t hash(char* ch);
	Information* searchInfo(char* lexem);
private:
	uint16_t memsize;
	Information** informations;
	int* keys;
	uint16_t keysize;
	uint16_t keysizemax;
	void keySizeBigger();
	void initSymbols();
};

#endif /* SYMBOLTABLE_H_ */
