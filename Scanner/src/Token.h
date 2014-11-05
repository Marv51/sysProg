#ifndef TOKEN_H_
#define TOKEN_H_

#include "myListe.h"
enum TokenType {
	Unknown //TODO TokenType
};

class Token {
public:
	Token();
	virtual ~Token();
	int getZeile();
	int getSpalte();
	void setZeile(int zeile);
	void setSpalte(int spalte);
	void setTokenType(TokenType t);
	TokenType getTokenType();
	myListe* content;

private:
	TokenType tokentype;
	int zeile;
	int spalte;
	// TODO Klasse Information erstellen -> Symboltabelle
};

#endif
