/*
 * Buffer.cpp
 *
 *  Created on: Sep 26, 2012
 *      Author: knad0001
 */
#include "Buffer.h"

Buffer::Buffer() {
	index = 0;
	for (int i = 0; i < 30; i++){
		file[i] = "HASHDSHDSDHSDH    int i <:> 3 + 12;   \n"[i];
	}
}

Buffer::~Buffer() {
}

char Buffer::getChar(){

	index++;
	return file[index - 1];
}

void Buffer::ungetChar(){
	index --;
}

int Buffer::getIndex(){
	return index;
}
