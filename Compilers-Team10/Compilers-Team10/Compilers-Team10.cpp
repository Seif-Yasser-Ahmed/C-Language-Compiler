#include <iostream>
#include <regex>
#include<vector>
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
	 " ",
	 "+",
	 "-",
	 "*",
	 "/",
	 "=",
	 ",",
	 ";",
	 "%",
	 "^",
	 ">",
	 "<",
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
		cin >> input;
		vector<string> linesofcode;
		linesofcode.push_back(input);


		smatch matches;


		regex myRegex("\".*\"|([a-zA-Z_][a-zA-Z0-9_]*)|\\(|\\)|\\{|\\}|;|[0-9]+|,|=");
		/*	regex decimalNum("(\\+|-)?(0|[1-9][0-9]*)");
			regex octalNum("(\\+|-)?0[0-7]*");
			regex binaryNum("(\\+|-)?0(b|B)[0-1]+");
			regex hexaNum("(\\+|-)?0(x|X)[0-9a-fA-F]+");
			regex floatNum("((\\+-)*\\+?|(-\\+)*-?)(0|[1-9][0-9]*)((e|E)(\\+|-)?[0-9]+)?");*/


		for (auto line : linesofcode)
		{
			sregex_iterator myRegexIterator(line.begin(), line.end(), myRegex);
			sregex_iterator end;

			while (myRegexIterator != end)
			{
				for (int i = 0; i < 44; i++)
					if (myRegexIterator->str() == keywords[i])
						cout << "< " << myRegexIterator->str() << " , Keyword >" << endl;

				for (int i = 0; i < 11; i++)
					if (myRegexIterator->str() == STDfunctions[i])
						cout << "< " << myRegexIterator->str() << " , Function >" << endl;

				for (int i = 0; i < 19; i++)
					if (myRegexIterator->str() == Delimiters[i])
						cout << "< " << myRegexIterator->str() << " , Delimiters >" << endl;

				for (int i = 0; i < 9; i++)
					if (myRegexIterator->str() == Operators[i])
						cout << "< " << myRegexIterator->str() << " , Operators >" << endl;


				for (int i = 0; i < 16; i++)
					if (myRegexIterator->str() == BooleanOperator[i])
						cout << "< " << myRegexIterator->str() << " , Boolean Operators >" << endl;





				myRegexIterator++;
			}
		}

	}
}

