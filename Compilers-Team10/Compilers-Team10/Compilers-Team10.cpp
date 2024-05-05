#include <iostream>
#include <regex>
#include <vector>
#include <sstream>
#include <fstream>
#include <iterator>
#include <map>
#include "VariadicTable.h"
using namespace std;

/*Fix 10e4 Exponential number e4 (identifier) */
#define Test1
// #define Test2
// #define Test3

int main()
{
    vector<pair<string, string>> tokenVector;
    VariadicTable<string, string> tokenTable({"token", "Type"});
    int tokensSize = 0;
    string myText;
    string delimiter = " ";
    string token;
    vector<string> linesofcode;
    smatch match;
    bool boolOp = false;
    bool isStringLiteral = false;

#ifdef Test1
    ifstream MyReadFile("C:\\ASU\\ASU\\SEM 6\\Design of compilers\\Compilers-project\\Test_1.txt");
#endif

#ifdef Test2
    ifstream MyReadFile("C:\\ASU\\ASU\\SEM 6\\Design of compilers\\Compilers-project\\Test_2.txt");
#endif

#ifdef Test3
    ifstream MyReadFile("C:\\ASU\\ASU\\SEM 6\\Design of compilers\\Compilers-project\\Test_3.txt");
#endif

    //---------------------------------------------------------------------------------------
    regex commentRegex(R"(\/\/.*|\/\*.*\*\/)");

    regex keywordsRegex(R"(\b(auto|static|const|_Alignas|sizeof|break|inline|while|_Alignof|_Generic|case|long|for|_Atomic|_Imaginary|char|short|if|_Bool|_Noreturn|int|struct|do|typedef|_Complex|float|union|return|else|_Static_assert|double|enum|extern|void|_Thread_local|signed|unsigned|register|switch|volatile|continue|goto|restrict|default)\b)");

    regex booleanOpRegex(R"((>=|<=|==|!=|>>|<<|\&\&|\|\||!|\&|\||\^|~|<|>|\?|\.\s|->))");

    regex IdRegex(R"((?:[_a-zA-Z][_a-zA-Z0-9]*|0x[0-9a-fA-F]+|0b[01]+))");

    regex numbersRegex(R"(((-\+)*-?(0|[1-9][0-9]*)?(\.)?([1-9][0-9]*)(((e|E)(\+|-)?[0-9]+)?)|(0[bB][01]+|0[xX][0-9a-fA-F]+|0[0-7]*|[1-9][0-9]*)))");

    regex delimitersRegex(R"(\{|\}|\(|\)|;|,|\[|\]|\.|:)");

    regex arithmeticOpRegex(R"((\+\+|--|\*|\/|%|\+|-|=))");

    regex stringLiteralRegex(R"(\".*\")");

    /*-----------------------------------------------------------------------------------------*/
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
    /*-----------------------------------------------*/

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
            tokenVector.push_back(pair<string, string>(match.str(0), "Keyword"));
        }

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
                tokenVector.push_back(pair<string, string>(match.str(0), "Delimiter"));
            }
            start = match[0].second;
        }

        /*----------------String Literals-------------------*/
        // start = linesofcode[i].cbegin();
        if (regex_search(linesofcode[i], match, stringLiteralRegex))
        {
            cout << "<< String Literal , " << match.str(0) << "  >>" << endl;
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
                    tokenVector.push_back(pair<string, string>(match.str(0), s));

                    boolOp = true;
                }
                else if (match.str(0) == "<=")
                {
                    string s = "Less than or Equal Operator";
                    cout << "<< Less than or Equal Operator ," << match.str(0) << "  >>" << endl;
                    cout << "<< " << s << " ," << match.str(0) << "  >>" << endl;

                    tokenVector.push_back(pair<string, string>(match.str(0), s));

                    boolOp = true;
                }
                else if (match.str(0) == "==")
                {
                    string s = "Equality Operator";
                    cout << "<< Equality Operator ," << match.str(0) << " >>" << endl;
                    cout << "<< " << s << " ," << match.str(0) << "  >>" << endl;

                    tokenVector.push_back(pair<string, string>(match.str(0), s));

                    boolOp = true;
                }
                else if (match.str(0) == "!=")
                {
                    string s = "Not Equal Operator";
                    cout << "<< " << s << " ," << match.str(0) << "  >>" << endl;
                    tokenVector.push_back(pair<string, string>(match.str(0), s));

                    boolOp = true;
                }
                else if (match.str(0) == "<")
                {
                    string s = "Less than Operator";
                    cout << "<< " << s << " ," << match.str(0) << "  >>" << endl;
                    tokenVector.push_back(pair<string, string>(match.str(0), s));
                }
                else if (match.str(0) == ">")
                {
                    string s = "More Operator";
                    cout << "<< " << s << " ," << match.str(0) << "  >>" << endl;
                    tokenVector.push_back(pair<string, string>(match.str(0), s));
                }
                else if (match.str(0) == "&&")
                {
                    string s = "Logical AND Operator";
                    cout << "<< " << s << " ," << match.str(0) << "  >>" << endl;
                    tokenVector.push_back(pair<string, string>(match.str(0), s));
                }
                else if (match.str(0) == "||")
                {
                    string s = "Logical OR Operator";
                    cout << "<< " << s << " ," << match.str(0) << "  >>" << endl;
                    tokenVector.push_back(pair<string, string>(match.str(0), s));
                }
                else if (match.str(0) == "!")
                {
                    string s = "Logical NOT Operator";
                    cout << "<< " << s << " ," << match.str(0) << "  >>" << endl;
                    tokenVector.push_back(pair<string, string>(match.str(0), s));
                }
                else if (match.str(0) == "&")
                {
                    string s = "Bitwise AND Operator";
                    cout << "<< " << s << " ," << match.str(0) << "  >>" << endl;
                    tokenVector.push_back(pair<string, string>(match.str(0), s));
                }
                else if (match.str(0) == "|")
                {
                    string s = "Bitwise OR Operator";
                    cout << "<< " << s << " ," << match.str(0) << "  >>" << endl;
                    tokenVector.push_back(pair<string, string>(match.str(0), s));
                }
                else if (match.str(0) == "^")
                {
                    string s = "Bitwise XOR Operator";
                    cout << "<< " << s << " ," << match.str(0) << "  >>" << endl;
                    tokenVector.push_back(pair<string, string>(match.str(0), s));
                }
                else if (match.str(0) == "~")
                {
                    string s = "Bitwise NOT Operator";
                    cout << "<< " << s << " ," << match.str(0) << "  >>" << endl;
                    tokenVector.push_back(pair<string, string>(match.str(0), s));
                }
                else if (match.str(0) == ">>")
                {
                    string s = "Shift Right Operator";
                    cout << "<< " << s << " ," << match.str(0) << "  >>" << endl;
                    tokenVector.push_back(pair<string, string>(match.str(0), s));
                }
                else if (match.str(0) == "<<")
                {
                    string s = "Shift Left Operator";
                    cout << "<< " << s << " ," << match.str(0) << "  >>" << endl;
                    tokenVector.push_back(pair<string, string>(match.str(0), s));
                }
                else if (match.str(0) == "?")
                {
                    string s = "Ternary Conditional Operator";
                    cout << "<< " << s << " ," << match.str(0) << "  >>" << endl;
                    tokenVector.push_back(pair<string, string>(match.str(0), s));
                }
                else if (match.str(0) == ".")
                {
                    string s = "Operator";
                    cout << "<< " << s << " ," << match.str(0) << "  >>" << endl;
                    tokenVector.push_back(pair<string, string>(match.str(0), s));
                }
                else if (match.str(0) == "->")
                {
                    string s = "Operator";
                    cout << "<< " << s << " ," << match.str(0) << "  >>" << endl;
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
                        tokenVector.push_back(pair<string, string>(match.str(0), "Assignment Operator"));
                    }
                    else if (match.str(0) == "+")
                    {
                        cout << "<< Addition Operator ," << match.str(0) << "  >>" << endl;
                        tokenVector.push_back(pair<string, string>(match.str(0), "addition Operator"));
                    }
                    else if (match.str(0) == "-")
                    {
                        cout << "<< Subtraction Operator ," << match.str(0) << "  >>" << endl;
                        tokenVector.push_back(pair<string, string>(match.str(0), "subtraction Operator"));
                    }
                    else if (match.str(0) == "*")
                    {
                        cout << "<< Multiplicative Operator ," << match.str(0) << "  >>" << endl;
                        tokenVector.push_back(pair<string, string>(match.str(0), "multiplicative Operator"));
                    }
                    else if (match.str(0) == "/")
                    {
                        cout << "<< Division Operator ," << match.str(0) << "  >>" << endl;
                        tokenVector.push_back(pair<string, string>(match.str(0), "division Operator"));
                    }
                    else if (match.str(0) == "%")
                    {
                        cout << "<< Remainder Operator ," << match.str(0) << " >>" << endl;
                        tokenVector.push_back(pair<string, string>(match.str(0), "remainder Operator"));
                    }
                    else if (match.str(0) == "++")
                    {
                        cout << "<< Addition Unary Operator ," << match.str(0) << "  >>" << endl;
                        tokenVector.push_back(pair<string, string>(match.str(0), "Addition Unary Operator"));
                    }
                    else if (match.str(0) == "--")
                    {
                        cout << "<< Subtraction Unary Operator ," << match.str(0) << "  >>" << endl;
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
                tokenVector.push_back(pair<string, string>(temp, "Hexadecimal Number"));
            }
            else if (temp.find("0b") != string::npos)
            {
                cout << "<< Binary Number ," << temp << "  >>" << endl;
                tokenVector.push_back(pair<string, string>(temp, "Binary Number"));
            }
            else if (temp.find("e") != string::npos)
            {
                cout << "<< Scientific Notation Number ," << temp << "  >>" << endl;
                tokenVector.push_back(pair<string, string>(temp, "Scientific Notation Number"));
            }
            else if (temp.find(".") != string::npos)
            {
                cout << "<< Floating Point Number ," << temp << " >>" << endl;
                tokenVector.push_back(pair<string, string>(temp, "Floating Point Number"));
            }
            else if (temp[0] == '0')
            {
                cout << "<< Octal Number ," << temp << "  >>" << endl;
                tokenVector.push_back(pair<string, string>(temp, "Octal Number"));
            }
            else
            {
                cout << "<< Decimal Number ," << temp << "  >>" << endl;
                tokenVector.push_back(pair<string, string>(temp, "Decimal Number"));
            }
        }
    }

    for (const auto &pair : tokenVector)
    {
        cout << pair.first << ": " << pair.second << endl;
        tokenTable.addRow(pair.first, pair.second);
    }
    tokenTable.print(cout);
}
