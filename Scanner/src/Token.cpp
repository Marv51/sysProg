#include "Token.h"

Token::Token() {
	key = '\0';
	content = new myListe();
	spalte = 1;
	zeile = 1;
	tokentype = Undefined;
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

void Token::setTokenType(int t) {
	tokentype = t;
}
int Token::getTokenType() {
	return tokentype;
}

char* Token::getContent(){
	return content->getString();
}

uint16_t Token::getKey(){
	return key;
}

void Token::setKey(uint16_t k){
	key = k;
}

const char* Token::getTokenTypeString() {
	const char* tokennames[] = { "Undefined", "Start", "Integer", "Identifier",
			"<", "{", "}",
			"/", "[", "]",
			"&", ">", "*", "!", "(",
			")", "=", "-", "+", ":",
			":=", ";", "<:",
			"<:>", "SchraegStrichStern",
			"SchraegstrichSternStern", "SchraegstrichSternSternSchraegstrich", "Fehler" };
	return tokennames[tokentype];
}

