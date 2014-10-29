/*
 * Buffer.h
 *
 *  Created on: Sep 26, 2012
 *      Author: knad0001
 */

#ifndef BUFFER_H_
#define BUFFER_H_

class Buffer {
public:
	Buffer();
	virtual ~Buffer();
	char getChar();
	void ungetChar(/*int wieviele -> nicht benötigt*/);
	int getIndex(); // nur Debug
private: 
	int index;
	char file[100];
};

#endif /* BUFFER_H_ */
