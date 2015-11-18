/*
 * Parser.cpp
 *
 *  Created on: Nov 18, 2015
 *      Author: marius
 */

#include "Parser.h"

Parser::Parser(Scanner* s) {
	scanner = s;
	token = new Token();
	scanner->nextToken(token);
}

Parser::~Parser() {
}

void Parser::parse() {
	parseProg();
}

void Parser::parseProg() {
	parseDecls();
	parseStatements();
}

void Parser::parseDecls() {
	auto info = scanner->getInfo(token->getKey());
	if (info->getType() == InfoTyp::inttyp) {
		parseDecl();
		accept(State::Semikolon);
		parseDecls();
	}
}

void Parser::parseDecl() {
	accept(InfoTyp::inttyp);
	parseArray();
	accept(InfoTyp::Identifier);
}

void Parser::parseArray() {
	if (token->getTokenType() == State::EckigeKlammerAuf) {
		accept(State::EckigeKlammerAuf);
		accept(State::Number);
		accept(State::EckigeKlammerZu);
	}
}

void Parser::parseStatements() {
	auto infoType = scanner->getInfo(token->getKey())->getType();
	auto tokenType = token->getTokenType();
	if (infoType == InfoTyp::Identifier || infoType == InfoTyp::writetyp
			|| infoType == InfoTyp::readtyp
			|| tokenType == State::GeschweifteKlammerAuf
			|| infoType == InfoTyp::iftyp || infoType == InfoTyp::whiletyp) {
		parseStatement();
		accept(State::Semikolon);
		parseStatements();
	}
}

void Parser::parseStatement() {
	auto infoType = scanner->getInfo(token->getKey())->getType();
	auto tokenType = token->getTokenType();
	if (infoType == InfoTyp::Identifier) {
		accept(InfoTyp::Identifier);
		parseIndex();
		accept(State::DoppelpunktIstGleich);
		parseExp();
	} else if (infoType == InfoTyp::writetyp) {
		accept(InfoTyp::writetyp);
		accept(State::RundeKlammerAuf);
		parseExp();
		accept(State::RundeKlammerZu);
	} else if (infoType == InfoTyp::readtyp) {
		accept(InfoTyp::readtyp);
		accept(State::RundeKlammerAuf);
		accept(InfoTyp::Identifier);
		parseIndex();
		accept(State::RundeKlammerZu);
	} else if (tokenType == State::GeschweifteKlammerAuf) {
		accept(State::GeschweifteKlammerAuf);
		parseStatements();
		accept(State::GeschweifteKlammerZu);
	} else if (infoType == InfoTyp::iftyp) {
		accept(InfoTyp::iftyp);
		accept(State::RundeKlammerAuf);
		parseExp();
		accept(State::RundeKlammerZu);
		parseStatement();
		accept(InfoTyp::elsetyp);
		parseStatement();
	} else if (infoType == InfoTyp::whiletyp) {
		accept(InfoTyp::whiletyp);
		accept(State::RundeKlammerAuf);
		parseExp();
		accept(State::RundeKlammerZu);
		parseStatement();
	} else {
		error();
	}
}

void Parser::parseExp() {
	parseExp2();
	parseOpExp();
}

void Parser::parseExp2() {
	auto infoType = scanner->getInfo(token->getKey())->getType();
	auto tokenType = token->getTokenType();
	if (tokenType == State::RundeKlammerAuf) {
		accept(State::RundeKlammerAuf);
		parseExp();
		accept(State::RundeKlammerZu);
	} else if (infoType == InfoTyp::Identifier) {
		accept(InfoTyp::Identifier);
		parseIndex();
	} else if (infoType == InfoTyp::Integer) {
		accept(InfoTyp::Integer);
	} else if (tokenType == State::Minus) {
		accept(State::Minus);
		parseExp2();
	} else if (tokenType == State::Ausrufezeichen) {
		accept(State::Ausrufezeichen);
		parseExp2();
	} else {
		error();
	}
}

void Parser::parseIndex() {
	if (token->getTokenType() == State::EckigeKlammerAuf) {
		accept(State::EckigeKlammerAuf);
		parseExp();
		accept(State::EckigeKlammerZu);
	}
}

void Parser::parseOpExp() {
	auto tokenType = token->getTokenType();
	if (tokenType == State::Plus || tokenType == State::Minus
			|| tokenType == State::Stern
			|| tokenType == State::VorwaertsSchraegstrich
			|| tokenType == State::KleinerAls || tokenType == State::GroesserAls
			|| tokenType == State::kleinerDoppelpunktGroesser
			|| tokenType == State::UndZeichen) {
		parseOp();
		parseExp();
	}
}

void Parser::parseOp() {
	auto tokenType = token->getTokenType();
	if (tokenType == State::Plus) {
		accept(State::Plus);
	} else if (tokenType == State::Minus) {
		accept(State::Minus);
	} else if (tokenType == State::Stern) {
		accept(State::Stern);
	} else if (tokenType == State::VorwaertsSchraegstrich) {
		accept(State::VorwaertsSchraegstrich);
	} else if (tokenType == State::KleinerAls) {
		accept(State::KleinerAls);
	} else if (tokenType == State::GroesserAls) {
		accept(State::GroesserAls);
	} else if (tokenType == State::IstGleichZeichen) {
		accept(State::IstGleichZeichen);
	} else if (tokenType == State::kleinerDoppelpunktGroesser) {
		accept(State::kleinerDoppelpunktGroesser);
	} else if (tokenType == State::UndZeichen) {
		accept(State::UndZeichen);
	} else {
		error();
	}
}

void Parser::nextToken() {
	token = new Token();
	scanner->nextToken(token);
}

void Parser::accept(State typ) {
	if (token->getTokenType() != typ) {
		error();
	}
	delete token;
	nextToken();
}

void Parser::accept(InfoTyp typ) {
	if (scanner->getInfo(token->getKey())->getType() != typ) {
		error();
	}
	delete token;
	nextToken();
}

void Parser::error() {
	printf("unexpected token '%s' at line '%d', column '%d'\n",
			token->getContent(), token->getZeile(), token->getSpalte());
	printf("Typ: '%s'", token->getTokenTypeString());
	exit(1);
}
