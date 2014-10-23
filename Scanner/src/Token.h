#ifndef TOKEN_H_
#define TOKEN_H_

enum TokenType {
	Integer, Float // TODO Token types weiter ergänzen
};

class Token {
public:
	Token(TokenType, int, int);
	virtual ~Token();
private:
	TokenType tokentype;
	int zeile;
	int spalte;
	// TODO Klasse Information erstellen
};

#endif
