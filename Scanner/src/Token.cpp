#include "Token.h"

Token::Token() {
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

void Token::setTokenType(State t) {
	tokentype = t;
}
State Token::getTokenType() {
	return tokentype;
}

const char* Token::getTokenTypeString() {
	const char* tokennames[] = { "Undefined", "Start", "Number", "Identifier",
			"KleinerAls", "GeschweifteKlammerAuf", "GeschweifteKlammerZu",
			"VorwaertsSchraegstrich", "EckigeKlammerAuf", "EckigeKlammerZu",
			"UndZeichen", "GroesserAls", "Stern", "Ausrufezeichen", "RundeKlammerAuf",
			"RundeKlammerZu", "IstGleichZeichen", "Minus", "Plus", "Doppelpunkt",
			"DoppelpunktIstGleich", "Semikolon", "KleinerDoppelpunkt",
			"kleinerDoppelpunktGroesser", "SchraegStrichStern",
			"SchraegstrichSternStern", "SchraegstrichSternSternSchraegstrich", "Fehler" };
	return tokennames[tokentype];
}

