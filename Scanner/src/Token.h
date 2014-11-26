#ifndef TOKEN_H_
#define TOKEN_H_

#include "myListe.h"
#include "../../Automat/src/Automat.h"
#include <stdint.h>

class Token {
public:
	Token();
	virtual ~Token();
	int getZeile();
	int getSpalte();
	void setZeile(int zeile);
	void setSpalte(int spalte);
	void setTokenType(int t);
	int getTokenType();
	const char* getTokenTypeString();
	char* getContent();
	uint16_t getKey();
	void setKey(uint16_t k);
	myListe* content;

private:
	int tokentype;
	int zeile;
	int spalte;
	uint16_t key;
};

#endif
