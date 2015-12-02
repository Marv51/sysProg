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

Node* Parser::parse() {
	return parseProg();
}

Node* Parser::parseProg() {
	auto prog = createNode(NodeType::PROG);
	auto decls = parseDecls();
	prog->addNode(decls);
	auto statements = parseStatements();
	prog->addNode(statements);
	return prog;
}

Node* Parser::parseDecls() {
	auto decls = createNode(NodeType::DECLS);
	auto info = scanner->getInfo(token->getKey());
	if (info->getType() == InfoTyp::inttyp) {
		decls->addNode(parseDecl());
		decls->addNode(match(State::Semikolon));
		decls->addNode(parseDecls());
	}
	return decls;
}

Node* Parser::parseDecl() {
	auto decl = createNode(NodeType::DECL);
	decl->addNode(match(InfoTyp::inttyp));
	decl->addNode(parseArray());
	decl->addNode(match(InfoTyp::Identifier));
	return decl;
}

Node* Parser::parseArray() {
	auto array = createNode(NodeType::ARRAY);
	if (token->getTokenType() == State::EckigeKlammerAuf) {
		array->addNode(match(State::EckigeKlammerAuf));
		array->addNode(match(State::Number));
		array->addNode(match(State::EckigeKlammerZu));
	}
	return array;
}

Node* Parser::parseStatements() {
	auto statements = createNode(NodeType::STATEMENTS);
	auto infoType = scanner->getInfo(token->getKey())->getType();
	auto tokenType = token->getTokenType();
	if (infoType == InfoTyp::Identifier || infoType == InfoTyp::writetyp
			|| infoType == InfoTyp::readtyp
			|| tokenType == State::GeschweifteKlammerAuf
			|| infoType == InfoTyp::iftyp || infoType == InfoTyp::whiletyp) {
		statements->addNode(parseStatement());
		statements->addNode(match(State::Semikolon));
		statements->addNode(parseStatements());
	}
	return statements;
}

Node* Parser::parseStatement() {
	auto statement = createNode(NodeType::STATEMENT);
	auto infoType = scanner->getInfo(token->getKey())->getType();
	auto tokenType = token->getTokenType();
	if (infoType == InfoTyp::Identifier) {
		statement->addNode(match(InfoTyp::Identifier));
		statement->addNode(parseIndex());
		statement->addNode(match(State::DoppelpunktIstGleich));
		statement->addNode(parseExp());
	} else if (infoType == InfoTyp::writetyp) {
		statement->addNode(match(InfoTyp::writetyp));
		statement->addNode(match(State::RundeKlammerAuf));
		statement->addNode(parseExp());
		statement->addNode(match(State::RundeKlammerZu));
	} else if (infoType == InfoTyp::readtyp) {
		statement->addNode(match(InfoTyp::readtyp));
		statement->addNode(match(State::RundeKlammerAuf));
		statement->addNode(match(InfoTyp::Identifier));
		statement->addNode(parseIndex());
		statement->addNode(match(State::RundeKlammerZu));
	} else if (tokenType == State::GeschweifteKlammerAuf) {
		statement->addNode(match(State::GeschweifteKlammerAuf));
		statement->addNode(parseStatements());
		statement->addNode(match(State::GeschweifteKlammerZu));
	} else if (infoType == InfoTyp::iftyp) {
		statement->addNode(match(InfoTyp::iftyp));
		statement->addNode(match(State::RundeKlammerAuf));
		statement->addNode(parseExp());
		statement->addNode(match(State::RundeKlammerZu));
		statement->addNode(parseStatement());
		statement->addNode(match(InfoTyp::elsetyp));
		statement->addNode(parseStatement());
	} else if (infoType == InfoTyp::whiletyp) {
		statement->addNode(match(InfoTyp::whiletyp));
		statement->addNode(match(State::RundeKlammerAuf));
		statement->addNode(parseExp());
		statement->addNode(match(State::RundeKlammerZu));
		statement->addNode(parseStatement());
	} else {
		error();
	}
	return statement;
}

Node* Parser::parseExp() {
	auto exp = createNode(NodeType::EXP);
	exp->addNode(parseExp2());
	exp->addNode(parseOpExp());
	return exp;
}

Node* Parser::parseExp2() {
	auto exp2 = createNode(NodeType::EXP2);
	auto infoType = scanner->getInfo(token->getKey())->getType();
	auto tokenType = token->getTokenType();
	if (tokenType == State::RundeKlammerAuf) {
		exp2->addNode(match(State::RundeKlammerAuf));
		exp2->addNode(parseExp());
		exp2->addNode(match(State::RundeKlammerZu));
	} else if (infoType == InfoTyp::Identifier) {
		exp2->addNode(match(InfoTyp::Identifier));
		exp2->addNode(parseIndex());
	} else if (infoType == InfoTyp::Integer) {
		exp2->addNode(match(InfoTyp::Integer));
	} else if (tokenType == State::Minus) {
		exp2->addNode(match(State::Minus));
		exp2->addNode(parseExp2());
	} else if (tokenType == State::Ausrufezeichen) {
		exp2->addNode(match(State::Ausrufezeichen));
		exp2->addNode(parseExp2());
	} else {
		error();
	}
	return exp2;
}

Node* Parser::parseIndex() {
	auto index = createNode(NodeType::INDEX);
	if (token->getTokenType() == State::EckigeKlammerAuf) {
		index->addNode(match(State::EckigeKlammerAuf));
		index->addNode(parseExp());
		index->addNode(match(State::EckigeKlammerZu));
	}
	return index;
}

Node* Parser::parseOpExp() {
	auto op_exp = createNode(NodeType::OP_EXP);
	auto tokenType = token->getTokenType();
	if (tokenType == State::Plus || tokenType == State::Minus
			|| tokenType == State::Stern
			|| tokenType == State::VorwaertsSchraegstrich
			|| tokenType == State::KleinerAls || tokenType == State::GroesserAls
			|| tokenType == State::kleinerDoppelpunktGroesser
			|| tokenType == State::UndZeichen) {
		op_exp->addNode(parseOp());
		op_exp->addNode(parseExp());
	}
	return op_exp;
}

Node* Parser::parseOp() {
	auto op = createNode(NodeType::OP);
	auto tokenType = token->getTokenType();
	if (tokenType == State::Plus) {
		op->addNode(match(State::Plus));
	} else if (tokenType == State::Minus) {
		op->addNode(match(State::Minus));
	} else if (tokenType == State::Stern) {
		op->addNode(match(State::Stern));
	} else if (tokenType == State::VorwaertsSchraegstrich) {
		op->addNode(match(State::VorwaertsSchraegstrich));
	} else if (tokenType == State::KleinerAls) {
		op->addNode(match(State::KleinerAls));
	} else if (tokenType == State::GroesserAls) {
		op->addNode(match(State::GroesserAls));
	} else if (tokenType == State::IstGleichZeichen) {
		op->addNode(match(State::IstGleichZeichen));
	} else if (tokenType == State::kleinerDoppelpunktGroesser) {
		op->addNode(match(State::kleinerDoppelpunktGroesser));
	} else if (tokenType == State::UndZeichen) {
		op->addNode(match(State::UndZeichen));
	} else {
		error();
	}
	return op;
}

void Parser::nextToken() {
	token = new Token();
	scanner->nextToken(token);
}

Node* Parser::match(State typ) {
	if (token->getTokenType() != typ) {
		error();
	}
	auto leaf = createNode(NodeType::LEAF);
	leaf->setKey(token->getKey(), token->getContent());
	nextToken();
	return leaf;
}

Node* Parser::match(InfoTyp typ) {
	if (scanner->getInfo(token->getKey())->getType() != typ) {
		error();
	}
	auto leaf = createNode(NodeType::LEAF);
	leaf->setKey(token->getKey(), token->getContent());
	nextToken();
	return leaf;
}

void Parser::error() {
	printf("unexpected token '%s' at line '%d', column '%d'\n",
			token->getContent(), token->getZeile(), token->getSpalte());
	printf("Typ: '%s'", token->getTokenTypeString());
	exit(1);
}

Node* Parser::createNode(NodeType ntype) {
	return new Node(ntype);
}
