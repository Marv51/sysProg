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
	Buffer(char* input);
	virtual ~Buffer();
	char getChar();
	void ungetChar(/*int wieviele -> nicht benötigt*/);
	int getIndex(); // nur Debug
	bool hasCharLeft();
private: 
	int index;
	char *current_buffer;
	char *prev_buffer;
	int fileHandle;
	void readFromFile(char* where);
};

#endif /* BUFFER_H_ */
