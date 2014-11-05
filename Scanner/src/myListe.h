/*
 * myListe.h
 *
 *  Created on: Nov 5, 2014
 *      Author: marius
 */

#ifndef SCANNER_SRC_MYLISTE_H_
#define SCANNER_SRC_MYLISTE_H_

class myListe {
public:
	myListe();
	virtual ~myListe();
	void push(char ch);
	char pop();
	char* getString();
	bool isEmpty();
private:
	char* list;
	int i;
	int size;
};

#endif /* SCANNER_SRC_MYLISTE_H_ */
