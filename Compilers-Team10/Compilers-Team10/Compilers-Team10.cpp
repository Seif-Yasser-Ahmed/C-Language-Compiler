#include <iostream>
#include <regex>
#include <vector>
#include <sstream>
#include <fstream>
#include <iterator>
#include <map>
#include "VariadicTable.h"
//#include "Parser.cpp"
#include "Lexer.h"
#include "Lexer.cpp"

using namespace std;

/*Fix 10e4 Exponential number e4 (identifier) */
#define Test1
// #define Test2
// #define Test3

int main()
{
    vector<pair<string, string>> tokenVector;
    VariadicTable<string, string> tokenTable({ "token", "Type" });
    int tokensSize = 0;
    string myText;
    string delimiter = " ";
    string token;
    vector<string> linesofcode;
    smatch match;
    bool boolOp = false;
    bool isStringLiteral = false;

#ifdef Test1
    ifstream MyReadFile("C:\\Users\\Seif Yasser\\Desktop\\Compilers\\Project\\Compilers-Team10\\Test_1.txt");
#endif

#ifdef Test2
    ifstream MyReadFile("C:\\Users\\Seif Yasser\\Desktop\\Compilers\\Project\\Compilers-Team10\\Test_2.txt");
#endif

#ifdef Test3
    ifstream MyReadFile("C:\\Users\\Seif Yasser\\Desktop\\Compilers\\Project\\Compilers-Team10\\Test_3.txt");
#endif


    
    Lexer lexer=Lexer();
    /*lexer.Tokenize(MyReadFile, myText);
    tokenVector=lexer.getTokens();*/

    //tokensSize = linesofcode.size();


    for (const auto& pair : tokenVector)
    {
        cout << pair.first << ": " << pair.second << endl;
        tokenTable.addRow(pair.first, pair.second);
    }
    tokenTable.print(cout);
    cout << "=================================================================================================="<<endl;

    cout << "==================================================================================================" << endl;
    // replace with actual tokens from our scanner, this vector is made to store the tokens 
    //vector<Token> tokens = tokenVector;

    //Parser parser(tokens);
    //if (parser.parseProgram()) {
    //    cout << "Parsing successful!" << endl;
    //}
    //else {
    //    cout << "Parsing failed!" << endl;
    //}
}