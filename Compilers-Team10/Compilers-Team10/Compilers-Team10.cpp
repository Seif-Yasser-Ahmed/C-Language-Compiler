#include <iostream>
#include <regex>
#include <vector>
#include "VariadicTable.h"
using namespace std;


/*
Notes :
- Differentaite between add operator and posotive sign , same with negative
- Identifiers Regex
- Symbol Table
- Exponential
*/

//Delimimters
//  
//Boolean Operators
//
//Arithmetic    
//
//Keywords
//
//Identifiers
//
//Numbers

//-------is integer function
bool isInt(string str) {

	int i = 0;
	while (isdigit(str[i])) {
		i++;
	}
	return str[i] == '\0';
}
//-------is float function
bool isFloat(string str) {

	int i = 0;
	int dots = 0;
	while (isdigit(str[i]) || str[i] == '.') {
		if (str[i] == '.') dots++;
		if (dots > 1) return false;
		i++;
	}
	return str[i] == '\0';
}
int main()
{
	string input, temp;
	vector<string> symbolTable;
	//vector<string> tokenTable;
	vector<pair<string, string>>tokenTable;
	//map<string, int> mp;


	VariadicTable<string> symbolT({ "Identifiers" });
	VariadicTable<string, string, string> tokenT({ "Tokens","description","lexeme" });


	smatch match;
	auto start = input.cbegin();


	//---------------------------------------------------------------------------------------
	regex delimitersRegex(R"(\{|\}|\(|\)|;|,|\[|\]|\.|:)");
	regex arithmeticOpRegex(R"((\+|-|\*|\/|%|\+\+|--|=))");
	regex booleanOpRegex(R"((>=|<=|==|!=|>|<|\&\&|\|\||!|\&|\||\^|~|<<|>>|\?|\.\s|->))");
	regex keywordsRegex(R"(\b(auto|static|const|_Alignas|sizeof|break|inline|while|_Alignof|_Generic|case|long|for|_Atomic|_Imaginary|char|short|if|_Bool|_Noreturn|int|struct|do|typedef|_Complex|float|union|return|else|_Static_assert|double|enum|extern|void|_Thread_local|signed|unsigned|register|switch|volatile|continue|goto|restrict|default)(\*)?\b)");
	regex stringLiteralRegex(R"(\".*\")");
	regex numbersRegex(R"(((\+|-)?(-\+)*-?(0|[1-9][0-9]*)?(\.)?([1-9][0-9]*)(((e|E)(\+|-)?[0-9]+)?)|(0[bB][01]+|0[xX][0-9a-fA-F]+|0[0-7]*|[1-9][0-9]*)))");
	regex IdRegex(R"((?:[_a-zA-Z][_a-zA-Z0-9]*|0x[0-9a-fA-F]+|0b[01]+))");
	//regex IdRegex(R"(^[a-zA-Z_][0-9a-zA-Z_]*$)");
	//regex Exponential(R"(((\+-)*\+?|(-\+)*-?)(0|[1-9][0-9]*)(((e|E)(\+|-)?[0-9]+)?))");
	//
//----------------------------------------------------------------------------------------

	cout << "Type \"return\" to close the program and print the symbol table" << endl;
	while (true)
	{

		cout << "Enter a line of code: ";
		getline(cin, input);
		if (input.empty() || regex_match(input, regex("^\\s*(//.*)?$")))
		{
			continue;
		}
		//------------- Delimiter's Regex
		start = input.cbegin();
		bool allow = true;
		bool stringlit = true;
		while (regex_search(start, input.cend(), match, delimitersRegex))
		{
			int size = input.size();
			for (int i = 0; i < input.size(); i++) {
				if (i > 0)
				{
					if (input[i] == '.' && isdigit(input[i - 1]) && isdigit(input[i + 1]) && size > 1) {
						allow = false;
					}
				}
				if (i == 0 && input[0] == '.' && isdigit(input[i + 1])) {
					allow = false;
				}
			}
			if (!allow) {
				break;
			}
			bool allowadd = true;
			cout << "<  " << match.str(0) << " , Delimiter >" << endl;
			for (int i = 0; i < tokenTable.size(); i++) {
				if (tokenTable[i].first == match.str(0))
				{
					allowadd = false;
				}
			}
			if (allowadd) {
				string temp = match.str(0);
				tokenTable.push_back(make_pair(temp, "Delimiter"));
			}
			start = match[0].second;
		}


		//------------- Strings's Regex
		start = input.cbegin();
		while (regex_search(start, input.cend(), match, stringLiteralRegex))
		{
			cout << "<  " << match.str(0) << " , String literal >" << endl;
			stringlit = false;
			start = match[0].second;
		}


		//------------- Boolean's Regex
		start = input.cbegin();
		while (regex_search(start, input.cend(), match, booleanOpRegex))
		{
			cout << "<  " << match.str(0) << " , Boolean Operator >" << endl;
			start = match[0].second;
		}


		//------------- Arithmatic operation's Regex
		start = input.cbegin();
		while (regex_search(start, input.cend(), match, arithmeticOpRegex))
		{
			cout << "<  " << match.str(0) << " , Arithmetic Operator >" << endl;
			start = match[0].second;
		}


		//------------- Keyword's Regex
		start = input.cbegin();
		while (regex_search(start, input.cend(), match, keywordsRegex))
		{
			cout << "<  " << match.str(0) << " , Keyword >" << endl;
			start = match[0].second;
		}


		//------------- Identifiers's Regex
		start = input.cbegin();
		bool allowID = true;
		while (regex_search(start, input.cend(), match, IdRegex))
		{

			for (int i = 0; i < input.size(); i++) {
				// || (isalpha(input[i])&&input[i+1]!=NULL && input[i - 1] == '\"')
				if ((input[i] == 'e' && isdigit(input[i - 1]) || ((input[i] == '\"')&&isalpha(input[i+1])))) {
					allowID = false;
				}
			}
			if (!allowID || !stringlit) {
				break;
			}
			bool allowadd = true;
			if (!regex_match(match.str(0), keywordsRegex) && !regex_match(match.str(0), numbersRegex))
			{
				cout << "<  " << match.str(0) << " , Identifier >" << endl;
				for (int i = 0; i < symbolTable.size(); i++) {
					if (symbolTable[i] == match.str(0))
					{
						allowadd = false;
					}
				}
				if (allowadd) {
					symbolTable.push_back(match.str(0));
				}
			}
			start = match[0].second;
		}


		//------------- Number's Regex
		start = input.cbegin();
		bool expo = true;
		while (regex_search(start, input.cend(), match, numbersRegex))
		{
			for (int i = 0; i < match.str(0).size(); i++) {
				if (match.str(0)[i] == 'e') {
					expo = false;
				}
			}
			if (expo) {
				if (isInt(match.str(0))) {

					cout << "< " << match.str(0) << " , Number of Type Integer >" << endl;
				}
				else if (isFloat(match.str(0))) {
					cout << "< " << match.str(0) << " , Number of Type Float >" << endl;
				}
				else {
					cout << "< " << match.str(0) << " , Number But the type is not identified >" << endl;
				}
			}
			else {
				cout << "< " << match.str(0) << " , Exponential >" << endl;

			}

			start = match[0].second;
		}
		if (input == "return")
			break;

	}

	//------------- Printing the symbol table
	for (int i = 0; i < symbolTable.size(); i++) {
		symbolT.addRow(symbolTable[i]);
	}
	cout << endl << endl << "Symbol Table" << endl;
	cout << "-------------------------" << endl;
	symbolT.print(cout);


	/*for (int i = 0; i < tokenTable.size(); i++) {
		tokenT.addRow(tokenTable[i].first,tokenTable[i].second,"s");
	}*/
	cout << endl << endl << "Token Table" << endl;
	cout << "-------------------------" << endl;
	tokenT.print(cout);

}
