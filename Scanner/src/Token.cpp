#include "Token.h"

Token::Token(TokenType type, int zeil, int spalt, char cont[]){
	tokentype = type;
	zeile = zeil;
	spalte = spalt;
	content = cont;
}

Token::~Token(){

}
