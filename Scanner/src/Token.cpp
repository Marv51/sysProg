#include "Token.h"

Token::Token() {
	content = new myListe();
	spalte = 1;
	zeile = 1;
	tokentype = Unknown;
}

Token::~Token() {
	delete content;
}

void Token::setSpalte(int spalte) {
	this->spalte = spalte;
}

void Token::setZeile(int zeile) {
	this->zeile = zeile;
}

int Token::getSpalte() {
	return spalte;
}

int Token::getZeile() {
	return zeile;
}

void Token::setTokenType(TokenType t) {
	tokentype = t;
}
TokenType Token::getTokenType() {
	return tokentype;
}

