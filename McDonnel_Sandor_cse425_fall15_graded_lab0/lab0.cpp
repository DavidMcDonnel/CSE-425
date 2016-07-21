// lab0.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "parser.h"
#include "Scanner.h"
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;



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
	Token testy;


	for (string line; getline(ll, line);) {
	
		istringstream iss(line);
		copy(istream_iterator<string>(iss), istream_iterator<string>(), back_inserter(sc.ss));
	
	}
	
	while (!inf.eof()) {
		sc >> testy;
		
		if (testy.tok == Token::Tokens::unknown) {
			continue; 
			//skips this token.
		}
	}
	
	bool hcb = false;
	
	//loop through the vector of tokens until no more.
	//start the recursive descent parser in each loop. 
	//In the loop of vt size, go over until sc.counts which represents tokens until 
	//it covers a complete HC. 
	while ( (sc.vt.size() > 1 ) && sc.ifValidToRead() ) {
		string file = "";
		bool hcb = sc.hc();
		for (int i = 0; i < sc.counts; ++i) {
			
			if (hcb) {
				file += sc.vt[0].tokstr;
				sc.vt.erase(sc.vt.begin());
				//remove tokens already looked at.
			}
		}
		sc.counts = 0;
		if (hcb) {
			//send the string that is an HC to the outfile
			outfile << file  << endl;
		}
	}
	
}


int main(int argc, char* argv[])
{
	
	if (argc < 3) {
		//error message!
		cout << errorNotEnough << endl;
		
	}
	else if (argc > 3) {
		cout << errorTooMany << endl;
	}
	try {
		parser(argv[1], argv[2]);
	}
	catch (errors e) {
		if (e == errors::inputFile) {
			cout << errorIn << endl;
			return 1;
		}
		else if (e ==  errors::outputFile) {
			cout << errorOut << endl;
			return 2;
		}
	}

	return 0;
}

