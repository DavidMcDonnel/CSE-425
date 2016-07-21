#include "stdafx.h"
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <memory>
#include "SemAnaFun.h"
#include "SymTabObj.h"

RecDec2::RecDec2() : counts2(), semans(), output() {

}

void RecDec2::HC() {

	addToOutput(lp);
	Head();

	if (counts2 < semans.size() && semans[counts2].vi[zero] == Info::isBodyP) {
		Body();
	}

	addToOutput(rp);

}

void RecDec2::addToOutput(string s) {
	output += stringSpace;
	output += s;
}

void RecDec2::read1() {
	counts2++;
}

void RecDec2::Head() {
	Predicate();

	//Extra Credit Attempt
	////////////////////////////

	while (counts2 < semans.size() && semans[counts2].vi[zero] == Info::isHeadP) {

		Predicate();
	}
	//////////////////////
}

void RecDec2::Body() {

	addToOutput(lp);
	while (counts2 < semans.size() && semans[counts2].vi[zero] == Info::isBodyP) {
		Predicate();
	}
	addToOutput(rp);
}

void RecDec2::Predicate() {

	addToOutput(lp);
	Name();

	while ((counts2 < semans.size()) && ((semans[counts2].vi[zero] == Info::isSymbolLab))) {
		Symbol();
	}

	addToOutput(rp);
}

void RecDec2::Name() {
	addToOutput(semans[counts2].st->tokstr);
	counts2++;

}

void RecDec2::Symbol() {
	addToOutput(semans[counts2].st->tokstr);
	counts2++;
}


