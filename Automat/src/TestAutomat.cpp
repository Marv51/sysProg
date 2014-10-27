#include "Automat.h"
#include <stdio.h>

int main (int argc, char* argv[]){
	printf("Hallo\n");
	Automat* automat;

	automat = new Automat();

	printf(automat->testChar('/')? "true\n" : "false\n");
	printf(automat->testChar('*')? "true\n" : "false\n");
	printf(automat->testChar('*')? "true\n" : "false\n");
	printf(automat->testChar('*')? "true\n" : "false\n");
	printf(automat->testChar('/')? "true\n" : "false\n");
	//printf(automat->testChar('>')? "true\n" : "false\n");
	printf("Finale State: %i\n",automat->getLastFinalState());
	printf("Schritte seit dem: %i\n",automat->getStepsSinceLastFinalState());
	printf("Zustand: %i\n",SchraegstrichSternSternSchraegstrich);
	printf("End\n");

}
