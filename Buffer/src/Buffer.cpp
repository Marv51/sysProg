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

#define BLOCKSIZE 512 // Sollte wahrscheinlich ein vielfaches von 512 sein.
	// alignment to the logical block - The logical block size can be determined using the ioctl(2) BLKSSZGET operation or from the shell using the command: blockdev --getss

Buffer::Buffer(char* input) {
	position = 0;
	int result = posix_memalign((void**) &current_buffer, BLOCKSIZE, BLOCKSIZE);
	if (result != 0) {
		printf("Konnte keinen Speicher für den Puffer bekommen.");
		/*
		TODO: Hier hilfreichere Fehlermeldung und Programm beenden.
		 EINVAL The alignment argument was not a power of two, or was not a multiple of sizeof(void *).
		 ENOMEM There was insufficient memory to fulfill the allocation request.
		*/
		return;
	}
	result = posix_memalign((void**) &prev_buffer, BLOCKSIZE, BLOCKSIZE);
	if (result != 0) {
		printf("Konnte keinen Speicher für den Puffer bekommen.");
		// TODO: siehe Oben.
		return;
	}
	fileHandle = open(input, O_RDONLY | O_DIRECT);
	if (fileHandle == -1) {
		// TODO: bessere Fehlermeldungen: errno 
		/*  EACCES keine Rechte
		    EINVAL The filesystem does not support the O_DIRECT flag.
		    EINVAL Invalid value in flags.
		    ELOOP  Too many symbolic links were encountered in resolving pathname.
		    EMFILE The process already has the maximum number of files open.
		    ENAMETOOLONG pathname was too long.
		    ENFILE The system limit on the total number of open files has been reached.
 		    ENOENT O_CREAT is not set and the named file does not exist. 
 		    ENOMEM Insufficient kernel memory was available.
 		    EOVERFLOW pathname refers to a regular file that is too large to be opened.
		*/
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
		return prev_buffer[BLOCKSIZE + position - 1]; // TODO hier kann unser Programm abstürzen wenn position < 511 ist.
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
