#include "Symboltable.h"
#include <stdint.h>
#include <stdio.h>

int main(int argc, char **argv) {

	printf("Symboltabelle Test:\n");

	Symboltable* symboltable;

	symboltable = new Symboltable();

	uint16_t s1 = symboltable->newInfo("hallo");
	uint16_t s2 = symboltable->newInfo("welt");
	uint16_t s3 = symboltable->newInfo("hallo");
	uint16_t s4 = symboltable->newInfo("was");
	uint16_t s5 = symboltable->newInfo("gehtn");

	printf("s1: %s key: %i\n", symboltable->getInfo(s1)->getLexem(), s1);
	printf("s2: %s key: %i\n", symboltable->getInfo(s2)->getLexem(), s2);
	printf("s3: %s key: %i\n", symboltable->getInfo(s3)->getLexem(), s3);
	printf("s4: %s key: %i\n", symboltable->getInfo(s4)->getLexem(), s4);
	printf("s5: %s key: %i\n", symboltable->getInfo(s5)->getLexem(), s5);
}
