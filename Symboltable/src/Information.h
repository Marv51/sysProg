/*
 * Information.h
 *
 *  Created on: Nov 6, 2014
 *      Author: marius
 */

#ifndef SYMBOLTABLE_SRC_INFORMATION_H_
#define SYMBOLTABLE_SRC_INFORMATION_H_

class Information {
public:
	Information(char* lex, int k);
	virtual ~Information();
	char* getLexem();
	void setLexem(char* lex);
	bool compareLexem(char* lex);
	Information* getNextInfo();
	void setNextInfo(Information* info);
	int getKey();
private:
	char* lexem;
	Information* nextInfo;
	int key;
};

#endif /* SYMBOLTABLE_SRC_INFORMATION_H_ */
