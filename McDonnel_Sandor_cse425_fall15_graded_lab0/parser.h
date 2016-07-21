#pragma once

#include <string>

using namespace std;

enum errors {inputFile, outputFile};

const string errorNotEnough = "This program failed to run due to not enough inputs:";
const string errorTooMany = "This program failed to run because there were too many inputs";
const string errorIn = "This program failed to run: Input file could not be opened";
const string errorOut = "This program failed to run: Output file could not be opened";



void parser(string in, string out);



