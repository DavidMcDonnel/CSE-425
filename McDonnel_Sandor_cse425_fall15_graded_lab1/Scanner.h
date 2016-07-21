#pragma once
/*Authors: Adam Sandor, David Mcdonnel
 Lab 0
 adam.sandor@wustl.edu
 dmcdonnel@wustl.edu
 Purpose:
	THis file has the Scanner class. The Scanner calls the first
	recursive descent parser which determines if a valid HC is being read.
*/
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include "Token.h"
#include "SymbolTable.h"

using namespace std;


class Scanner {
public:
	ifstream & ifs;
	Scanner(ifstream & infs);
	unsigned int counts;
	vector<string> ss;
	vector<string> vs;
	vector<shared_ptr<Token>> vt;

	SymTab symTab;

	bool ifValidToRead();
	
	Scanner & operator>>(shared_ptr<Token> spt);

	bool findAlpha(string in);
	bool findAnd(string in);
	bool findSep(string in);
	bool findLP(string in);
	bool findRP(string in);
	bool findComma(string in);
	bool findNum(string in);

	
	bool hc(); //start rec dec parser
	//helper methods for recursive descent parser
	void head();
	void predicate(bool isHeadP);
	void body();
	void name(bool isHeadPN);
	void args();
	void symbol();
	void read(shared_ptr<Token> t, Token::Tokens expected);

	enum Errors { errorExpected, endOfFileCase };
	const string errorTok = "Error with the tokens seen in the file. Incorrect token seen.";
	const string errorTokExpWas = "The expected token was: ";
	const string errorTokExpWas2 = " but the token,string seen were: ";
	const string errorEndEarly = "The file ended before a valid HC could be found";
	const int counterZero = 0;
	const int one = 1;
	const string andS = "^";
	const string commaS = ",";
	const string lpS = "(";
	const string rpS = ")";
	const string sepS = ":-";

};