/*
 * Automat.cpp
 *
 */

#include "Automat.h"

Automat::Automat() {
	lastFinalState = State::Start;
	stepsSinceLastFinalState = 0;
	currentState = State::Start;
	zeile = 1;
	spalte = 1;

	TokenAnfangSpalte = 1;
	TokenAnfangZeile = 1;

	//Initalisiert jeden Zustand mit nur undefinieren Übergängen
	for (int i = (int) State::Number;
			i != (int) State::SchraegstrichSternSternSchraegstrich; i++) {
		for (int a = 1; a <= 255; a++) {
			stateMatrix[i][a] = State::Undefined;
		}
	}

	stateMatrix[(int) State::Start]['{'] = State::GeschweifteKlammerAuf;
	stateMatrix[(int) State::Start]['}'] = State::GeschweifteKlammerZu;
	stateMatrix[(int) State::Start]['('] = State::RundeKlammerAuf;
	stateMatrix[(int) State::Start][')'] = State::RundeKlammerZu;
	stateMatrix[(int) State::Start]['['] = State::EckigeKlammerAuf;
	stateMatrix[(int) State::Start][']'] = State::EckigeKlammerZu;
	stateMatrix[(int) State::Start]['='] = State::IstGleichZeichen;
	stateMatrix[(int) State::Start]['-'] = State::Minus;
	stateMatrix[(int) State::Start]['+'] = State::Plus;
	stateMatrix[(int) State::Start]['/'] = State::VorwaertsSchraegstrich;
	stateMatrix[(int) State::Start][';'] = State::Semikolon;
	stateMatrix[(int) State::Start]['*'] = State::Stern;
	stateMatrix[(int) State::Start]['&'] = State::UndZeichen;
	stateMatrix[(int) State::Start]['!'] = State::Ausrufezeichen;
	stateMatrix[(int) State::Start]['>'] = State::GroesserAls;
	stateMatrix[(int) State::Start]['<'] = State::KleinerAls;
	stateMatrix[(int) State::Start][':'] = State::Doppelpunkt;

	// Die Uebergangs Matrix erstellen
	for (int i = '0'; i <= '9'; i++) {
		stateMatrix[(int) State::Start][i] = State::Number;
		stateMatrix[(int) State::Number][i] = State::Number;
		stateMatrix[(int) State::Identifier][i] = State::Identifier;
	}
	for (int i = 'a'; i <= 'z'; i++) {
		stateMatrix[(int) State::Start][i] = State::Identifier;
		stateMatrix[(int) State::Identifier][i] = State::Identifier;
	}
	for (int i = 'A'; i <= 'Z'; i++) {
		stateMatrix[(int) State::Start][i] = State::Identifier;
		stateMatrix[(int) State::Identifier][i] = State::Identifier;
	}

	stateMatrix[(int) State::KleinerAls][':'] = State::KleinerDoppelpunkt;
	stateMatrix[(int) State::KleinerDoppelpunkt]['>'] =
			State::kleinerDoppelpunktGroesser;
	stateMatrix[(int) State::Doppelpunkt]['='] = State::DoppelpunktIstGleich;
	for (int i = 1; i <= 255; i++) {
		stateMatrix[(int) State::SchraegstrichSternStern][i] =
				State::SchraegStrichStern;
		stateMatrix[(int) State::SchraegStrichStern][i] =
				State::SchraegStrichStern;
	}
	stateMatrix[(int) State::VorwaertsSchraegstrich]['*'] =
			State::SchraegStrichStern;
	stateMatrix[(int) State::SchraegStrichStern]['*'] =
			State::SchraegstrichSternStern;
	stateMatrix[(int) State::SchraegstrichSternStern]['*'] =
			State::SchraegstrichSternStern;
	stateMatrix[(int) State::SchraegstrichSternStern]['/'] =
			State::SchraegstrichSternSternSchraegstrich;
	stateMatrix[(int) State::SchraegStrichStern][' '] =
			State::SchraegStrichStern;
	stateMatrix[(int) State::SchraegStrichStern]['\n'] =
			State::SchraegStrichStern;

	// Einstellen welche Zustaende Finale Zustaende sind.

	finaleStates[(int) State::Start] = false;
	finaleStates[(int) State::Undefined] = false;
	finaleStates[(int) State::Number] = true;
	finaleStates[(int) State::Identifier] = true;
	finaleStates[(int) State::KleinerAls] = true;
	finaleStates[(int) State::GeschweifteKlammerAuf] = true;
	finaleStates[(int) State::GeschweifteKlammerZu] = true;
	finaleStates[(int) State::VorwaertsSchraegstrich] = true;
	finaleStates[(int) State::EckigeKlammerAuf] = true;
	finaleStates[(int) State::EckigeKlammerZu] = true;
	finaleStates[(int) State::UndZeichen] = true;
	finaleStates[(int) State::GroesserAls] = true;
	finaleStates[(int) State::Stern] = true;
	finaleStates[(int) State::Ausrufezeichen] = true;
	finaleStates[(int) State::RundeKlammerAuf] = true;
	finaleStates[(int) State::RundeKlammerZu] = true;
	finaleStates[(int) State::IstGleichZeichen] = true;
	finaleStates[(int) State::Minus] = true;
	finaleStates[(int) State::Plus] = true;
	finaleStates[(int) State::Doppelpunkt] = false;
	finaleStates[(int) State::DoppelpunktIstGleich] = true;
	finaleStates[(int) State::Semikolon] = true;
	finaleStates[(int) State::KleinerDoppelpunkt] = false;
	finaleStates[(int) State::kleinerDoppelpunktGroesser] = true;
	finaleStates[(int) State::SchraegStrichStern] = false;
	finaleStates[(int) State::SchraegstrichSternStern] = false;
	finaleStates[(int) State::SchraegstrichSternSternSchraegstrich] = true;
}

Automat::~Automat() {
}

State Automat::getLastFinalState() {
	return lastFinalState;
}

int Automat::getStepsSinceLastFinalState() {
	return stepsSinceLastFinalState;
}

int Automat::getZeile() {
	return TokenAnfangZeile;
}

int Automat::getSpalte() {
	return TokenAnfangSpalte;
}

bool Automat::testChar(char c) {
	if (currentState == State::Start) {
		TokenAnfangSpalte = spalte;
		TokenAnfangZeile = zeile;
		stepsSinceLastFinalState = 0;
		lastFinalState = State::Start;
	}

	if (c == '\n'
			&& (currentState == State::Start
					|| currentState == State::SchraegStrichStern)) {
		spalte = 1;
		zeile++;
	}

	stepsSinceLastFinalState++;

	if (stateMatrix[(int) currentState][(unsigned short) c]
			!= State::Undefined) {

		currentState = stateMatrix[(int) currentState][(unsigned short) c];

		if (finaleStates[(int) currentState]) {
			spalte += stepsSinceLastFinalState;
			stepsSinceLastFinalState = 0;
			lastFinalState = currentState;
		}
		return true;
	} else {
		if (lastFinalState == State::Start) {
			if (c != '\n') {
				spalte++;
			}
			if ((c != '\n') && (c != ' ') && (c != '\r') && (c != '\t')) {
				lastFinalState = State::Fehler;
			}
		}
		currentState = State::Start;
		return false;
	}
}
