
#include "stdafx.h"
/*
 Authors: Adam Sandor, David Mcdonnel
 Lab 0
 adam.sandor@wustl.edu
 dmcdonnel@wustl.edu
 Purpose:
	THis class runs the  recursive descent parser to parse the inputted
	file depending on a grammar. THis class determines which kind of Token::Tokens
	value to a string. 
*/
#include "Scanner.h"
#include "SymTabObj.h"
#include "SymbolTable.h"

#include <set>
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>


using namespace std;


Scanner::Scanner(ifstream & infs) : ifs(infs), counts(0), ss(), vt(),  symTab() {

}

bool Scanner::findAnd(string in) {
	return !in.compare(andS);
}

bool Scanner::findSep(string in) {
	return !in.compare(sepS);
}

bool Scanner::findLP(string in) {
	return !in.compare(lpS);
}

bool Scanner::findRP(string in) {
	return !in.compare(rpS);
}

bool Scanner::findComma(string in) {
	return !in.compare(commaS);
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
	int i = counterZero;
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
Scanner & Scanner::operator>>(shared_ptr<Token> spt) {
	string test;
	Scanner::ifs >> test;
	
	if (Scanner::findComma(test)) {
	
		spt->tok = Token::Tokens::Comma;
		spt->tokstr = test;
		vt.push_back(spt);

	}
	else if (Scanner::findRP(test)) {
		spt->tok = Token::Tokens::Rp;
		spt->tokstr = test;
		vt.push_back(spt);

	}
	else if (Scanner::findLP(test)) {
		spt->tok = Token::Tokens::Lp;
		spt->tokstr = test;
		vt.push_back(spt);

	}
	else if (Scanner::findSep(test)) {
		spt->tok = Token::Tokens::Sep;
		spt->tokstr = test;
		vt.push_back(spt);
		
	}
	else if (Scanner::findAnd(test)) {
		spt->tok = Token::Tokens::And;
		spt->tokstr = test;
		vt.push_back(spt);
	
	}
	else if (Scanner::findAlpha(test)) {
		
		LabelToken tt(test);
		shared_ptr<Token> sp = make_shared<Token>(tt);
		vt.push_back(sp);
		
	}
	else if (Scanner::findNum(test)) {

		NumberToken tt(test);
		shared_ptr<Token> sp = make_shared<Token>(tt);
		vt.push_back(sp);

	}
	else {
		spt->tok = Token::Tokens::unknown;
		spt->tokstr = test;
		vt.push_back(spt);

	}

	return *this;//dereferencing operator to get the thing this is pointing to
}

void Scanner::read(shared_ptr<Token> t, Token::Tokens expected) {
	
	if (t->tok == expected) {
		counts++;
		
		if (counts == vt.size() && (expected == Token::Tokens::Rp)) {
			
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
		cout << errorTokExpWas << expected << errorTokExpWas2 << t->tok << commaS << t->tokstr << endl;

		vt.erase(vt.begin());
		if (!(counts - one > vt.size())) {
			vt.erase(vt.begin(), vt.begin() + (counts - one));
		}
		
		throw Errors::errorExpected;
	}
}

bool Scanner::hc() {
	try  {

		head();
		if (vt[counts]->tok == Token::Tokens::Sep) {
			read(vt[counts], Token::Tokens::Sep);
			body();
		}
	}
	
	catch (Errors e) {
		if (e == Errors::errorExpected) {
			symTab.getSyms().clear();
			symTab.getSymsValid().clear();
			return false;
		}
		else if (e == Errors::endOfFileCase) {
			for (SymTabObj s : symTab.getSyms()) {
				symTab.putValid(s);
			}
			
			symTab.getSyms().clear();
			return true;
		}
	}
	for (SymTabObj s : symTab.getSyms()) {
		symTab.putValid(s);
	}
	
	symTab.getSyms().clear();
	
	return true;
}

void Scanner::head() {
	bool isHeadH = true;
	
	predicate(isHeadH);
	
	//Extra Credit Attempt
	////////////////////////////

	while (  vt[counts]->tok == Token::Tokens::And) {
		read(vt[counts], Token::Tokens::And);
		predicate(isHeadH);
	}
	
	///////////////////////////////////

	isHeadH = false;
}

void Scanner::body() {
	
	bool isHeadB = false;
	predicate(isHeadB);
	while (vt[counts]->tok == Token::Tokens::And){

		read(vt[counts], Token::Tokens::And);

		predicate(isHeadB);
	}
}

void Scanner::predicate(bool isHeadP) {
	
	name(isHeadP);
	read(vt[counts], Token::Tokens::Lp);

	if (vt[counts]->tok == Token::Tokens::Number || vt[counts]->tok == Token::Tokens::Label) {

		args();
	}
	read(vt[counts], Token::Tokens::Rp);


}

void Scanner::name(bool isHeadPN) {
	
	read(vt[counts], Token::Tokens::Label);
	vector<Info> v;
	
	if (isHeadPN) {
		v.push_back(Info::isHeadP);
		v.push_back(Info::isNameLab);
	}
	else {

		v.push_back(Info::isBodyP);
		v.push_back(Info::isNameLab);
	}
	SymTabObj sn(vt[counts-one], v);
	symTab.putLab(sn);

}
void Scanner::args() {

	symbol();
	while (vt[counts]->tok == Token::Tokens::Comma) {
		read(vt[counts], Token::Tokens::Comma);
		symbol();
	}
}
void Scanner::symbol() {
	if (vt[counts]->tok == Token::Tokens::Number) {
		read(vt[counts], Token::Tokens::Number);
		vector<Info> v{ Info::isSymbolLab };
		SymTabObj sn(vt[counts-one], v);
		symTab.putNum(sn);
	
	}
	else if (vt[counts]->tok == Token::Tokens::Label) {
		read(vt[counts], Token::Tokens::Label);
		
		vector<Info> v{ Info::isSymbolLab };
		SymTabObj sn(vt[counts-one], v);
		
		symTab.putLab(sn);
	
	}
}


