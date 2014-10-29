/*
 * Scanner.h
 *
 *  Created on: Sep 26, 2012
 *      Author: knad0001
 */

#include "../../Automat/src/Automat.h"
#include "../../Buffer/src/Buffer.h"
#include "Token.h"

#ifndef SCANNER_H_
#define SCANNER_H_

class Scanner {
public:
	Scanner();
	virtual ~Scanner();
	Token* nextToken();

private:
	Automat* automat;
	Buffer* buffer;
	char word[100]; // TODO durch Stack/Liste ersetzen?
};

#endif /* SCANNER_H_ */
