// #include "Lexer.h"
#include <iostream>
#include <regex>
#include <vector>
#include <sstream>
#include <fstream>
#include <iterator>
// #include <map>
// #include "VariadicTable.h"
// #include "Parser.cpp"
#include "Lexer.h"
#include "Token.h"
// #include "Lexer.cpp"

using namespace std;

Lexer::Lexer()
{
    regex commentRegex1(R"(\/\/.*|\/\*.*\*\/)");
    regex keywordsRegex1(R"(\b(auto|static|const|_Alignas|sizeof|break|inline|while|_Alignof|_Generic|case|long|for|_Atomic|_Imaginary|char|short|if|_Bool|_Noreturn|int|struct|do|typedef|_Complex|float|union|return|else|_Static_assert|double|enum|extern|void|_Thread_local|signed|unsigned|register|switch|volatile|continue|goto|restrict|default)\b)");

    regex booleanOpRegex1(R"((>=|<=|==|!=|>>|<<|\&\&|\|\||!|\&|\||\^|~|<|>|\?|\.\s|->))");

    regex IdRegex1(R"((?:[_a-zA-Z][_a-zA-Z0-9]*|0x[0-9a-fA-F]+|0b[01]+))");

    regex numbersRegex1(R"(((-\+)*-?(0|[1-9][0-9]*)?(\.)?([1-9][0-9]*)(((e|E)(\+|-)?[0-9]+)?)|(0[bB][01]+|0[xX][0-9a-fA-F]+|0[0-7]*|[1-9][0-9]*)))");

    regex delimitersRegex1(R"(\{|\}|\(|\)|;|,|\[|\]|\.|:)");

    regex arithmeticOpRegex1(R"((\+\+|--|\*|\/|%|\+|-|=))");

    regex stringLiteralRegex1(R"(\".*\")");
    commentRegex = commentRegex1;
    keywordsRegex = keywordsRegex1;
    booleanOpRegex = booleanOpRegex1;
    IdRegex = IdRegex1;
    numbersRegex = numbersRegex1;
    delimitersRegex = delimitersRegex1;
    arithmeticOpRegex = arithmeticOpRegex1;
    stringLiteralRegex = stringLiteralRegex1;
}

Lexer::~Lexer() {}

/*-----------------------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------*/

// Lexer::Lexer(ifstream MyReadFile1, string myText) {}

void Lexer::Tokenize()
{
}

vector<Token> Lexer::getTokens(std::ifstream &MyReadFile, string myText)
{
    vector<Token> tokenVector1;

    while (getline(MyReadFile, myText))
    {
        string str = myText;
        istringstream iss(str);

        /*----------------Tokenization-------------------*/
        do
        {
            string subs;
            iss >> subs;
            if (subs[0] == '/' && subs[1] == '/')
            {
                break;
            }
            if (subs[0] == '/' && subs[1] == '*')
            {
                while (subs[subs.length() - 2] != '*' && subs[subs.length() - 1] != '/')
                {
                    string temp;
                    iss >> temp;
                    subs += " " + temp;
                }
            }
            if (subs[0] == '\"' && subs[subs.length() - 1] != '\"')
            {
                while (subs[subs.length() - 1] != '\"')
                {
                    string temp;
                    iss >> temp;
                    subs += " " + temp;
                }
            }
            if (subs == "\n" || subs == " " || subs == "" || subs == "\t" || subs == "\r" || subs == "\r\n" || subs == "\n\r" || subs == "\r\n" || subs == "\n\r")
            {
                continue;
            }
            linesofcode.push_back(subs);
            // cout << subs << endl;
        } while (iss);
    }
    tokensSize = linesofcode.size();

    /*-----------------------------------------------*/
    for (int i = 0; i < tokensSize; i++)
    {
        isStringLiteral = false;
        boolOp = false;

        /*----------------Comments----------------------*/
        if (regex_match(linesofcode[i], commentRegex))
        {
            continue;
        }

        /*----------------Keywords---------------------------*/
        if (regex_search(linesofcode[i], match, keywordsRegex))
        {
            cout << "<< Keyword ," << match.str(0) << " >>" << endl;
            Token token1 = Token();
            token1.setToken(match.str(0), "Keyword");
            tokenVector1.push_back(token1);
        };
        tokenVector.push_back(pair<string, string>(match.str(0), "Keyword"));

        /*----------------Identifiers-------------------*/
        if (regex_search(linesofcode[i], match, IdRegex) && linesofcode[i] != "quit")
        {
            string temp = match.str(0);
            if (!regex_search(temp, match, keywordsRegex))
            {
                if (!regex_match(temp, match, numbersRegex))
                {
                    if (!regex_search(temp, match, stringLiteralRegex) && !regex_search(linesofcode[i], match, stringLiteralRegex))
                    {
                        if (!regex_search(temp, match, commentRegex))
                        {
                            cout << "<< Identifier ," << temp << " >>" << endl;
                            Token token1 = Token();
                            token1.setToken(temp, "Identifier");
                            tokenVector1.push_back(token1);
                            tokenVector.push_back(pair<string, string>(temp, "Identifier"));
                        }
                    }
                }
            }
        }

        /*----------------------------Delimiters--------------------------------*/
        auto start = linesofcode[i].cbegin();
        while (regex_search(start, linesofcode[i].cend(), match, delimitersRegex))
        {

            string temp = match.str(0);
            if (!regex_search(linesofcode[i], numbersRegex))
            {
                cout << "<< Delimiter ," << match.str(0) << "  >>" << endl;
                cout << match.str(0).size() << endl;
                Token token1 = Token();
                token1.setToken(match.str(0), "Delimiter");
                tokenVector1.push_back(token1);
                tokenVector.push_back(pair<string, string>(match.str(0), "Delimiter"));
            }
            start = match[0].second;
        }

        /*----------------String Literals-------------------*/
        // start = linesofcode[i].cbegin();
        if (regex_search(linesofcode[i], match, stringLiteralRegex))
        {
            cout << "<< String Literal , " << match.str(0) << "  >>" << endl;
            Token token1 = Token();
            token1.setToken(match.str(0), "String Literal");
            tokenVector1.push_back(token1);
            tokenVector.push_back(pair<string, string>(match.str(0), "String Literal"));
            start = match[0].second;
            isStringLiteral = true;
        }

        /*---------------Boolean Operators--------------------*/
        if (!isStringLiteral)
        {
            if (regex_search(linesofcode[i], match, booleanOpRegex))
            {
                if (match.str(0) == ">=")
                {
                    string s = "More than or Equal Operator";
                    cout << "<< " << s << " ," << match.str(0) << "  >>" << endl;
                    Token token1 = Token();
                    token1.setToken(match.str(0), s);
                    tokenVector1.push_back(token1);
                    tokenVector.push_back(pair<string, string>(match.str(0), s));

                    boolOp = true;
                }
                else if (match.str(0) == "<=")
                {
                    string s = "Less than or Equal Operator";
                    cout << "<< Less than or Equal Operator ," << match.str(0) << "  >>" << endl;
                    cout << "<< " << s << " ," << match.str(0) << "  >>" << endl;
                    cout << "<< " << s << " ," << match.str(0) << "  >>" << endl;
                    Token token1 = Token();
                    token1.setToken(match.str(0), s);
                    tokenVector1.push_back(token1);
                    tokenVector.push_back(pair<string, string>(match.str(0), s));

                    boolOp = true;
                }
                else if (match.str(0) == "==")
                {
                    string s = "Equality Operator";
                    cout << "<< Equality Operator ," << match.str(0) << " >>" << endl;
                    cout << "<< " << s << " ," << match.str(0) << "  >>" << endl;
                    cout << "<< " << s << " ," << match.str(0) << "  >>" << endl;
                    Token token1 = Token();
                    token1.setToken(match.str(0), s);
                    tokenVector1.push_back(token1);
                    tokenVector.push_back(pair<string, string>(match.str(0), s));

                    boolOp = true;
                }
                else if (match.str(0) == "!=")
                {
                    string s = "Not Equal Operator";
                    cout << "<< " << s << " ," << match.str(0) << "  >>" << endl;
                    cout << "<< " << s << " ," << match.str(0) << "  >>" << endl;
                    Token token1 = Token();
                    token1.setToken(match.str(0), s);
                    tokenVector1.push_back(token1);
                    tokenVector.push_back(pair<string, string>(match.str(0), s));

                    boolOp = true;
                }
                else if (match.str(0) == "<")
                {
                    string s = "Less than Operator";
                    cout << "<< " << s << " ," << match.str(0) << "  >>" << endl;
                    cout << "<< " << s << " ," << match.str(0) << "  >>" << endl;
                    Token token1 = Token();
                    token1.setToken(match.str(0), s);
                    tokenVector1.push_back(token1);
                    tokenVector.push_back(pair<string, string>(match.str(0), s));
                }
                else if (match.str(0) == ">")
                {
                    string s = "More Operator";
                    cout << "<< " << s << " ," << match.str(0) << "  >>" << endl;
                    cout << "<< " << s << " ," << match.str(0) << "  >>" << endl;
                    Token token1 = Token();
                    token1.setToken(match.str(0), s);
                    tokenVector1.push_back(token1);
                    tokenVector.push_back(pair<string, string>(match.str(0), s));
                }
                else if (match.str(0) == "&&")
                {
                    string s = "Logical AND Operator";
                    cout << "<< " << s << " ," << match.str(0) << "  >>" << endl;
                    cout << "<< " << s << " ," << match.str(0) << "  >>" << endl;
                    Token token1 = Token();
                    token1.setToken(match.str(0), s);
                    tokenVector1.push_back(token1);
                    tokenVector.push_back(pair<string, string>(match.str(0), s));
                }
                else if (match.str(0) == "||")
                {
                    string s = "Logical OR Operator";
                    cout << "<< " << s << " ," << match.str(0) << "  >>" << endl;
                    cout << "<< " << s << " ," << match.str(0) << "  >>" << endl;
                    Token token1 = Token();
                    token1.setToken(match.str(0), s);
                    tokenVector1.push_back(token1);
                    tokenVector.push_back(pair<string, string>(match.str(0), s));
                }
                else if (match.str(0) == "!")
                {
                    string s = "Logical NOT Operator";
                    cout << "<< " << s << " ," << match.str(0) << "  >>" << endl;
                    cout << "<< " << s << " ," << match.str(0) << "  >>" << endl;
                    Token token1 = Token();
                    token1.setToken(match.str(0), s);
                    tokenVector1.push_back(token1);
                    tokenVector.push_back(pair<string, string>(match.str(0), s));
                }
                else if (match.str(0) == "&")
                {
                    string s = "Bitwise AND Operator";
                    cout << "<< " << s << " ," << match.str(0) << "  >>" << endl;
                    cout << "<< " << s << " ," << match.str(0) << "  >>" << endl;
                    Token token1 = Token();
                    token1.setToken(match.str(0), s);
                    tokenVector1.push_back(token1);
                    tokenVector.push_back(pair<string, string>(match.str(0), s));
                }
                else if (match.str(0) == "|")
                {
                    string s = "Bitwise OR Operator";
                    cout << "<< " << s << " ," << match.str(0) << "  >>" << endl;
                    cout << "<< " << s << " ," << match.str(0) << "  >>" << endl;
                    Token token1 = Token();
                    token1.setToken(match.str(0), s);
                    tokenVector1.push_back(token1);
                    tokenVector.push_back(pair<string, string>(match.str(0), s));
                }
                else if (match.str(0) == "^")
                {
                    string s = "Bitwise XOR Operator";
                    cout << "<< " << s << " ," << match.str(0) << "  >>" << endl;
                    cout << "<< " << s << " ," << match.str(0) << "  >>" << endl;
                    Token token1 = Token();
                    token1.setToken(match.str(0), s);
                    tokenVector1.push_back(token1);
                    tokenVector.push_back(pair<string, string>(match.str(0), s));
                }
                else if (match.str(0) == "~")
                {
                    string s = "Bitwise NOT Operator";
                    cout << "<< " << s << " ," << match.str(0) << "  >>" << endl;
                    cout << "<< " << s << " ," << match.str(0) << "  >>" << endl;
                    Token token1 = Token();
                    token1.setToken(match.str(0), s);
                    tokenVector1.push_back(token1);
                    tokenVector.push_back(pair<string, string>(match.str(0), s));
                }
                else if (match.str(0) == ">>")
                {
                    string s = "Shift Right Operator";
                    cout << "<< " << s << " ," << match.str(0) << "  >>" << endl;
                    cout << "<< " << s << " ," << match.str(0) << "  >>" << endl;
                    Token token1 = Token();
                    token1.setToken(match.str(0), s);
                    tokenVector1.push_back(token1);
                    tokenVector.push_back(pair<string, string>(match.str(0), s));
                }
                else if (match.str(0) == "<<")
                {
                    string s = "Shift Left Operator";
                    cout << "<< " << s << " ," << match.str(0) << "  >>" << endl;
                    cout << "<< " << s << " ," << match.str(0) << "  >>" << endl;
                    Token token1 = Token();
                    token1.setToken(match.str(0), s);
                    tokenVector1.push_back(token1);
                    tokenVector.push_back(pair<string, string>(match.str(0), s));
                }
                else if (match.str(0) == "?")
                {
                    string s = "Ternary Conditional Operator";
                    cout << "<< " << s << " ," << match.str(0) << "  >>" << endl;
                    cout << "<< " << s << " ," << match.str(0) << "  >>" << endl;
                    Token token1 = Token();
                    token1.setToken(match.str(0), s);
                    tokenVector1.push_back(token1);
                    tokenVector.push_back(pair<string, string>(match.str(0), s));
                }
                else if (match.str(0) == ".")
                {
                    string s = "Operator";
                    cout << "<< " << s << " ," << match.str(0) << "  >>" << endl;
                    cout << "<< " << s << " ," << match.str(0) << "  >>" << endl;
                    Token token1 = Token();
                    token1.setToken(match.str(0), s);
                    tokenVector1.push_back(token1);
                    tokenVector.push_back(pair<string, string>(match.str(0), s));
                }
                else if (match.str(0) == "->")
                {
                    string s = "Operator";
                    cout << "<< " << s << " ," << match.str(0) << "  >>" << endl;
                    cout << "<< " << s << " ," << match.str(0) << "  >>" << endl;
                    Token token1 = Token();
                    token1.setToken(match.str(0), s);
                    tokenVector1.push_back(token1);
                    tokenVector.push_back(pair<string, string>(match.str(0), s));
                    boolOp = true;
                }
            }
        }

        /*------------Arithmetic Operators-----------------------*/
        if (!isStringLiteral)
        {
            if (regex_search(linesofcode[i], match, arithmeticOpRegex))
            {
                string temp = match.str(0);
                if (!boolOp)
                {
                    if (match.str(0) == "=")
                    {
                        cout << "<< Assignment Operator ," << match.str(0) << " >>" << endl;
                        // cout << "<< " << s << " ," << match.str(0) << "  >>" << endl;
                        Token token1 = Token();
                        token1.setToken(match.str(0), "Assignment Operator");
                        tokenVector1.push_back(token1);
                        tokenVector.push_back(pair<string, string>(match.str(0), "Assignment Operator"));
                    }
                    else if (match.str(0) == "+")
                    {
                        cout << "<< Addition Operator ," << match.str(0) << "  >>" << endl;
                        Token token1 = Token();
                        token1.setToken(match.str(0), "addition Operator");
                        tokenVector1.push_back(token1);
                        tokenVector.push_back(pair<string, string>(match.str(0), "addition Operator"));
                    }
                    else if (match.str(0) == "-")
                    {
                        cout << "<< Subtraction Operator ," << match.str(0) << "  >>" << endl;
                        Token token1 = Token();
                        token1.setToken(match.str(0), "subtraction Operator");
                        tokenVector1.push_back(token1);
                        tokenVector.push_back(pair<string, string>(match.str(0), "subtraction Operator"));
                    }
                    else if (match.str(0) == "*")
                    {
                        cout << "<< Multiplicative Operator ," << match.str(0) << "  >>" << endl;
                        Token token1 = Token();
                        token1.setToken(match.str(0), "multiplicative Operator");
                        tokenVector1.push_back(token1);
                        tokenVector.push_back(pair<string, string>(match.str(0), "multiplicative Operator"));
                    }
                    else if (match.str(0) == "/")
                    {
                        cout << "<< Division Operator ," << match.str(0) << "  >>" << endl;
                        Token token1 = Token();
                        token1.setToken(match.str(0), "division Operator");
                        tokenVector1.push_back(token1);
                        tokenVector.push_back(pair<string, string>(match.str(0), "division Operator"));
                    }
                    else if (match.str(0) == "%")
                    {
                        cout << "<< Remainder Operator ," << match.str(0) << " >>" << endl;
                        Token token1 = Token();
                        token1.setToken(match.str(0), "remainder Operator");
                        tokenVector1.push_back(token1);
                        tokenVector.push_back(pair<string, string>(match.str(0), "remainder Operator"));
                    }
                    else if (match.str(0) == "++")
                    {
                        cout << "<< Addition Unary Operator ," << match.str(0) << "  >>" << endl;
                        Token token1 = Token();
                        token1.setToken(match.str(0), "Addition Unary Operator");
                        tokenVector1.push_back(token1);
                        tokenVector.push_back(pair<string, string>(match.str(0), "Addition Unary Operator"));
                    }
                    else if (match.str(0) == "--")
                    {
                        cout << "<< Subtraction Unary Operator ," << match.str(0) << "  >>" << endl;
                        Token token1 = Token();
                        token1.setToken(match.str(0), "subtraction Unary Operator");
                        tokenVector1.push_back(token1);
                        tokenVector.push_back(pair<string, string>(match.str(0), "subtraction Unary Operator"));
                    }
                }
            }
        }

        /*----------------Numbers----------------------------*/
        if (regex_search(linesofcode[i], match, numbersRegex))
        {
            string temp = match.str(0);
            if (temp.find("0x") != string::npos)
            {
                cout << "<< Hexadecimal Number ," << temp << "  >>" << endl;
                Token token1 = Token();
                token1.setToken(match.str(0), "Hexadecimal Number");
                tokenVector1.push_back(token1);
                tokenVector.push_back(pair<string, string>(temp, "Hexadecimal Number"));
            }
            else if (temp.find("0b") != string::npos)
            {
                cout << "<< Binary Number ," << temp << "  >>" << endl;
                Token token1 = Token();
                token1.setToken(match.str(0), "Binary Number");
                tokenVector1.push_back(token1);
                tokenVector.push_back(pair<string, string>(temp, "Binary Number"));
            }
            else if (temp.find("e") != string::npos)
            {
                cout << "<< Scientific Notation Number ," << temp << "  >>" << endl;
                Token token1 = Token();
                token1.setToken(match.str(0), "Scientific Notation Number");
                tokenVector1.push_back(token1);
                tokenVector.push_back(pair<string, string>(temp, "Scientific Notation Number"));
            }
            else if (temp.find(".") != string::npos)
            {
                cout << "<< Floating Point Number ," << temp << " >>" << endl;
                Token token1 = Token();
                token1.setToken(match.str(0), "Floating Point Number");
                tokenVector1.push_back(token1);
                tokenVector.push_back(pair<string, string>(temp, "Floating Point Number"));
            }
            else if (temp[0] == '0' && temp.length() > 1)
            {
                cout << "<< Octal Number ," << temp << "  >>" << endl;
                Token token1 = Token();
                token1.setToken(match.str(0), "Octal Number");
                tokenVector1.push_back(token1);
                tokenVector.push_back(pair<string, string>(temp, "Octal Number"));
            }
            else
            {
                cout << "<< Decimal Number ," << temp << "  >>" << endl;
                Token token1 = Token();
                token1.setToken(match.str(0), "Decimal Number");
                tokenVector1.push_back(token1);
                tokenVector.push_back(pair<string, string>(temp, "Decimal Number"));
            }
        }
    }
    return tokenVector1;
}