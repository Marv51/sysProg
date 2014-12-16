/*
 * Automat.cpp
 *
 */

#include "Automat.h"

void Automat::addStateToMatrix(State s){
	//Initalisiert jeden Zustand mit nur undefinieren Übergängen
	for (int i = 1; i <= 255; i++){
		stateMatrix[(int)s][i] = State::Undefined;
	}
}

Automat::Automat() {
	lastFinalState = State::Start;
	stepsSinceLastFinalState = 0;
	currentState = State::Start;
	zeile = 1;
	spalte = 1;

	TokenAnfangSpalte = 1;
	TokenAnfangZeile = 1;

	for (int i = (int)State::Number; i != (int)State::SchraegstrichSternSternSchraegstrich; i++){
		addStateToMatrix((State)i);
	}

	stateMatrix[(int)State::Start]['{'] = State::GeschweifteKlammerAuf;
	stateMatrix[(int)State::Start]['}'] = State::GeschweifteKlammerZu;
	stateMatrix[(int)State::Start]['('] = State::RundeKlammerAuf;
	stateMatrix[(int)State::Start][')'] = State::RundeKlammerZu;
	stateMatrix[(int)State::Start]['['] = State::EckigeKlammerAuf;
	stateMatrix[(int)State::Start][']'] = State::EckigeKlammerZu;
	stateMatrix[(int)State::Start]['='] = State::IstGleichZeichen;
	stateMatrix[(int)State::Start]['-'] = State::Minus;
	stateMatrix[(int)State::Start]['+'] = State::Plus;
	stateMatrix[(int)State::Start]['/'] = State::VorwaertsSchraegstrich;
	stateMatrix[(int)State::Start][';'] = State::Semikolon;
	stateMatrix[(int)State::Start]['*'] = State::Stern;
	stateMatrix[(int)State::Start]['&'] = State::UndZeichen;
	stateMatrix[(int)State::Start]['!'] = State::Ausrufezeichen;
	stateMatrix[(int)State::Start]['>'] = State::GroesserAls;
	stateMatrix[(int)State::Start]['<'] = State::KleinerAls;
	stateMatrix[(int)State::Start][':'] = State::Doppelpunkt;

	// Die Uebergangs Matrix erstellen
	for (int i = '0'; i <= '9'; i++){
		stateMatrix[(int)State::Start][i] = State::Number;
		stateMatrix[(int)State::Number][i] = State::Number;
		stateMatrix[(int)State::Identifier][i] = State::Identifier;
	}
	for (int i = 'a'; i <= 'z'; i++){
		stateMatrix[(int)State::Start][i] = State::Identifier;
		stateMatrix[(int)State::Identifier][i] = State::Identifier;
	}
	for (int i = 'A'; i <= 'Z'; i++){
		stateMatrix[(int)State::Start][i] = State::Identifier;
		stateMatrix[(int)State::Identifier][i] = State::Identifier;
	}

	stateMatrix[(int)State::KleinerAls][':'] = State::KleinerDoppelpunkt;
	stateMatrix[(int)State::KleinerDoppelpunkt]['>'] = State::kleinerDoppelpunktGroesser;
	stateMatrix[(int)State::Doppelpunkt]['='] = State::DoppelpunktIstGleich;
	for (int i = 1; i <= 255; i++){
		stateMatrix[(int)State::SchraegstrichSternStern][i] = State::SchraegStrichStern;
		stateMatrix[(int)State::SchraegStrichStern][i] = State::SchraegStrichStern;
	}
	stateMatrix[(int)State::VorwaertsSchraegstrich]['*'] = State::SchraegStrichStern;
	stateMatrix[(int)State::SchraegStrichStern]['*'] = State::SchraegstrichSternStern;
	stateMatrix[(int)State::SchraegstrichSternStern]['*'] = State::SchraegstrichSternStern;
	stateMatrix[(int)State::SchraegstrichSternStern]['/'] = State::SchraegstrichSternSternSchraegstrich;



	// Einstellen welche Zustaende Finale Zustaende sind.
	
	//TODO: setzte alle finaleStates auf false und dann nur die auf true die final sind.
	finaleStates[(int)State::Start] = false;
	finaleStates[(int)State::Undefined] = false;
	finaleStates[(int)State::Number] = true;
	finaleStates[(int)State::Identifier] = true;
	finaleStates[(int)State::KleinerAls] = true;
	finaleStates[(int)State::GeschweifteKlammerAuf] = true;
	finaleStates[(int)State::GeschweifteKlammerZu] = true;
	finaleStates[(int)State::VorwaertsSchraegstrich] = true;
	finaleStates[(int)State::EckigeKlammerAuf] = true;
	finaleStates[(int)State::EckigeKlammerZu] = true;
	finaleStates[(int)State::UndZeichen] = true;
	finaleStates[(int)State::GroesserAls] = true;
	finaleStates[(int)State::Stern] = true;
	finaleStates[(int)State::Ausrufezeichen] = true;
	finaleStates[(int)State::RundeKlammerAuf] = true;
	finaleStates[(int)State::RundeKlammerZu] = true;
	finaleStates[(int)State::IstGleichZeichen] = true;
	finaleStates[(int)State::Minus] = true;
	finaleStates[(int)State::Plus] = true;
	finaleStates[(int)State::Doppelpunkt] = false;
	finaleStates[(int)State::DoppelpunktIstGleich] = true;
	finaleStates[(int)State::Semikolon] = true;
	finaleStates[(int)State::KleinerDoppelpunkt] = false;
	finaleStates[(int)State::kleinerDoppelpunktGroesser] = true;
	finaleStates[(int)State::SchraegStrichStern] = false;
	finaleStates[(int)State::SchraegstrichSternStern] = false;
	finaleStates[(int)State::SchraegstrichSternSternSchraegstrich] = true;
}

Automat::~Automat() {
}


//TODO: Diese Funktion wird nicht gebraucht, wenn Start ein finalerZustand ist, wie es sein sollte.
//	Clean kann man einfach machen wenn man im Start Zustand ein Zeichen testet.
void Automat::clean(){
	stepsSinceLastFinalState = 0;
	currentState = State::Start;
	lastFinalState = State::Start;
}

State Automat::getLastFinalState(){
	return lastFinalState;
}

//TODO: reicht hier wirklich die Spalte zurück Methode? Was passiert wenn wir Zeilen zurüück gehen sollten?
void Automat::spalteZurueck(){
	spalte--;
}

int Automat::getStepsSinceLastFinalState(){
	return stepsSinceLastFinalState;
}

int Automat::getZeile(){
	return TokenAnfangZeile;
}

int Automat::getSpalte(){
	return TokenAnfangSpalte;
}

bool Automat::testChar(char c){
	if (currentState == State::Start){
			TokenAnfangSpalte = spalte;
			TokenAnfangZeile = zeile;
	}
	if (c != '\n'){
		spalte++;
	} else {
		spalte = 1;
		zeile++;
	}
	
	// TODO: hier könnte man doch auch einfach die Übergänge entsprechend definieren, oder?
	if (currentState != State::SchraegStrichStern && (c == ' ' || c == '\n')){
		return false;
	}
	//TODO: Man könnte hier stepsSinceLastFinalState auch einfach immer erhöhen, außerhalb von all den ifs
	
	if (stateMatrix[(int)currentState][(unsigned short)c] != State::Undefined){
		currentState = stateMatrix[(int)currentState][(unsigned short)c];
		if (finaleStates[(int)currentState]){
			stepsSinceLastFinalState = 0;
			lastFinalState = currentState;
		} else {
			stepsSinceLastFinalState++;
		}
		return true;
	}
	else{
		currentState = State::Start;
		stepsSinceLastFinalState++;
		return false;
	}

	return true;
}
