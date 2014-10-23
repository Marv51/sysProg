#include "Token.h"

Token::Token(TokenType type, int zeil, int spalt){
	tokentype = type;
	zeile = zeil;
	spalte = spalt;
}

Token::~Token(){

}
