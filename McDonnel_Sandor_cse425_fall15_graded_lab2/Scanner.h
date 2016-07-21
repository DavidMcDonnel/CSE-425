#pragma once
/*Authors: Adam Sandor, David Mcdonnel
Lab 0
adam.sandor@wustl.edu
dmcdonnel@wustl.edu
Purpose:
THis file has the Scanner class. The Scanner calls the first
recursive descent parser which determines if a valid HC is being read.

Lab2 update:
This file has some helpful constants and new methods 
for predicate matching and unification of predicates.
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


	//bool hc(); //start rec dec parser
	bool hc(ofstream & os);
	//helper methods for recursive descent parser
	//void head();
	void head(HCObj & hc);
	//void predicate(bool isHeadP);
	void predicate(bool isHeadP, HBObj & hbo);
	//void body();
	void body(HCObj & hc);
	//void name(bool isHeadPN);
	void name(bool isHeadPN, PredObj & po);
	void args(PredObj & po);
	//void symbol();
	void symbol(PredObj & po);
	void read(shared_ptr<Token> t, Token::Tokens expected);
	int checkIfSymbolExists(shared_ptr<Token> symToCheck);
	
	

	enum Errors { errorExpected, endOfFileCase };


};


const string errorTok = "Error with the tokens seen in the file. Incorrect token seen.";
const string errorTokExpWas = "The expected token was: ";
const string errorTokExpWas2 = " but the token,string seen were: ";
const string errorEndEarly = "The file ended before a valid HC could be found";
const string predicateC = "The C/earlier Predicate is:";
const string predicateD = "The D/later predicate is:";
const string subListPrint = "The required substitution list is: (value being changed, new value)";
const string resultingPred = "The predicate that results from unification is:";
const int counterZeroScan = 0;
const int oneScan = 1;
const string andS = "^";
const string commaS = ",";
const string lpS = "(";
const string rpS = ")";
const string sepS = ":-";
const string space = " ";

bool isNumber(string in);
bool isAlpha(string in);
void unify(string & nameC, vector<string> & symsC, string & nameD, vector<string> & symsD, ofstream & os);
bool samePreds(shared_ptr<PredObj> & p1, shared_ptr<PredObj> & p2);
void predMatching(ofstream & os);