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

enum Info { isHeadP, isBodyP, isNameLab, isSymbolLab,  isNum, isNull, isAndH  };
const int twoI = 2;
const int zero = 0;
struct SymTabObj {
	shared_ptr<Token> st;
	vector<Info> vi;
	int seen;
	
	SymTabObj();
	SymTabObj(shared_ptr<Token> s, vector<Info> vii);
	
};