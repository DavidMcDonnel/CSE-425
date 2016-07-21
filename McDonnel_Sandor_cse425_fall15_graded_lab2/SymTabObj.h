#pragma once

/*
Lab1
Authors:
Adam Sandor, adam.sandor@wustl.edu
David Mcdonnel, dmcdonnel@wustl.edu

Purpose:
This file defines a Symbol Table Object that we use to populate the
Symbol Table. THese objects consist of shared pointers to TOkens and
a vector of relevant information about the token in reference to the
output grammar.
*/


#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include "Token.h"

using namespace std;
class HeadObj;
class BodyObj;
class PredObj;
class HBObj;
class NameObj;
class SymbolObj;

enum Info { isHeadP, isBodyP, isNameLab, isSymbolLab, isNum, isNull, isAndH };

enum Types {HC, Head, Body, Predicate, Name, Symbol, Label, Number, None};
enum Terms {llp, rrp};

const int twoI = 2;
const int zero = 0;
struct SymTabObj {
	shared_ptr<Token> st;
	vector<Info> vi;
	int seen;

	vector<Types> vTypes;

	SymTabObj();
	SymTabObj(shared_ptr<Token> s, vector<Info> vii);

};


class HCObj {
public:
	Terms first;
	shared_ptr<HBObj > sho;
	shared_ptr<HBObj> sbo;
	Terms second;
	HCObj();
};

class HBObj {
public:
	Types t;
	
	vector<shared_ptr<PredObj>> vp;
	HBObj();
};

class PredObj {
public:
	Terms first;
	shared_ptr<NameObj> sno;
	vector<shared_ptr<SymbolObj> > vspo;
	Terms second;
	PredObj();
};

class NameObj {
public:
	Types t;
	shared_ptr<Token> st;
	NameObj();
};

class SymbolObj {
public:
	Types t;
	shared_ptr<Token> st;
	SymbolObj();
}; 







