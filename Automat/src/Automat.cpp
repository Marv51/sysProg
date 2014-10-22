/*
 * Automat.cpp
 *
 */

#include "Automat.h"


Automat::Automat() {
	lastFinalState = Start;
	stepsSinceLastFinalState = 0;
	currentState = Start;
	zeile = 0;
	spalte = 0;

	// Die Uebergangs Matrix erstellen
	for (int i = 0; i <= 9; i++){
		stateMatrix[Start][i] = Number;
		stateMatrix[Number][i] = Number;
		stateMatrix[Identifier][i] = Identifier;
	}
	for (int i = 'a'; i <= 'z'; i++){
		stateMatrix[Number][i] = Undefined;
		stateMatrix[Start][i] = Identifier;
		stateMatrix[Identifier][i] = Identifier;
	}
	for (int i = 'A'; i <= 'Z'; i++){
		stateMatrix[Number][i] = Undefined;
		stateMatrix[Start][i] = Identifier;
		stateMatrix[Identifier][i] = Identifier;
	}
	stateMatrix[Start]['<'] = KleinerAls;
	stateMatrix[Identifier]['<'] = Undefined;
	stateMatrix[Number]['<'] = Undefined;



	// Einstellen welche Zustaende Finale Zustaende sind.
	finaleStates[Start] = false;
	finaleStates[Number] = true;
	finaleStates[Undefined] = false;
	finaleStates[Identifier] = true;
	finaleStates[KleinerAls] = true;
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
