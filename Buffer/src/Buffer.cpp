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

/*
 "The thing that has always disturbed me about O_DIRECT is that
 the whole interface is just stupid, and was probably designed
 by a deranged monkey on some serious mind-controlling
 substances."—Linus
 */

const int BLOCKSIZE { 512 }; // Sollte wahrscheinlich ein vielfaches von 512 sein.
// alignment to the logical block - The logical block size can be determined using the ioctl(2) BLKSSZGET operation or from the shell using the command: blockdev --getss

Buffer::Buffer(char* input) {
	position = 0;
	int result = posix_memalign((void**) &current_buffer, BLOCKSIZE, BLOCKSIZE);
	if (result != 0) {
		printf("Konnte keinen Speicher für den Puffer bekommen: %s\n", strerror(errno));
		exit(1);
	}
	result = posix_memalign((void**) &prev_buffer, BLOCKSIZE, BLOCKSIZE);
	if (result != 0) {
		printf("Konnte keinen Speicher für den Puffer bekommen: %s\n", strerror(errno));
		exit(1);
	}
	fileHandle = open(input, O_RDONLY | O_DIRECT);
	if (fileHandle == -1) {
		printf("Datei konnte nicht geöffnet werden: %s\n", strerror(errno));
		exit(1);
	}
	readFromFile(current_buffer);
}

void Buffer::readFromFile(char* where) {
	ssize_t res = read(fileHandle, where, BLOCKSIZE);
	if (res == -1) {
		printf("Datei konnte nicht gelesen werden: %s\n", strerror(errno));
		exit(1);
	}
}

Buffer::~Buffer() {
	free(current_buffer);
	free(prev_buffer);

	int res = close(fileHandle);
	if (res == -1) {
		printf("Datei konnte nicht geschlossen werden.");
		exit(1);
	}
}

char Buffer::getChar() {
	if (position < 0) {
		position++;
		if (position < -511){
			printf("Mehr als 512 Schritte zurück werden nicht unterstützt.");
			exit(1);
		}
		return prev_buffer[BLOCKSIZE + position - 1];
	}
	if (position >= BLOCKSIZE) {
		auto temp_buffer = prev_buffer;
		prev_buffer = current_buffer;
		current_buffer = temp_buffer;
		memset(current_buffer, 0, BLOCKSIZE);
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
	char nextChar;
	auto counter = 0;
	do {
		nextChar = getChar();
		counter++;
	} while (nextChar == ' ' || nextChar == '\n' || nextChar == '\r');
	for (auto i = 0; i < counter; i++){
		ungetChar();
	}
	return (nextChar != '\0');
}
