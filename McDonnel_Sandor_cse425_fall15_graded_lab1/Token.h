#pragma once
/*Authors: Adam Sandor, David Mcdonnel
 Lab 0
 adam.sandor@wustl.edu
 dmcdonnel@wustl.edu
 Purpose: This file has the declarations for the Token struct.
	The Token structs have necessary info such as the Tokens enum
	and the string to which it is associated. It also has the two 
	special cases of a Token, the LabelToken and the NumberToken. 
	These two make up every valid HC.
*/
#include <string>
using namespace std;

struct Token {
	int num;
	enum Tokens{ symbol, args, name, pred, body, head, hc, Sep, Comma, And, Rp, Lp, Label, Number, unknown };
	Tokens tok;
	string tokstr;
	Token();
	Token(Tokens tk, const string ts);
};

struct LabelToken : public Token {

	LabelToken(string str);
};

struct NumberToken : public Token {
	unsigned int n;
	NumberToken(string st);
};