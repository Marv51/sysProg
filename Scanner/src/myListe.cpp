/*
 * myListe.cpp
 *
 *  Created on: Nov 5, 2014
 *      Author: marius
 */

#include "myListe.h"
#include <stdlib.h>
#include <cstring>

myListe::myListe() {
	i = 0;
	size = 5;
	list = (char*) malloc(size * sizeof(char));
}

myListe::~myListe() {
	free(list);
}

void myListe::push(char ch) {
	list[i] = ch;
	i++;
	if (i >= size) {
		size *= 2;
		char* tempList = (char*) malloc(size * sizeof(char));
		memcpy(tempList, list, size / 2 * sizeof(char));
		free(list);
		list = tempList;
	}
	list[i] = '\0';
}

char myListe::pop() {
	i--;
	char ret = list[i];
	list[i] = '\0';
	return ret;
}

char* myListe::getString() {
	return list;
}

bool myListe::isEmpty() {
	return i == 0;
}
