#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <vector>
// #include "VariadicTable.h"
#include <regex>
#include <fstream>
#include <iostream>
#include "Token.h"
using namespace std;

#pragma once

class Lexer
{
private:
	vector<pair<string, string>> tokenVector;
	// vector<Token> tokenVector1;
	int tokensSize = 0;
	// string myText;
	string delimiter = " ";
	// string token;
	vector<string> linesofcode;
	smatch match;
	bool boolOp = false;
	bool isStringLiteral = false;
	Token token = Token();

	ifstream MyReadFile;
	regex commentRegex;

	regex keywordsRegex;
	regex booleanOpRegex;
	regex IdRegex;
	regex numbersRegex;
	regex delimitersRegex;
	regex arithmeticOpRegex;
	regex stringLiteralRegex;

public:
	Lexer();

	~Lexer();

	// Lexer(ifstream MyReadFile, string MyText);

	// void Analyze(ifstream &MyReadFile, string myText);

	void Tokenize();

	vector<Token> getTokens(ifstream &MyReadFile, string myText);
	vector<Token> tokenVector1;
};
