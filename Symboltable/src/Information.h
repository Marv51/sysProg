/*
 * Information.h
 *
 *  Created on: Nov 6, 2014
 *      Author: marius
 */

#ifndef SYMBOLTABLE_SRC_INFORMATION_H_
#define SYMBOLTABLE_SRC_INFORMATION_H_

#include <stdint.h>
#include <stdlib.h>
#include <errno.h>
#include <error.h>
#include <limits.h>
#include "../../Parser/src/Node.h"

enum class InfoTyp{
	Unknown,
	Sign,
	Integer,
	Identifier,
	iftyp,
	whiletyp,
	elsetyp,
	inttyp,
	writetyp,
	readtyp,
	Fehler
};

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
	InfoTyp getType();
	void setType(InfoTyp t);
	CheckType getCheckType() const;
	void setCheckType(CheckType checkType);

private:
	char* lexem;
	Information* nextInfo;
	uint16_t key;
	int value;
	InfoTyp type;
	CheckType checkType;
};

#endif /* SYMBOLTABLE_SRC_INFORMATION_H_ */
