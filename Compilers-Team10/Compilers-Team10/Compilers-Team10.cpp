#include <iostream>
#include <regex>
#include <vector>
#include <sstream>
#include <fstream>
#include <iterator>
#include <map>
#include "VariadicTable.h"
// #include "Parser.cpp"
#include "Parser2.cpp"
#include "Lexer.h"
#include "Lexer.cpp"
#include "Token.h"
#include "Token.cpp"
using namespace std;

/*Fix 10e4 Exponential number e4 (identifier) */
#define Test4
// #define Test2
// #define Test3

int main()
{
    std::vector<Token> tokenVector2;
    VariadicTable<string, string> tokenTable({"token", "Type"});
    string myText;

#ifdef Test1
    ifstream MyReadFile("C:\\Users\\Seif Yasser\\Desktop\\Compilers\\Project\\Compilers-Team10\\Test_1.txt");
#endif

#ifdef Test2
    ifstream MyReadFile("C:\\Users\\Seif Yasser\\Desktop\\Compilers\\Project\\Compilers-Team10\\Test_2.txt");
#endif

#ifdef Test3
    ifstream MyReadFile("C:\\Users\\Seif Yasser\\Desktop\\Compilers\\Project\\Compilers-Team10\\Test_3.txt");
#endif

#ifdef Test4
    ifstream MyReadFile("C:\\Users\\Seif Yasser\\Desktop\\Test-Case-1.txt");
#endif

    Lexer lexer = Lexer();
    tokenVector2 = lexer.getTokens(MyReadFile, myText);
    cout << tokenVector2[0].lexeme << endl;
    cout << tokenVector2[0].type << endl;

    for (const auto &x : tokenVector2)
    {
        tokenTable.addRow(x.lexeme, x.type);
    }
    tokenTable.print(cout);

    cout << "==================================================================================================" << endl;
    cout << "==================================================================================================" << endl;
    cout << tokenVector2[0].lexeme << endl;
    cout << tokenVector2[0].type << endl;
    Parser2 parser(tokenVector2);
    if (parser.parseProgram())
    {
        cout << "Parsing successful!" << endl;
    }
    else
    {
        cout << "Parsing failed!" << endl;
    }
}
