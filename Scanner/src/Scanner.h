/*
 * Scanner.h
 *
 *  Created on: Sep 26, 2012
 *      Author: knad0001
 */


#ifndef SCANNER_H_
#define SCANNER_H_

class Scanner {
public:
	Scanner();
	virtual ~Scanner();
	void nextToken(); // TODO Token zurückliefern

private:
	Automat* automat;
	Buffer* buffer;
};

#endif /* SCANNER_H_ */
