// lab2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"


/* Authors: Adam Sandor, David Mcdonnel
Lab 0
adam.sandor@wustl.edu
dmcdonnel@wustl.edu
Purpose:
This file runs the recursive descent parsers and the scanner to
parse an input file and output the parsed form to the output
file.
*/

#include "parser.h"
#include "Scanner.h"
#include "SymbolTable.h"

#include "SemAnaFun.h"

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <memory>
#include <algorithm>
using namespace std;


RecDec2 rd2;
extern ofstream os;

void parser(string in, string out) {

	ifstream inf(in);
	ifstream ll(in);
	ofstream outfile(out);
	
	

	if (!inf.is_open()) {
		cout << errorIn << endl;
		throw inputFile;
		return;
	}
	if (!outfile.is_open()) {
		cout << errorOut << endl;
		throw outputFile;
		return;
	}

	Scanner sc(inf);
	string test;

	for (string line; getline(ll, line);) {
		istringstream iss(line);
		copy(istream_iterator<string>(iss), istream_iterator<string>(), back_inserter(sc.ss));
	}

	while (!inf.eof()) {
		Token testy;
		shared_ptr<Token> spt = make_shared<Token>(testy);
		sc >> spt;

	}

	bool hcb = false;

	//loop through the vector of tokens until no more.
	//start the recursive descent parser in each loop. 
	//In the loop of vt size, go over until sc.counts which represents tokens until 
	//it covers a complete HC. 
	vector<string> forSymsLater;
	set<int> numLabelsOrder;
	set<string> labLabelsOrder;
	vector<string> labLabelsVect;

	while ((sc.vt.size() > one) && sc.ifValidToRead()) {
		string file = emptyString;
		bool hcb = sc.hc( outfile);
		for (unsigned int i = counterZero; i < sc.counts; ++i) {
			if (hcb) {


				if (sc.vt[counterZero]->tok == Token::Tokens::Number || sc.vt[counterZero]->tok == Token::Tokens::Label) {
					forSymsLater.push_back(sc.vt[counterZero]->tokstr);
					if (sc.vt[counterZero]->tok == Token::Tokens::Number) {
						int sn = atoi(sc.vt[counterZero]->tokstr.c_str());
						numLabelsOrder.insert(sn);
					}
					else {
						labLabelsOrder.insert(sc.vt[counterZero]->tokstr);
					}
				}
				file += sc.vt[counterZero]->tokstr + spaceString;
				sc.vt.erase(sc.vt.begin());
				//remove tokens already looked at.
			}
		}
		sc.counts = counterZero;
		if (hcb) {
			//call semantic analysis function here to
			//look at all things in the forsymslater vector that are also in 
			vector<SymTabObj> finals;
			finals.insert(finals.end(), sc.symTab.getSymsValid().begin(), sc.symTab.getSymsValid().end());
			sc.symTab.getSymsValid().clear();
			rd2.semans.insert(rd2.semans.end(), finals.begin(), finals.end());

			rd2.HC();

			//reset for next HC
			finals.clear();
			rd2.counts2 = counterZero;
			rd2.semans.clear();

			//change this stuff for printing out the AST stuff. 
			outfile << outputHC << endl;
			outfile << rd2.output << endl;

			rd2.output = emptyString;
		}
	}



	for (string sl : labLabelsOrder) {
		labLabelsVect.push_back(sl);
	}
	sort(labLabelsVect.begin(), labLabelsVect.end(), compareString);
	outfile << outputLabNums << endl;
	for (string s : labLabelsVect) {
		outfile << s << endl;
	}

	for (int sn : numLabelsOrder) {
		outfile << sn << endl;
	}

}


bool compareString(string s1, string s2) {
	int size = counterZero;
	if (s1.size() >= s2.size()) {
		size = s2.size();
	}
	else {
		size = s1.size();
	}
	for (int c = counterZero; c < size; c++) {
		if (tolower(s1[c]) < tolower(s2[c])) {
			return true;
		}
		else if (tolower(s1[c]) > tolower(s2[c])) {
			return false;
		}
	}
	return false;
}


int main(int argc, char* argv[])
{

	if (argc < numArgsThree) {
		//error messages!
		cout << errorNotEnough << endl;
		return tooFewReturn;
	}
	else if (argc > numArgsThree) {
		cout << errorTooMany << endl;
		return tooManyReturn;
	}
	try {
		parser(argv[inputFileIndex], argv[outputFileIndex]);
	}
	catch (errors e) {
		if (e == errors::inputFile) {
			cout << errorIn << endl;
			return inputFileBadReturn;
		}
		else if (e == errors::outputFile) {
			cout << errorOut << endl;
			return outputFileBadReturn;
		}
	}

	return correctReturn;
}

