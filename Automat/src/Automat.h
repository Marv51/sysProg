/*
 * Automat.h
 *
 *  Created on: Jul 5, 2012
 *      Author: knad0001
 */

#ifndef Automat_H_
#define Automat_H_

enum State {
	Undefined,
	Start,
	Number,
	Identifier,
	KleinerAls,
	GeschweifteKlammerAuf,
	GeschweifteKlammerZu,
	VorwaertsSchraegstrich,
	EckigeKlammerAuf,
	EckigeKlammerZu,
	UndZeichen,
	GroesserAls,
	Stern,
	Ausrufezeichen,
	RundeKlammerAuf,
	RundeKlammerZu,
	IstGleichZeichen,
	Minus,
	Plus,
	Doppelpunkt,
	DoppelpunktIstGleich,
	Semikolon,
	KleinerDoppelpunkt,
	kleinerDoppelpunktGroesser,
	SchraegStrichStern,
	SchraegstrichSternStern,
	SchraegstrichSternSternSchraegstrich,
	Fehler,
	Length // Zustand um die Anzahl der definierten Zustände zu erkennen muss immer der letzte Zustand sein.
};

class Automat {
public:
	Automat();
	virtual ~Automat();
	State getLastFinalState();
	int getStepsSinceLastFinalState();
	bool testChar(char c);
	int getZeile();
	int getSpalte();
	void clean();
	void spalteZurueck();
private:
	void addStateToMatrix(State s);
	State lastFinalState;
	State currentState;
	int stepsSinceLastFinalState;
	State stateMatrix[50][256]; //TODO 50 sollte durch State.Length ersetzt werden
	bool finaleStates[50]; //TODO 50 sollte durch State.Length ersetzt werden
	int zeile;
	int spalte;
	int TokenAnfangZeile;
	int TokenAnfangSpalte;
};

#endif /* Automat_H_ */
