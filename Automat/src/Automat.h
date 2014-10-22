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
	KleinerAls
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
	State stateMatrix[20][256];
	bool finaleStates[20];
	int zeile;
	int spalte;
};

#endif /* Automat_H_ */
