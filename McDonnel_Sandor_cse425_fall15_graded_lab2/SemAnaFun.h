#pragma once
/*
Authors: Adam Sandor, David Mcdonnel
Lab 1
adam.sandor@wustl.edu
dmcdonnel@wustl.edu
Purpose:
This file has helpful string and int constants and declares the
2nd recursive descent parser, which is used to build the output
according to the output grammar.
*/
#include <vector>
#include "SymTabObj.h"

class RecDec2 {
public:
	void HC();
	void Head();
	void Body();
	void Predicate();
	void Name();
	void Symbol();
	void read2(SymTabObj so, vector<Info> in);
	void read1();
	RecDec2();
	unsigned int counts2;
	vector<SymTabObj> semans;
	string output;
	void addToOutput(string s);
};

const string lp = "(";
const string rp = ")";
const string stringSpace = " ";

