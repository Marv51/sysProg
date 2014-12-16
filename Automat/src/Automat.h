/*
 * Automat.h
 *
 *  Created on: Jul 5, 2012
 *      Author: knad0001
 */

#ifndef Automat_H_
#define Automat_H_

enum class State {
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
private:
	State lastFinalState;
	State currentState;
	int stepsSinceLastFinalState;
	State stateMatrix[(int)State::Length][256];
	bool finaleStates[(int)State::Length];
	int zeile;
	int spalte;
	int TokenAnfangZeile;
	int TokenAnfangSpalte;
};

#endif /* Automat_H_ */
