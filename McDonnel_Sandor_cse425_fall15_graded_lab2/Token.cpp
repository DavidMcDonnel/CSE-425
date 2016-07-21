#include "stdafx.h"
/*Authors: Adam Sandor, David Mcdonnel
Lab 0
adam.sandor@wustl.edu
dmcdonnel@wustl.edu
Purpose:
This file defines the Token object. Tokens are the building blocks of
this group of files. THey hold information about an inputted string,
determining what kind of string it is in the context of a particular grammar.
*/
#include "Token.h"
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>

Token::Token() : tok(Token::Tokens::unknown), num(rand()) {

}

Token::Token(Token::Tokens tk, const string ts) : tok(tk), tokstr(ts), num(rand()) {

}

LabelToken::LabelToken(const string str) : Token(Token::Tokens::Label, str)  {

}

NumberToken::NumberToken(string st) : Token(Token::Tokens::Number, st) {

}
