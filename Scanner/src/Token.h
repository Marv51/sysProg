#ifndef TOKEN_H_
#define TOKEN_H_

enum TokenType {
	Unknown, Integer, Float // TODO Token types weiter ergänzen
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
	char content[100];
private:
	TokenType tokentype;
	int zeile;
	int spalte;
	// TODO Klasse Information erstellen -> Symboltabelle
};

#endif
