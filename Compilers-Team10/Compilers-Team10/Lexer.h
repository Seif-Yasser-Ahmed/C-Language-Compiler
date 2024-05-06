#include <ctype.h> 
#include <stdbool.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <string>
#include <vector>
#include "VariadicTable.h"
#include <regex>
using namespace std;
#ifndef GAME_H
#define GAME_H
#pragma once
//class Lexer
//{
//private:
//	const char* keywords[44] = {
//		"auto","static","const",
//		"_Alignas","sizeof","break",
//		"inline","while","_Alignof",
//		"_Generic","case","long",
//		"for","_Atomic","_Imaginary",
//		"char","short","if",
//		"_Bool","_Noreturn","int",
//		"struct","do","typedef",
//		"_Complex","float","union",
//		"return","else","_Static_assert",
//		"double","enum","extern",
//		"void","_Thread_local",
//		"signed","unsigned","register",
//		"switch","volatile","continue",
//		"goto","restrict","default"
//	};
//
//	const char* STDfunctions[11] = {
//		"printf","scanf","strlen",
//		"strcpy","strcmp","strcat",
//		"malloc","free","fgets",
//		"fprintf","toupper"
//	};
//public:
//	bool isDelimiter(char chr) {
//		return (
//			chr == ' ' ||
//			chr == '+' ||
//			chr == '-' || 
//			chr == '*' || 
//			chr == '/' ||
//			chr == '=' ||
//			chr == ',' || 
//			chr == ';' || 
//			chr == '%' || 
//			chr == '^' || 
//			chr == '>' ||
//			chr == '<' || 
//			chr == '(' || 
//			chr == ')' || 
//			chr == '[' || 
//			chr == ']' || 
//			chr == '{' || 
//			chr == '}' ||
//			chr == '#' ||
//			chr == '?');
//	}
//	bool isOperator(char chr) {
//		return(
//			chr == '+'  ||
//			chr == '-'  ||
//			chr == '*'  ||
//			chr == '/'  ||
//			chr == '>'  ||
//			chr == '<'  ||
//			chr == '='  ||
//			chr == '++' ||
//			chr == '--');
//	}
//	bool isBooleanOperator(char chr) {
//		return(
//			chr == '==' || 
//			chr == '!=' || 
//			chr == '>'  || 
//			chr == '<'  || 
//			chr == '<=' || 
//			chr == '>=' || 
//			chr == '&&' ||
//			chr == '||' ||
//			chr == '!'  ||
//			chr == '~'  ||
//			chr == '?:' ||
//			chr == '&'  ||
//			chr == '|'  ||
//			chr == '^'  ||
//			chr == '<<' ||
//			chr == '>>');
//	}
//	bool isValidID(char* str) {
//		return(
//			str[0] != '0' &&
//			str[0] != '1' &&
//			str[0] != '2' &&
//			str[0] != '3' &&
//			str[0] != '4' &&
//			str[0] != '5' &&
//			str[0] != '6' &&
//			str[0] != '7' &&
//			str[0] != '8' &&
//			str[0] != '9' &&
//			!isDelimiter(str[0]) &&
//			!isOperator(str[0]) &&
//			!isBooleanOperator(str[0])&&
//			!isKeyword(str)
//			);
//	}
//	bool isKeyword(char* str) {
//		for (int i = 0; i < sizeof(keywords); i++) {
//			if (strcmp(keywords[i], str) == 0) {
//				return true;
//			}
//			else {
//				return false;
//			}
//		}
//	}
//
//	
//};
class Lexer{
public:
	Lexer();

	~Lexer();

	//Lexer(ifstream MyReadFile, string MyText);

	void Analyze(ifstream & MyReadFile, string myText);

	void Tokenize(ifstream& MyReadFile, string myText);

	vector<pair<string, string>> getTokens();

private:

	vector<pair<string, string>> tokenVector;
	int tokensSize = 0;
	string myText;
	string delimiter = " ";
	string token;
	vector<string> linesofcode;
	smatch match;
	bool boolOp = false;
	bool isStringLiteral = false;

	ifstream MyReadFile;


};
#endif
