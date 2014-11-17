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

class Symboltable {
public:
	Symboltable();
	virtual ~Symboltable();
	Information* getInfo(uint16_t key);
	uint16_t newInfo(char* lexem);
	uint16_t hash(char* ch);
private:
	int memsize;
	Information** informations;
};

#endif /* SYMBOLTABLE_H_ */
