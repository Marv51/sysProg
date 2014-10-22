/*
 * Automat.cpp
 *
 */

#include "Automat.h"


Automat::Automat() {
	// TODO Auto-generated constructor stub
	lastFinalState = Start;
	stepsSinceLastFinalState = 0;
}

Automat::~Automat() {
	// TODO Auto-generated destructor stub
}

State Automat::getLastFinalState(){
	return lastFinalState;
}

int Automat::getStepsSinceLastFinalState(){
	return stepsSinceLastFinalState;
}

bool Automat::testChar(char c){
	EingabeType typ;
	if(c <= '9' && c >= '0'){
		typ = Zahl;
	}else{
		// Error kein zulässiges Zeichen.
	}

	return true;
}
