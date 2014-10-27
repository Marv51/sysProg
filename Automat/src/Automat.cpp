/*
 * Automat.cpp
 *
 */

#include "Automat.h"

void Automat::addStateToMatrix(State s){
	//Initalisiert jeden Zustand mit nur undefinieren Übergängen
	for (int i = 1; i <= 255; i++){
		stateMatrix[s][i] = Undefined;
	}
}

Automat::Automat() {
	lastFinalState = Start;
	stepsSinceLastFinalState = 0;
	currentState = Start;
	zeile = 0;
	spalte = 0;

	for (int i = Number; i != SchraegstrichSternSternSchraegstrich; i++){
		addStateToMatrix((State)i);
	}

	stateMatrix[Start]['{'] = GeschweifteKlammerAuf;
	stateMatrix[Start]['}'] = GeschweifteKlammerZu;
	stateMatrix[Start]['('] = RundeKlammerAuf;
	stateMatrix[Start][')'] = RundeKlammerZu;
	stateMatrix[Start]['['] = EckigeKlammerAuf;
	stateMatrix[Start][']'] = EckigeKlammerZu;
	stateMatrix[Start]['='] = IstGleichZeichen;
	stateMatrix[Start]['-'] = Minus;
	stateMatrix[Start]['+'] = Plus;
	stateMatrix[Start]['/'] = VorwaertsSchraegstrich;
	stateMatrix[Start][';'] = Semikolon;
	stateMatrix[Start]['*'] = Stern;
	stateMatrix[Start]['&'] = UndZeichen;
	stateMatrix[Start]['!'] = Ausrufezeichen;
	stateMatrix[Start]['>'] = GroesserAls;
	stateMatrix[Start]['<'] = KleinerAls;
	stateMatrix[Start][':'] = Doppelpunkt;

	// Die Uebergangs Matrix erstellen
	for (int i = 0; i <= 9; i++){
		stateMatrix[Start][i] = Number;
		stateMatrix[Number][i] = Number;
		stateMatrix[Identifier][i] = Identifier;
	}
	for (int i = 'a'; i <= 'z'; i++){
		stateMatrix[Start][i] = Identifier;
		stateMatrix[Identifier][i] = Identifier;
	}
	for (int i = 'A'; i <= 'Z'; i++){
		stateMatrix[Start][i] = Identifier;
		stateMatrix[Identifier][i] = Identifier;
	}

	stateMatrix[KleinerAls][':'] = KleinerDoppelpunkt;
	stateMatrix[KleinerDoppelpunkt]['>'] = kleinerDoppelpunktGroesser;
	stateMatrix[Doppelpunkt]['='] = DoppelpunktIstGleich;
	for (int i = 1; i <= 255; i++){
		stateMatrix[SchraegstrichSternStern][i] = SchraegStrichStern;
		stateMatrix[SchraegStrichStern][i] = SchraegstrichSternStern;
	}
	stateMatrix[VorwaertsSchraegstrich]['*'] = SchraegStrichStern;
	stateMatrix[SchraegStrichStern]['*'] = SchraegstrichSternStern;
	stateMatrix[SchraegstrichSternStern]['*'] = SchraegstrichSternStern;
	stateMatrix[SchraegstrichSternStern]['/'] = SchraegstrichSternSternSchraegstrich;


	// Einstellen welche Zustaende Finale Zustaende sind.
	finaleStates[Start] = false;
	finaleStates[Undefined] = false;
	finaleStates[Number] = true;
	finaleStates[Identifier] = true;
	finaleStates[KleinerAls] = true;
	finaleStates[GeschweifteKlammerAuf] = true;
	finaleStates[GeschweifteKlammerZu] = true;
	finaleStates[VorwaertsSchraegstrich] = true;
	finaleStates[EckigeKlammerAuf] = true;
	finaleStates[EckigeKlammerZu] = true;
	finaleStates[UndZeichen] = true;
	finaleStates[GroesserAls] = true;
	finaleStates[Stern] = true;
	finaleStates[Ausrufezeichen] = true;
	finaleStates[RundeKlammerAuf] = true;
	finaleStates[RundeKlammerZu] = true;
	finaleStates[IstGleichZeichen] = true;
	finaleStates[Minus] = true;
	finaleStates[Plus] = true;
	finaleStates[Doppelpunkt] = false;
	finaleStates[DoppelpunktIstGleich] = true;
	finaleStates[Semikolon] = true;
	finaleStates[KleinerDoppelpunkt] = false;
	finaleStates[kleinerDoppelpunktGroesser] = true;
	finaleStates[SchraegStrichStern] = false;
	finaleStates[SchraegstrichSternStern] = false;
	finaleStates[SchraegstrichSternSternSchraegstrich] = true;
}

Automat::~Automat() {
}

State Automat::getLastFinalState(){
	return lastFinalState;
}

int Automat::getStepsSinceLastFinalState(){
	return stepsSinceLastFinalState;
}

int Automat::getZeile(){
	return zeile;
}

int Automat::getSpalte(){
	return spalte;
}

bool Automat::testChar(char c){
	if (c != '\n'){
		spalte++;
	} else {
		spalte = 0;
		zeile++;
	}

	if (stateMatrix[currentState][(unsigned short)c] != Undefined){
		currentState = stateMatrix[currentState][(unsigned short)c];
		if (finaleStates[currentState]){
			stepsSinceLastFinalState = 0;
			lastFinalState = currentState;
		} else {
			stepsSinceLastFinalState++;
		}
		return true;
	}
	else{
		currentState = Start;
		stepsSinceLastFinalState++;
		return false;
	}

	return true;
}
