/*
 * Buffer.cpp
 *
 *  Created on: Sep 26, 2012
 *      Author: knad0001
 */
#include "Buffer.h"
#include <string.h>

Buffer::Buffer() {
	index = 0;
	strcpy(file, "?HASHen      int\n\n\n\ni <:> 3 + 12;");
}

Buffer::~Buffer() {
}

char Buffer::getChar() {

	index++;
	return file[index - 1];
}

void Buffer::ungetChar() {
	index--;
}

int Buffer::getIndex() {
	return index;
}

bool Buffer::hasCharLeft() {
	return (file[index] != '\0');
}
