#include <iostream>
#include <regex>
#include<vector>
//#include<pair>
using namespace std;

const string keywords[44] = {
"auto","static","const",
"_Alignas","sizeof","break",
"inline","while","_Alignof",
"_Generic","case","long",
"for","_Atomic","_Imaginary",
"char","short","if",
"_Bool","_Noreturn","int",
"struct","do","typedef",
"_Complex","float","union",
"return","else","_Static_assert",
"double","enum","extern",
"void","_Thread_local",
"signed","unsigned","register",
"switch","volatile","continue",
"goto","restrict","default"
};

const string STDfunctions[11] = {
	"printf","scanf","strlen",
	"strcpy","strcmp","strcat",
	"malloc","free","fgets",
	"fprintf","toupper"
};

const string Delimiters[19]{
	 ",",
	 ";",
	 "(",
	 ")",
	 "[",
	 "]",
	 "{",
	 "#",
	 "?"
};

const string Operators[9]
{
	 "+" ,
	 "-" ,
	 "*" ,
	 "/" ,
	 ">" ,
	 "<" ,
	 "=" ,
	 "+",
	 "--"
};


const string BooleanOperator[16]
{
			 "==",
			 "!=",
			 ">",
			 "<",
			 "<=",
			 ">=",
			 "&&",
			 "||",
			 "!",
			 "~",
			 "?:",
			 "&",
			 "|",
			 "^",
			 "<<",
			 ">>"
};

int main()
{

	string input;
	while (true)
	{
		getline(cin, input);
		/*cin >> input;
		cin >> ws;*/
		vector<string> linesofcode;
		vector<string> binaryNumbers;
		vector<string> decimalNumbers;
		vector<string> octalNumbers;
		vector<string> hexaNumbers;
		vector<string> ExpoNumbers;
		vector<string> floatNumbers;

		//vector<pair(string identifier, string value)> symbolTable;
		//int|float|double|  



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


		regex delimitersRegex("\\{|\\}|\\(|\\)|;|,|\\[|\\]|,|\\.|:");
		regex arithmeticOpRegex("(\\+|-|\\*|\\/|%|\\+\\+|--)");
		regex boolenOpRegex("(>=|<=|==|!=|>|<|\\&\&|\\|\\||!|&|\\||\\^|~|<<|>>|\\?|\\.\\s|->|\\*)");
		regex keywordsRegex("auto|static|const|_Alignas|sizeof|break|inline|while|_Alignof|_Generic|case|long|for|_Atomic|_Imaginary|char|short|if|_Bool|_Noreturn|int|struct|do|typedef|_Complex|float|union|return|else|_Static_assert|double|enum|extern|void|_Thread_local|signed|unsigned|register|switch|volatile|continue|goto|restrict|default");
		regex stringLiteralRegex(R"(\".*\")");
		regex numbersRegex(R"(((\+|-)?0[0-7]*)|(^[-+]?(0|[1-9][0-9]*)))");


		/*regex myRegex("\".*\"|([a-zA-Z_][a-zA-Z0-9_]*)|\\(|\\)|\\{|\\}|;|[0-9]+|,|=");*/
		/*regex binaryNum("(\\+|-)?0(b|B)[0-1]+");
		regex hexaNum("(\\+|-)?0(x|X)[0-9a-fA-F]+");
		regex ExpoNum("((\\+-)*\\+?|(-\\+)*-?)(0|[1-9][0-9]*)((e|E)(\\+|-)?[0-9]+)");
		regex decimalNum("(\\+|-)?(0|[1-9][0-9]*)");
		regex floatNum("^[-+]?[0-9]*\\.?[0-9]+$");
		regex octalNum("(\\+|-)?0[0-7]*");
		*/
		//smatch matches;
		//if (regex_match(input, delimitersRegex))
		//	cout<< 





		linesofcode.push_back(input);
		/*binaryNumbers.push_back(input);
		decimalNumbers.push_back(input);
		octalNumbers.push_back(input);
		hexaNumbers.push_back(input);
		ExpoNumbers.push_back(input);
		floatNumbers.push_back(input);*/



		for (auto line : linesofcode)
		{
			sregex_iterator myRegexIterator(line.begin(), line.end(), numbersRegex);
			sregex_iterator end1;

			/*sregex_iterator octalIterator(line.begin(), line.end(), octalNum);
			sregex_iterator end2;*/


			/*while (octalIterator != end2)
			{
				cout << "< " << octalIterator->str() << " , Octal Numbers >" << endl;
				octalIterator++;
			}*/

			while (myRegexIterator != end1)
			{
				cout << "< " << myRegexIterator->str() << " , Numbers >" << endl;
				myRegexIterator++;
			}


		}


	}
}

