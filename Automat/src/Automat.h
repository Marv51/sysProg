/*
 * Automat.h
 *
 *  Created on: Jul 5, 2012
 *      Author: knad0001
 */

#ifndef Automat_H_
#define Automat_H_

enum State
{
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
	SchraegstrichSternSternSchraegstrich
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
	void addStateToMatrix(State s);
	State lastFinalState;
	State currentState;
	int stepsSinceLastFinalState;
	State stateMatrix[50][256];
	bool finaleStates[50];
	int zeile;
	int spalte;
};

#endif /* Automat_H_ */
