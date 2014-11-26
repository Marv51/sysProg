/*
 * Information.h
 *
 *  Created on: Nov 6, 2014
 *      Author: marius
 */

#ifndef SYMBOLTABLE_SRC_INFORMATION_H_
#define SYMBOLTABLE_SRC_INFORMATION_H_

#include <stdint.h>

class Information {
public:
	Information(char* lex, uint16_t k);
	virtual ~Information();
	char* getLexem();
	void setLexem(char* lex);
	bool compareLexem(char* lex);
	Information* getNextInfo();
	void setNextInfo(Information* info);
	uint16_t getKey();
	int getValue();
	void setValue(int i);
	uint8_t getType();
	void setType(uint8_t t);
private:
	char* lexem;
	Information* nextInfo;
	uint16_t key;
	int value;
	uint8_t type;
};

#endif /* SYMBOLTABLE_SRC_INFORMATION_H_ */
