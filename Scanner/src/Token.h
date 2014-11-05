#ifndef TOKEN_H_
#define TOKEN_H_

#include "myListe.h"
#include "../../Automat/src/Automat.h"

class Token {
public:
	Token();
	virtual ~Token();
	int getZeile();
	int getSpalte();
	void setZeile(int zeile);
	void setSpalte(int spalte);
	void setTokenType(State t);
	State getTokenType();
	const char* getTokenTypeString();
	myListe* content;

private:
	State tokentype;
	int zeile;
	int spalte;
	// TODO Klasse Information erstellen -> Symboltabelle
};

#endif
