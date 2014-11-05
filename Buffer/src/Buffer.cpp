/*
 * Buffer.cpp
 *
 *  Created on: Sep 26, 2012
 *      Author: knad0001
 */
#include "Buffer.h"
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#define BLOCKSIZE 512

Buffer::Buffer() {
	index = 0;
	int result = posix_memalign((void**)&buffer, BLOCKSIZE, 2*BLOCKSIZE);
	if (result != 0){
		printf("Konnte keinen Speicher für den Puffer bekommen.");
		return;
	}
	fileHandle = open("testfile.txt", O_RDONLY | O_DIRECT);
	if (fileHandle < 0){
		printf("Datei konnte nicht geöffnet werden.");
		return;
	}
	readFromFile(buffer);
}

void Buffer::readFromFile(char* where){
	ssize_t res = read(fileHandle, where, BLOCKSIZE);
	if (res < 0){
		printf("Datei konnte nicht gelesen werden: %s\n", strerror(errno));
		return;
	}
}

Buffer::~Buffer() {
	free(buffer);

	int res = close(fileHandle);
	if (res < 0){
		printf("Datei konnte nicht geschlossen werden.");
		return;
	}
}

char Buffer::getChar() {

	index++;
	return buffer[index - 1];
}

void Buffer::ungetChar() {
	index--;
}

int Buffer::getIndex() {
	return index;
}

bool Buffer::hasCharLeft() {
	return (buffer[index] != '\0');
}
