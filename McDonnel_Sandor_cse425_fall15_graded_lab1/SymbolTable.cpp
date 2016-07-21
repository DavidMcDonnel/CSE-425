#include "stdafx.h"

/*
Lab1
Authors: Adam Sandor, adam.sandor@wustl.edu
		 David Mcdonnel, dmcdonnel@wustl.edu
Purpose:
	This is the Symbol Table object. It has all of the necessary put and getter 
	methods, and the necessary clear methods.
*/

#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <memory>
#include "SymbolTable.h"

SymTab::SymTab() : vsyms(), labels(), numbers(), vsymsValid() {
	
}

void SymTab::putNum(SymTabObj t) {
	numbers.push_back(t.st);
	vsyms.push_back(t);
}

void SymTab::putLab(SymTabObj t) {
	labels.push_back(t.st);
	vsyms.push_back(t);
}

void SymTab::putValid(SymTabObj t) {
	vsymsValid.push_back(t);
}

vector<shared_ptr<Token>> & SymTab::getLabels() {
	return labels;
}

vector<shared_ptr<Token>> & SymTab::getNums(){
	return numbers;
}

vector<SymTabObj> & SymTab::getSyms(){
	return vsyms;
}

void SymTab::emptyAll() {
	vsyms.clear();
	numbers.clear();
	labels.clear();
}

vector<SymTabObj> & SymTab::getSymsValid() {
	return vsymsValid;
}
