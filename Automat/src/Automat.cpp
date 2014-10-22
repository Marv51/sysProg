/*
 * Automat.cpp
 *
 */

#include "Automat.h"


Automat::Automat() {
	lastFinalState = Start;
	stepsSinceLastFinalState = 0;
	currentState = Start;
}

Automat::~Automat() {
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
	}else if((c <= 'Z' && c >= 'A') || (c <= 'z' && c >= 'a')){
		typ = Buchstabe;
	}else if(c == '+'){
		typ = Plus;
	}else if(c == '-'){
		typ = Minus;
	}else if(c == ' '){
		typ = Leerzeichen;
	}else if(c == '='){
		typ = Gleich;
	}else if(c == '.'){
		typ = Punkt;
	}else{
		// Error kein zulässiges Zeichen.
	}

	return true;
}
