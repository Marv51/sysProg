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
	switch (c){
	case 'a':
	case 'b':
	case 'c':
	case 'd':
	case 'e':
	case 'f':
	case 'g':
	case 'h':
	case 'i':
	case 'j':
	case 'k':
	case 'l':
	case 'm':
	case 'n':
	case 'o':
	case 'p':
	case 'q':
	case 'r':
	case 's':
	case 't':
	case 'u':
	case 'v':
	case 'w':
	case 'x':
	case 'y':
	case 'z':
		typ = Buchstabe;
		break;
	case '0':
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9':
		typ = Zahl;
		break;
	case '+':
		typ = Plus;
		break;
	default:
		typ = Error;
	}

	return true;
}
