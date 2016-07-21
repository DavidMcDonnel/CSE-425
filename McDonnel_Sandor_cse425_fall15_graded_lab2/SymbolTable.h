
#pragma once
/*
Lab1
Authors: Adam Sandor, adam.sandor@wustl.edu
David Mcdonnel, dmcdonnel@wustl.edu
Purpose:
This is the Symbol Table class. It has the accessor
and put methods for the table, whichl handle Symbol Table Objects.
The final vector of SymTabObjs we use to print out the output is
the vsymsValid vector.

*/
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <set>
#include "Token.h"
#include "SymTabObj.h"

using namespace std;

class SymTab {
public:


	vector<SymTabObj> vsyms;
	vector<SymTabObj> vsymsValid;
	vector<shared_ptr<Token>> labels;
	vector<shared_ptr<Token>> numbers;
	set<string> labs;
	set<int> nums;


	SymTab();
	void putNum(SymTabObj t);
	void putLab(SymTabObj t);
	void putValid(SymTabObj t);


	vector<shared_ptr<Token>> & getLabels();
	vector<shared_ptr<Token>> & getNums();
	vector<SymTabObj> & getSyms();
	void emptyAll();
	vector<SymTabObj> & getSymsValid();


	SymTabObj findSymObj();
};