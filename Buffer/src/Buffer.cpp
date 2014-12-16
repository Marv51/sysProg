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

#define BLOCKSIZE 512 // Sollte wahrscheinlich ein vielfaches von 512 sein.

Buffer::Buffer(char* input) {
	position = 0;
	int result = posix_memalign((void**) &current_buffer, BLOCKSIZE, BLOCKSIZE);
	if (result != 0) {
		printf("Konnte keinen Speicher für den Puffer bekommen.");
		return;
	}
	result = posix_memalign((void**) &prev_buffer, BLOCKSIZE, BLOCKSIZE);
	if (result != 0) {
		printf("Konnte keinen Speicher für den Puffer bekommen.");
		return;
	}
	fileHandle = open(input, O_RDONLY | O_DIRECT);
	if (fileHandle < 0) {
		printf("Datei konnte nicht geöffnet werden.");
		return;
	}
	readFromFile(current_buffer);
}

void Buffer::readFromFile(char* where) {
	ssize_t res = read(fileHandle, where, BLOCKSIZE);
	if (res < 0) {
		printf("Datei konnte nicht gelesen werden: %s\n", strerror(errno));
		return;
	}
}

Buffer::~Buffer() {
	free(current_buffer);
	free(prev_buffer);

	int res = close(fileHandle);
	if (res < 0) {
		printf("Datei konnte nicht geschlossen werden.");
		return;
	}
}

char Buffer::getChar() {
	if (position < 0) {
		position++;
		return prev_buffer[BLOCKSIZE + position - 1];
	}
	if (position >= BLOCKSIZE) {
		free(prev_buffer);	//TODO: Hier sollten wir den Speicher nur mit memset leeren und nicht jedes mal neuen Speicher anfordern.
		prev_buffer = current_buffer;
		int result = posix_memalign((void**) &current_buffer, BLOCKSIZE,
		BLOCKSIZE);
		if (result != 0) {
			printf("Konnte keinen Speicher für den Puffer bekommen.");
		}
		readFromFile(current_buffer);
		position = 0;
	}
	position++;
	return current_buffer[position - 1];
}

void Buffer::ungetChar() {
	position--;
}

int Buffer::getIndex() {
	return position;
}

bool Buffer::hasCharLeft() {
	if (position <= 0) {
		return true;
	}
	char nextChar = getChar();
	ungetChar();
	return (nextChar != '\0');
}
