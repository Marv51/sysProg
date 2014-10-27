/*
 * Buffer.cpp
 *
 *  Created on: Sep 26, 2012
 *      Author: knad0001
 */

#include "Buffer.h"

Buffer::Buffer() {
	// TODO Auto-generated constructor stub
	Buffer::index = 0;
	for (int i = 0; i < 11; i++){
		file[i] = "Hallo_Welt\n"[i];
	}
}

Buffer::~Buffer() {
	// TODO Auto-generated destructor stub
}

char Buffer::getChar(){

	index++;
	return file[index - 1];
}

void Buffer::ungetChar(int wieviele){
	index -= wieviele;
}

int Buffer::getIndex(){
	return index;
}