#include "stdafx.h"
/*
Authors: Adam Sandor, adam.sandor@wustl.edu
David Mcdonnel, dmcdonnel@wustl.edu
Purpose:
This is the code for constructing a Symbol Table Object.
It acts as a container of information.

*/

#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <memory>
#include "SymTabObj.h"

SymTabObj::SymTabObj() : vi(twoI, Info::isNull), seen(zero) {
	Token t;
	st = make_shared<Token>(t);//can make this in initialization list?

}

SymTabObj::SymTabObj(shared_ptr<Token> s, vector<Info> vii) : st(s), vi(vii) {

}


HCObj::HCObj() : first(Terms::llp), sho(), sbo(), second() {

}

/*
HeadObj::HeadObj() : spo() {
}
BodyObj::BodyObj() : first(Terms::llp), vspo(), second() {
}
*/
HBObj::HBObj() : t(None), vp() {

}

PredObj::PredObj() : first(Terms::llp), sno(), vspo(), second() {

}

NameObj::NameObj() : st() {

}

SymbolObj::SymbolObj() : t(), st() {

}