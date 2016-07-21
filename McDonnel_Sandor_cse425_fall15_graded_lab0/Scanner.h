#pragma once


#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include "Token.h"

using namespace std;


class Scanner {
public:
	ifstream & ifs;
	Scanner(ifstream & infs);
	int counts;
	vector<string> ss;
	
	vector<vector<string>> testSS;
	vector<vector<Token>> testTT;

	vector<string> vs;
	vector<Token> vt;
	

	bool ifValidToRead();
	Scanner & operator>>(Token & t);
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
	void predicate();
	void body();
	void name();
	void args();
	void symbol();
	void read(Token t, Token::Tokens expected);

	enum Errors {errorExpected, endOfFileCase};
	const string errorTok = "Error with the tokens seen in the file. Incorrect token seen.";
	const string errorTokExpWas = "The expected token was: ";
	const string errorTokExpWas2 = " but the token,string seen were: ";
	const string errorEndEarly = "The file ended before a valid HC could be found";
};