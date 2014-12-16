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
	zeile = 1;
	spalte = 1;

	TokenAnfangSpalte = 1;
	TokenAnfangZeile = 1;

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
	for (int i = '0'; i <= '9'; i++){
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
		stateMatrix[SchraegStrichStern][i] = SchraegStrichStern;
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


//TODO: Diese Funktion wird nicht gebraucht, wenn Start ein finalerZustand ist, wie es sein sollte.
//	Clean kann man einfach machen wenn man im Start Zustand ein Zeichen testet.
void Automat::clean(){
	stepsSinceLastFinalState = 0;
	currentState = Start;
	lastFinalState = Start;
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
	if (currentState == Start){
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
	if (currentState != SchraegStrichStern && (c == ' ' || c == '\n')){
		return false;
	}
	//TODO: Man könnte hier stepsSinceLastFinalState auch einfach immer erhöhen, außerhalb von all den ifs
	
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
