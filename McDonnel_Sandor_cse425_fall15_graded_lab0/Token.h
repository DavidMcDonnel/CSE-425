#pragma once

#include <string>
using namespace std;

struct Token {
	enum Tokens{ symbol, args, name, pred, body, head, hc, Sep, Comma, And, Rp, Lp, Label, Number, unknown };
	Tokens tok;
	string tokstr;
	Token();
	

};