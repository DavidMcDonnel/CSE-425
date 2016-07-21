
#include "stdafx.h"

#include "Scanner.h"

#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>


using namespace std;



Scanner::Scanner(ifstream & infs) : ifs(infs), counts(0), ss(), vt(), testTT(), testSS() {
	
	//initialixze member variablesd in the base member variable list.


	
}

//bool Scanner::ifValidToRead() {
	//NEED TO MAKE!!!!
//}

bool Scanner::findAnd(string in) {
	return !in.compare("^");
}

bool Scanner::findSep(string in) {
	return !in.compare(":-");
}

bool Scanner::findLP(string in) {
	return !in.compare("(");
}

bool Scanner::findRP(string in) {
	return !in.compare(")");
}

bool Scanner::findComma(string in) {
	return !in.compare(",");
}

bool Scanner::findNum(string in) {
	for (char c : in) {
		if (!isdigit(c)) {
			return false;
		}
	}
	return true;
}

bool Scanner::findAlpha(string in) {
	int i = 0;
	for (char c : in) {
		if (isalpha(c)) {
			i++;
		}
	}
	return (i == in.size());
}

bool Scanner::ifValidToRead() {
	if (ifs.is_open()) {
		return true;
	}
	else {
		return false;
	}
}

/*
Extraction operator.
Extracts from the input filestream, 
*/
Scanner & Scanner::operator>>(Token & t) {
	 string test;
	 Scanner::ifs >> test;
	 cout << test << " sssssssssssss" << endl;

	
	//finds an empty string to be an alpha. What?????/
	 if (Scanner::findComma(test)) {
		 t.tok = Token::Tokens::Comma;
		 t.tokstr = test;
		 vt.push_back(t);
		 cout << "found comma" << endl;

	 }
	 else if (Scanner::findRP(test)) {
		 t.tok = Token::Tokens::Rp;
		 t.tokstr = test;
		 vt.push_back(t);
		 cout << "found rp" << endl;

	 }
	 else if (Scanner::findLP(test)) {
		 t.tok = Token::Tokens::Lp;
		 t.tokstr = test;
		 vt.push_back(t);
		 cout << "found lp" << endl;

	 }
	 else if (Scanner::findSep(test)) {
		 t.tok = Token::Tokens::Sep;
		 t.tokstr = test;
		 vt.push_back(t);
		 cout << "found sep" << endl;

	 }
	 else if (Scanner::findAnd(test)) {
		 t.tok = Token::Tokens::And;
		 t.tokstr = test;
		 vt.push_back(t);
		 cout << "found and" << endl;

	 }
	 else if (Scanner::findAlpha(test)) {
		 t.tok = Token::Tokens::Label;
		 t.tokstr = test;
		 vt.push_back(t);
		 cout << "found alpha" << endl;
		 

	 }
	 else if (Scanner::findNum(test)) {
		 t.tok = Token::Tokens::Number;
		 t.tokstr = test;
		 vt.push_back(t);

		 cout << "found num" << endl;

	 }
	 else {
		 t.tok = Token::Tokens::unknown;
		 t.tokstr = test;
		 cout << "found unknown" << endl;

	 }
	
	 return *this;//dereferencing operator to get the thing this is pointing to
}


void Scanner::read(Token t, Token::Tokens expected) {
	
	if (t.tok == expected) {
		counts++;
		if (counts == vt.size() && (expected == Token::Tokens::Rp ) ) {
			throw Errors::endOfFileCase;
		}
		else if (counts == vt.size()) {
			
			vt.erase(vt.begin());
			cout << errorEndEarly << endl;
			throw Errors::errorExpected;
		}
	}
	else {
		cout << errorTok << endl;
		cout << errorTokExpWas << expected << errorTokExpWas2 << t.tok << "," << t.tokstr  <<endl;
		vt.erase(vt.begin());
		throw Errors::errorExpected;
	}
}

bool Scanner::hc() {
	try  {
		
		head();
		if (vt[counts].tok == Token::Tokens::Sep) {
			read(vt[counts], Token::Tokens::Sep);
			
			body();
		}
	}
	
	catch (Errors e) {
		if (e == Errors::errorExpected) {
			return false;
		}
		else if (e == Errors::endOfFileCase) {
			
			return true;
		}
	}
	return true;
}

void Scanner::head() {
	
	predicate();
}

void Scanner::body() {
	
	predicate();
	while (vt[counts].tok == Token::Tokens::And){
		
		read(vt[counts], Token::Tokens::And);
		
		predicate();
	}
}

void Scanner::predicate() {
	
	name();
	read(vt[counts], Token::Tokens::Lp);
	
	if (vt[counts].tok == Token::Tokens::Number || vt[counts].tok == Token::Tokens::Label) {
		
		args();
	}
	read(vt[counts], Token::Tokens::Rp);
	
	
}

void Scanner::name() {
	
	read(vt[counts], Token::Tokens::Label);
	
}
void Scanner::args() {
	
	symbol();
	while (vt[counts].tok == Token::Tokens::Comma) {
		read(vt[counts], Token::Tokens::Comma);
		symbol();
	}
}
void Scanner::symbol() {
	
	if (vt[counts].tok == Token::Tokens::Number) {
		read(vt[counts], Token::Tokens::Number);
	}
	else if (vt[counts].tok == Token::Tokens::Label) {
		read(vt[counts], Token::Tokens::Label);
	}
}


