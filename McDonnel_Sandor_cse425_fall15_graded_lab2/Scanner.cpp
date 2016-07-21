
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
Lab2 Update:
Now this class has a dynamic symbol table which is used to unify
predicates for logic programming.
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

HCObj hco;
vector<shared_ptr<PredObj>> predGlobs;
vector<shared_ptr<SymbolObj>> symGlobs;
vector<string> subList;
//<string> subListConst;
vector<shared_ptr<PredObj>> predsSwapped;


Scanner::Scanner(ifstream & infs) : ifs(infs), counts(0), ss(), vt(), symTab() {

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
	int i = counterZeroScan;
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

bool isNumber(string in) {
	for (char c : in) {
		if (!isdigit(c)) {
			return false;
		}
	}
	return true;
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
		shared_ptr<LabelToken> sp = make_shared<LabelToken>(tt);
		vt.push_back(sp);

	}
	else if (Scanner::findNum(test)) {

		NumberToken tt(test);
		//saves the value as an unsigned int.
		tt.n = strtoul(test.c_str(), nullptr, 10);
		shared_ptr<NumberToken> sp = make_shared<NumberToken>(tt);
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

			predGlobs.clear();
			symGlobs.clear();
			hco.sbo = nullptr;
			hco.sho = nullptr;

			throw Errors::errorExpected;
		}
	}
	else {

		cout << errorTok << endl;
		cout << errorTokExpWas << expected << errorTokExpWas2 << t->tok << commaS << t->tokstr << endl;

		vt.erase(vt.begin());
		if (!(counts - oneScan > vt.size())) {
			vt.erase(vt.begin(), vt.begin() + (counts - oneScan));
		}

		predGlobs.clear();
		symGlobs.clear();
		hco.sbo = nullptr;
		hco.sho = nullptr;

		throw Errors::errorExpected;
	}
}

bool Scanner::hc(ofstream & os) {
	try  {

		read(vt[counts], Token::Tokens::Lp);
		HCObj hco;
		head(hco);
		if (vt[counts]->tok == Token::Tokens::Lp) { //first of body
		
			body(hco);
		}

		read(vt[counts], Token::Tokens::Rp);
	}

	catch (Errors e) {
		if (e == Errors::errorExpected) {
			symTab.getSyms().clear();
			symTab.getSymsValid().clear();
			hco.sho = nullptr;
			hco.sbo = nullptr; //should delete the symbol table that was made.
			return false;
		}
		else if (e == Errors::endOfFileCase) {
			for (SymTabObj s : symTab.getSyms()) {
				symTab.putValid(s);
			}

			predMatching(os);
			symTab.getSyms().clear();
			
			return true;
		}
	}
	for (SymTabObj sym : symTab.getSyms()) {
		symTab.putValid(sym);
	}

	predMatching(os);

	symTab.getSyms().clear();

	return true;
}

void predMatching(ofstream & os) {
	vector<int> seenIndices;

	for (unsigned int c = counterZeroScan; c < predGlobs.size(); ++c) {//c is the 'first'/earlier use of the predicate
		for (unsigned int d = counterZeroScan; d < predGlobs.size(); ++d) { //d is the 'second'/later use of the predicate

			bool skip = false;
			
			//This section decides if these predicates were already looked at, and if so,
			//breaks out of this loop and causes a continue in the d loop.
			for (unsigned int count = 0; count < seenIndices.size(); ++count) {
				if (count == counterZeroScan && seenIndices[count] == c && seenIndices[count + oneScan] == d) {
					
					skip = true;
				}
				else if (count == counterZeroScan && seenIndices[count] == d && seenIndices[count + oneScan] == c) {
					
					skip = true;
				}
				else if (count % 2 == counterZeroScan) {
					
					if (count < (seenIndices.size() - oneScan) && seenIndices[count] == c && seenIndices[count + oneScan] == d) {
						skip = true;
					}

					else if (count < (seenIndices.size() - oneScan) && seenIndices[count] == d && seenIndices[count + oneScan] == c) {
						
						skip = true;
					}
					else if (count > counterZeroScan && seenIndices[count] == c && seenIndices[count - oneScan] == d) {
						
						skip = true;
					}
					else if (count > counterZeroScan && seenIndices[count] == d && seenIndices[count - oneScan] == c) {
						
						skip = true;
					}
					
				}
				if (skip) {///////////////////////////////////////////
					break;
				}
			}
			if (skip) {
				
				continue;
			}

			if ((d != c) && (d > c) && samePreds(predGlobs[c], predGlobs[d])) {//!!!!!!!!!!!!!!!!!
				//same preds but not same indices. can unify6.
				seenIndices.push_back(c);
				seenIndices.push_back(d);
				predsSwapped.push_back(predGlobs[c]);
				predsSwapped.push_back(predGlobs[d]);
				

				string nameC;
				vector<string> symsC;

				nameC = predGlobs[c]->sno->st->tokstr;
				for (unsigned int s = counterZeroScan; s < predGlobs[c]->vspo.size(); ++s) {
					symsC.push_back(predGlobs[c]->vspo[s]->st->tokstr);
				}
				string nameD;
				vector<string> symsD;
				nameD = predGlobs[d]->sno->st->tokstr;
				for (unsigned int s = counterZeroScan; s < predGlobs[d]->vspo.size(); ++s) {
					symsD.push_back(predGlobs[d]->vspo[s]->st->tokstr);
				}
				unify(nameC, symsC, nameD, symsD, os);
				
			}
		}
	}

	predGlobs.clear();
	symGlobs.clear();
}

bool samePreds(shared_ptr<PredObj> & p1, shared_ptr<PredObj> & p2) {
	
	if (!!p1->sno->st->tokstr.compare(p2->sno->st->tokstr) ||
		p1->vspo.size() != p2->vspo.size()) {
		
		return false;
	}
	
	for (unsigned int c = counterZeroScan; c < p1->vspo.size(); ++c) {

		if (isNumber(p1->vspo[c]->st->tokstr) && isNumber(p2->vspo[c]->st->tokstr) ) {
			if (p1->vspo[c]->st->tokstr.compare(p2->vspo[c]->st->tokstr)) {//checks if diff
				
				return false; //not matching constants
			}
		}
	}
	
	return true;
}

void unify(string & nameC, vector<string> & symsC, string & nameD, vector<string> & symsD, ofstream & os) {
	vector<string> symsCCopy = symsC;
	vector<string> symsDCopy = symsD;
	
	//change the previous binds of variables due to later calls.
	//then update the substitution list for it.
	//when constants override one, change all others of the same variable that was changed.
	//Need to know which is the later one.
	
		
	for (unsigned int count = counterZeroScan; count < symsC.size(); ++count) {
			
			if (!symsC[count].compare(symsD[count])) {
				//ignore because are same string
				continue;
			}
			else {
				
				//if both are constants, invalid logic.
				if (isNumber(symsC[count]) && isNumber(symsD[count]) && !!symsC[count].compare(symsD[count])) {
					
					subList.clear();
					return;
				}
				//if one is a constant, make the other the same constant
				else if (isNumber(symsC[count])) {
					
					string tempVar = symsD[count];
					symsD[count] = symsC[count];
					//now update the substitution list
					//first is tempVar, then second is symsC[count]
					string subEntry = tempVar + space + symsD[count];
					subList.push_back(subEntry);

					for (string & sym : symsC) {
						if (!sym.compare(tempVar)) {
							sym = symsC[count];
						}
					}
					for (string & sym : symsD) {
						if (!sym.compare(tempVar)) {
							sym = symsC[count];
						}
					}
					//subListConst.push_back(tempVar + " " + symsC[count]);
				}
				else if (isNumber(symsD[count])) {
					
					string tempVar = symsC[count];
					symsC[count] = symsD[count];
					string subEntry = tempVar + space + symsC[count];
					subList.push_back(subEntry);

					for (string & sym : symsD) {
						if (!sym.compare(tempVar)) {
							sym = symsD[count];
						}
					}
					for (string & sym : symsC) {
						if (!sym.compare(tempVar)) {
							sym = symsD[count];
						}
					}
					//subListConst.push_back(tempVar + " " + symsD[count]);
				}
				else {
					//2 vars. D overrides C.
					string tempVar = symsC[count];
					
					symsC[count] = symsD[count];
					
					string subEntry = tempVar + space + symsC[count];
					
					subList.push_back(subEntry);
					for (string & sym : symsD) {
						
						if (!sym.compare(tempVar)) {
							
							sym = symsD[count];
							
						}
					}
					for (string & sym : symsC) {
						if (!sym.compare(tempVar)) {
							sym = symsD[count];
						}
					}
				}

			}
		}

		//print out the original predicate, names unchanged and syms vectors
		//saved in symsCCopy, symsDCopy.
		os << predicateC << endl;
		os << nameC << space;
		for (string sOrig : symsCCopy) {
			os << sOrig  << space;
		}
		os << endl;
		os << predicateD << endl;
		os << nameD << space;
		for (string sOrig : symsDCopy) {
			os << sOrig << space;
		}
		os << endl;
		//print out the substitution list.
		os << subListPrint << endl;
		for (string sub : subList) {
			os << sub << endl;
		}
		//print out the new version of the predicates, one print out.
		os<< resultingPred << endl;
		string symbs;
		for (string s : symsC) {
			symbs += space + s;
		}
		os << lpS << space << nameC << space << symbs << space << rpS <<endl;

		subList.clear();

}


void Scanner::head(HCObj & hco) {
	
	bool isHeadH = true;
	HBObj hbo;
	
	predicate(isHeadH, hbo);

	//Extra Credit Attempt
	////////////////////////////

	//while (vt[counts]->tok == Token::Tokens::And) {
	//	read(vt[counts], Token::Tokens::And);
	//	predicate(isHeadH, hbo);
	//}
	
	///////////////////////////////////

	hbo.t = Types::Head;
	hco.sho = make_shared<HBObj>(hbo);

	isHeadH = false;
	
	
}

void Scanner::body(HCObj &hco) {
	
	read(vt[counts], Token::Tokens::Lp);
	
	HBObj hbo;
	hbo.t = Types::Body;

	bool isHeadB = false;
	predicate(isHeadB, hbo);
	while (vt[counts]->tok == Token::Tokens::Lp ||
		vt[counts]->tokstr == lpS){//label for name

		predicate(isHeadB, hbo);
	}

	///
	hco.sbo = make_shared<HBObj>(hbo);
	read(vt[counts], Token::Tokens::Rp);
	///
}

void Scanner::predicate(bool isHeadP, HBObj& hbo) {
	
	PredObj po;


	
	read(vt[counts], Token::Tokens::Lp);
	name(isHeadP,  po);
	
	while (isNumber(vt[counts]->tokstr) || 
		isAlpha(vt[counts]->tokstr) || 
		vt[counts]->tok == Token::Tokens::Number || 
		vt[counts]->tok == Token::Tokens::Label) {
		
		args(po);
	}
	read(vt[counts], Token::Tokens::Rp);
	
	shared_ptr<PredObj> sph = make_shared<PredObj>(po);
	hbo.vp.push_back(sph);
	predGlobs.push_back(sph);//pred list.
	
}

bool isAlpha(string in) {
	int i = counterZeroScan;
	for (char c : in) {
		if (isalpha(c)) {
			i++;
		}
	}
	return (i == in.size());
}

void Scanner::name(bool isHeadPN, PredObj& po) {
	
	NameObj no;
	no.st = vt[counts];

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
	SymTabObj sn(vt[counts - oneScan], v);
	symTab.putLab(sn);

	po.sno = make_shared<NameObj>(no);
	
	
}
void Scanner::args(PredObj& po) {
	
	while (isNumber(vt[counts]->tokstr) ||
		isAlpha(vt[counts]->tokstr) ||
		vt[counts]->tok == Token::Tokens::Number ||
		vt[counts]->tok == Token::Tokens::Label) {
		
		symbol(po);
	}
	
}
void Scanner::symbol(PredObj& po) {
	
	SymbolObj so;

	//if symGlobs ocntains this, just point to that original symbol.
	//hhh;
	int same = checkIfSymbolExists(vt[counts]);
	if ((vt[counts]->tok == Token::Tokens::Number || 
		vt[counts]->tok == Token::Tokens::Label) &&
		same >= counterZeroScan) { //symbol alreqady exists
		
		so.t = symGlobs[same]->t;
		so.st = symGlobs[same]->st;
		
		if (isNumber(so.st->tokstr)) {
			read(vt[counts], Token::Tokens::Number);
		}
		else {
			
			read(vt[counts], Token::Tokens::Label);
		}
		
		vector<Info> v{ Info::isSymbolLab };
		SymTabObj sn(vt[counts - oneScan], v);
		symTab.putNum(sn);
	}
	else if (vt[counts]->tok == Token::Tokens::Number) {

		so.t = Types::Number;
		so.st =vt[counts];
		symGlobs.push_back(make_shared<SymbolObj>(so));
		

		read(vt[counts], Token::Tokens::Number);
		vector<Info> v{ Info::isSymbolLab };
		SymTabObj sn(vt[counts - oneScan], v);
		symTab.putNum(sn);

	}
	else if (vt[counts]->tok == Token::Tokens::Label) {
		so.t = Types::Label;
		so.st = vt[counts];
		symGlobs.push_back(make_shared<SymbolObj>(so));
		

		read(vt[counts], Token::Tokens::Label);
		vector<Info> v{ Info::isSymbolLab };
		SymTabObj sn(vt[counts - oneScan], v);

		symTab.putLab(sn);
	}

	po.vspo.push_back(make_shared<SymbolObj>(so));
	
}

int Scanner::checkIfSymbolExists(shared_ptr<Token> symToCheck) {
	for (unsigned int c = counterZeroScan; c < symGlobs.size(); ++c) {
		if (!symToCheck->tokstr.compare(symGlobs[c]->st->tokstr)) {
			return c;
		}
	}
	return -oneScan;
}
