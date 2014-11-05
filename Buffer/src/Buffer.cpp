/*
 * Buffer.cpp
 *
 *  Created on: Sep 26, 2012
 *      Author: knad0001
 */
#include "Buffer.h"
#include <string.h>
#include <fcntl.h>
//#include <sys/types.h>
//#include <sys/stat.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#define BLOCKSIZE 512

Buffer::Buffer() {
	index = 0;
	int result = posix_memalign((void**)&buffer, BLOCKSIZE, BLOCKSIZE);
	if (result != 0){
		printf("Konnte keinen Speicher für den Puffer bekommen.");
		return;
	}
	int fileDesc = open("/home/marvin/git/sysProg/Scanner/debug/testfile.txt", O_RDONLY | O_DIRECT);
	if (fileDesc < 0){
		printf("Datei konnte nicht geöffnet werden.");
		return;
	}
	ssize_t res = read(fileDesc, buffer, BLOCKSIZE);
	if (res < 0){
		printf("Datei konnte nicht gelesen werden.");
		return;
	}
	res = close(fileDesc);
	if (res < 0){
		printf("Datei konnte nicht geschlossen werden.");
		return;
	}
	//strcpy(this->file, "?HASHen      int\n\n\n\ni <:> 3 + 12;");
}

Buffer::~Buffer() {
	free(buffer);
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
