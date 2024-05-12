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
// #define Test1
// #define Test2
// #define Test3
#define Test4

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
    ifstream MyReadFile("C:\\Users\\Seif Yasser\\Desktop\\C-Compiler-Team10\\Test_4.txt");
#endif

    Lexer lexer = Lexer();
    tokenVector2 = lexer.getTokens(MyReadFile, myText);

    for (const auto &x : tokenVector2)
    {
        tokenTable.addRow(x.lexeme, x.type);
    }
    tokenTable.print(cout);
    cout << "Number of Tokens is: " << tokenVector2.size() << endl;

    cout << "==================================================================================================" << endl;
    cout << "==================================================================================================" << endl;
    Parser2 parser(tokenVector2);
    if (parser.parseProgram())
    {
        cout << "Parsing successful!" << endl;
    }
    else
    {
        cout << "Parsing failed!" << endl;
    }
    cout << "Number of Unique Identifiers is: " << parser.SymbolTable.size() << endl;
    for (auto x : parser.SymbolTable)
    {
        cout << x.first << " " << x.second << endl;
    }
    // parser.SymbolTable
}
