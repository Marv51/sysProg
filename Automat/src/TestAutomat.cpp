#include "Automat.h"
#include <stdio.h>

int main (int argc, char* argv[]){

	Automat* automat;

	automat = new Automat();

	int status = automat->getLastFinalState();
	int steps = automat->getStepsSinceLastFinalState();
	printf("%i\n", status);
	printf("%i\n", steps);


}
