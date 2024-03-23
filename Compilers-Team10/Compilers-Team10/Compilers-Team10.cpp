#include <iostream>
#include <regex>
#include <vector>
#include <utility>
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


int main()
{
	string input, temp;
	vector<pair<string, string>> symbolTable;
	smatch match;
	auto start = input.cbegin();


	regex delimitersRegex(R"(\{|\}|\(|\)|;|,|\[|\]|\.|:)");
	regex arithmeticOpRegex(R"((\+|-|\*|\/|%|\+\+|--))");
	regex booleanOpRegex(R"((>=|<=|==|!=|>|<|\&\&|\|\||!|\&|\||\^|~|<<|>>|\?|\.\s|->|\*))");
	regex keywordsRegex(R"(\b(auto|static|const|_Alignas|sizeof|break|inline|while|_Alignof|_Generic|case|long|for|_Atomic|_Imaginary|char|short|if|_Bool|_Noreturn|int|struct|do|typedef|_Complex|float|union|return|else|_Static_assert|double|enum|extern|void|_Thread_local|signed|unsigned|register|switch|volatile|continue|goto|restrict|default)\b)");
	regex stringLiteralRegex(R"(\".*\")");
	regex numbersRegex(R"((\+|-)?(0[bB][01]+|0[xX][0-9a-fA-F]+|0[0-7]*|[1-9][0-9]*))");
	regex IdRegex(R"((?:[_a-zA-Z][_a-zA-Z0-9]*|0x[0-9a-fA-F]+|0b[01]+))");




	while (true)
	{
		cout << "Enter a line of code: ";
		getline(cin, input);

		if (input.empty() || regex_match(input, regex("^\\s*(//.*)?$")))
		{
			continue;
		}

		start = input.cbegin();
		while (regex_search(start, input.cend(), match, delimitersRegex))
		{
			cout << "<  " << match.str(0) << " , Delimiter >" << endl;
			start = match[0].second;
		}

		start = input.cbegin();
		while (regex_search(start, input.cend(), match, booleanOpRegex))
		{
			cout << "<  " << match.str(0) << " , Boolean Operator >" << endl;
			start = match[0].second;
		}


		start = input.cbegin();
		while (regex_search(start, input.cend(), match, arithmeticOpRegex))
		{
			cout << "<  " << match.str(0) << " , Arithmetic Operator >" << endl;
			start = match[0].second;
		}

		start = input.cbegin();
		while (regex_search(start, input.cend(), match, keywordsRegex))
		{
			cout << "<  " << match.str(0) << " , Keyword >" << endl;
			start = match[0].second;
		}

		start = input.cbegin();
		while (regex_search(start, input.cend(), match, IdRegex))
		{
			if (!regex_match(match.str(0), keywordsRegex) && !regex_match(match.str(0), numbersRegex))
			{
				cout << "<  " << match.str(0) << " , Identifier >" << endl;
			}
			start = match[0].second;
		}



		start = input.cbegin();
		while (regex_search(start, input.cend(), match, numbersRegex))
		{
			cout << "< " << match.str(0) << " , Number >" << endl;
			start = match[0].second;
		}

		//start = input.cbegin();
		//while (regex_search(start, input.cend(), match, binaryNumRegex))
		//{
		//	if (match.str(0) != "0")
		//	{
		//		cout << "Match found: " << match.str(0) << " Binary Number" << endl;
		//	}
		//	start = match[0].second;
		//}

		//start = input.cbegin();
		//while (regex_search(start, input.cend(), match, hexNumRegex))
		//{
		//	if (match.str(0) != "0")
		//	{
		//		cout << "Match found: " << match.str(0) << " Hex Number" << endl;
		//	}
		//	start = match[0].second;
		//}

		//start = input.cbegin();
		//while (regex_search(start, input.cend(), match, decNumRegex))
		//{
		//	if (match.str(0) != "0")
		//	{
		//		cout << "Match found: " << match.str(0) << " Dec Number" << endl;
		//	}
		//	start = match[0].second;
		//}




		//sregex_iterator delimiterIterator(input.begin(), input.end(), delimitersRegex);
		//sregex_iterator end1;

		//sregex_iterator arithmeticOpIterator(input.begin(), input.end(), arithmeticOpRegex);
		//sregex_iterator end2;

		//sregex_iterator boolaenOpIterator(input.begin(), input.end(), boolenOpRegex);
		//sregex_iterator end3;

		//sregex_iterator keywordsIterator(input.begin(), input.end(), keywordsRegex);
		//sregex_iterator end4;

		//sregex_iterator stringIterator(input.begin(), input.end(), stringLiteralRegex);
		//sregex_iterator end5;

		//sregex_iterator numbersIterator(input.begin(), input.end(), numbersRegex);
		//sregex_iterator end6;



		//while (delimiterIterator != end1)
		//{
		//	cout << "< " << delimiterIterator->str() << " , Delimiter > " << endl;
		//	delimiterIterator++;
		//}

		//while (arithmeticOpIterator != end2)
		//{
		//	cout << "< " << arithmeticOpIterator->str() << " , Operator > " << endl;
		//	arithmeticOpIterator++;
		//}

		//while (boolaenOpIterator != end3)
		//{
		//	cout << "< " << boolaenOpIterator->str() << " , Operator > " << endl;
		//	boolaenOpIterator++;
		//}

		//while (keywordsIterator != end4)
		//{
		//	cout << "< " << keywordsIterator->str() << " , Keyword > " << endl;
		//	keywordsIterator++;
		//}

		//while (stringIterator != end5)
		//{
		//	cout << "< " << stringIterator->str() << " , String Literal > " << endl;
		//	stringIterator++;
		//}

		//while (numbersIterator != end6)
		//{
		//	cout << "< " << numbersIterator->str() << " , Number > " << endl;
		//	numbersIterator++;
		//}


	}
}
