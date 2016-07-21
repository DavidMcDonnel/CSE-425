#pragma once

/*
Lab0
Authors: Adam Sandor, adam.sandor@wustl.edu
David Mcdonnel, dmcdonnel@wustl.edu
Purpose:
THis file has useful string and number constants used
throughout the lab1.cpp file.
*/


#include <string>

using namespace std;

enum errors { inputFile, outputFile };

const string errorNotEnough = "This program failed to run due to not enough inputs:";
const string errorTooMany = "This program failed to run because there were too many inputs";
const string errorIn = "This program failed to run: Input file could not be opened";
const string errorOut = "This program failed to run: Output file could not be opened";
const string outputHC = "The valid HC is:";
const string outputLabNums = "The labels and numbers in the entire file are:";
const int counterZero = 0;
const int outputFileIndex = 2;
const int inputFileIndex = 1;
const int one = 1;
const int two = 2;
const int numArgsThree = 3;
const int tooFewReturn = 4;
const int tooManyReturn = 5;
const int inputFileBadReturn = 1;
const int outputFileBadReturn = 2;
const int correctReturn = 0;

string emptyString = "";
string spaceString = " ";
const int numSeen = -1;

void parser(string in, string out);

bool compareString(string s1, string s2);


