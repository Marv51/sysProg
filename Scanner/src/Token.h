#ifndef TOKEN_H_
#define TOKEN_H_

enum TokenType {
	Integer, Float // TODO Token types weiter ergänzen
};

class Token {
public:
	Token();
	virtual ~Token();
private:
	TokenType tokentype;
	int zeile;
	int spalte;
	char content[100];
	// TODO Klasse Information erstellen -> Symboltabelle
};

#endif
