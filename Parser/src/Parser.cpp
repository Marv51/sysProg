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
	createNode();
	parseDecls();
	parseStatements();
}

void Parser::parseDecls() {
	auto info = scanner->getInfo(token->getKey());
	if (info->getType() == InfoTyp::inttyp) {
		parseDecl();
		match(State::Semikolon);
		parseDecls();
	}
}

void Parser::parseDecl() {
	match(InfoTyp::inttyp);
	parseArray();
	match(InfoTyp::Identifier);
}

void Parser::parseArray() {
	if (token->getTokenType() == State::EckigeKlammerAuf) {
		match(State::EckigeKlammerAuf);
		match(State::Number);
		match(State::EckigeKlammerZu);
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
		match(State::Semikolon);
		parseStatements();
	}
}

void Parser::parseStatement() {
	auto infoType = scanner->getInfo(token->getKey())->getType();
	auto tokenType = token->getTokenType();
	if (infoType == InfoTyp::Identifier) {
		match(InfoTyp::Identifier);
		parseIndex();
		match(State::DoppelpunktIstGleich);
		parseExp();
	} else if (infoType == InfoTyp::writetyp) {
		match(InfoTyp::writetyp);
		match(State::RundeKlammerAuf);
		parseExp();
		match(State::RundeKlammerZu);
	} else if (infoType == InfoTyp::readtyp) {
		match(InfoTyp::readtyp);
		match(State::RundeKlammerAuf);
		match(InfoTyp::Identifier);
		parseIndex();
		match(State::RundeKlammerZu);
	} else if (tokenType == State::GeschweifteKlammerAuf) {
		match(State::GeschweifteKlammerAuf);
		parseStatements();
		match(State::GeschweifteKlammerZu);
	} else if (infoType == InfoTyp::iftyp) {
		match(InfoTyp::iftyp);
		match(State::RundeKlammerAuf);
		parseExp();
		match(State::RundeKlammerZu);
		parseStatement();
		match(InfoTyp::elsetyp);
		parseStatement();
	} else if (infoType == InfoTyp::whiletyp) {
		match(InfoTyp::whiletyp);
		match(State::RundeKlammerAuf);
		parseExp();
		match(State::RundeKlammerZu);
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
		match(State::RundeKlammerAuf);
		parseExp();
		match(State::RundeKlammerZu);
	} else if (infoType == InfoTyp::Identifier) {
		match(InfoTyp::Identifier);
		parseIndex();
	} else if (infoType == InfoTyp::Integer) {
		match(InfoTyp::Integer);
	} else if (tokenType == State::Minus) {
		match(State::Minus);
		parseExp2();
	} else if (tokenType == State::Ausrufezeichen) {
		match(State::Ausrufezeichen);
		parseExp2();
	} else {
		error();
	}
}

void Parser::parseIndex() {
	if (token->getTokenType() == State::EckigeKlammerAuf) {
		match(State::EckigeKlammerAuf);
		parseExp();
		match(State::EckigeKlammerZu);
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
		match(State::Plus);
	} else if (tokenType == State::Minus) {
		match(State::Minus);
	} else if (tokenType == State::Stern) {
		match(State::Stern);
	} else if (tokenType == State::VorwaertsSchraegstrich) {
		match(State::VorwaertsSchraegstrich);
	} else if (tokenType == State::KleinerAls) {
		match(State::KleinerAls);
	} else if (tokenType == State::GroesserAls) {
		match(State::GroesserAls);
	} else if (tokenType == State::IstGleichZeichen) {
		match(State::IstGleichZeichen);
	} else if (tokenType == State::kleinerDoppelpunktGroesser) {
		match(State::kleinerDoppelpunktGroesser);
	} else if (tokenType == State::UndZeichen) {
		match(State::UndZeichen);
	} else {
		error();
	}
}

void Parser::nextToken() {
	token = new Token();
	scanner->nextToken(token);
}

void Parser::match(State typ) {
	if (token->getTokenType() != typ) {
		error();
	}
	delete token;
	nextToken();
}

void Parser::match(InfoTyp typ) {
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
