#include <iostream>
#include <regex>
#include <vector>
#include <sstream>
#include <fstream>
#include "VariadicTable.h"
using namespace std;

// #define Test1
//#define Test2
#define Test3

int main()
{
    int tokensSize = 0;
    string myText;
    string delimiter = " ";
    string token;
    vector<string> linesofcode;
    smatch match;
    bool boolOp = false;

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
            }
            start = match[0].second;
        }

        /*---------------Boolean Operators--------------------*/
        if (regex_search(linesofcode[i], match, booleanOpRegex))
        {
            if (match.str(0) == ">=")
            {
                cout << "<< More than or Equal Operator ," << match.str(0) << "  >>" << endl;
                boolOp = true;
            }
            else if (match.str(0) == "<=")
            {
                cout << "<< Less than or Equal Operator ," << match.str(0) << "  >>" << endl;
                boolOp = true;
            }
            else if (match.str(0) == "==")
            {
                cout << "<< Equality Operator ," << match.str(0) << " >>" << endl;
                boolOp = true;
            }
            else if (match.str(0) == "!=")
            {
                cout << "<< Not Equal Operator ," << match.str(0) << "  >>" << endl;
                boolOp = true;
            }
            else if (match.str(0) == "<")
                cout << "<<Less than Operator ," << match.str(0) << "  >>" << endl;
            else if (match.str(0) == ">")
                cout << "<<More Operator ," << match.str(0) << "   >>" << endl;
            else if (match.str(0) == "&&")
                cout << "<<Logical AND Operator ," << match.str(0) << "  >>" << endl;
            else if (match.str(0) == "||")
                cout << "<<Logical OR Operator ," << match.str(0) << " >>" << endl;
            else if (match.str(0) == "!")
                cout << "<<Logical NOT Operator ," << match.str(0) << "  >>" << endl;
            else if (match.str(0) == "&")
                cout << "<<Bitwise AND Operator ," << match.str(0) << " >>" << endl;
            else if (match.str(0) == "|")
                cout << "<<Bitwise OR Operator ," << match.str(0) << "  >>" << endl;
            else if (match.str(0) == "^")
                cout << "<<Bitwise XOR Operator ," << match.str(0) << "  >>" << endl;
            else if (match.str(0) == "~")
                cout << "<<Bitwise NOT Operator ," << match.str(0) << "  >>" << endl;
            else if (match.str(0) == ">>")
                cout << "<<Shift Right Operator ," << match.str(0) << "  >>" << endl;
            else if (match.str(0) == "<<")
                cout << "<<Shift Left Operator ," << match.str(0) << "   >>" << endl;
            else if (match.str(0) == "?")
                cout << "<<Ternary Conditional Operator ," << match.str(0) << "  >>" << endl;
            else if (match.str(0) == ".")
                cout << "<<Operator ," << match.str(0) << "  >>" << endl;
            else if (match.str(0) == "->")
            {
                cout << "<<Operator ," << match.str(0) << "   >>" << endl;
                boolOp = true;
            }
        }

        /*------------Arithmetic Operators-----------------------*/
        if (regex_search(linesofcode[i], match, arithmeticOpRegex))
        {
            string temp = match.str(0);
            if (!boolOp)
            {
                if (match.str(0) == "=")
                    cout << "<< Assignment Operator ," << match.str(0) << " >>" << endl;
                else if (match.str(0) == "+")
                    cout << "<< Addition Operator ," << match.str(0) << "  >>" << endl;
                else if (match.str(0) == "-")
                    cout << "<< Subtraction Operator ," << match.str(0) << "  >>" << endl;
                else if (match.str(0) == "*")
                    cout << "<< Multiplicative Operator ," << match.str(0) << "  >>" << endl;
                else if (match.str(0) == "/")
                    cout << "<< Division Operator ," << match.str(0) << "  >>" << endl;
                else if (match.str(0) == "%")
                    cout << "<< Remainder Operator ," << match.str(0) << " >>" << endl;
                else if (match.str(0) == "++")
                    cout << "<< Addition Unary Operator ," << match.str(0) << "  >>" << endl;
                else if (match.str(0) == "--")
                    cout << "<< Subtraction Unary Operator ," << match.str(0) << "  >>" << endl;
            }
        }

        /*----------------Numbers----------------------------*/
        if (regex_search(linesofcode[i], match, numbersRegex))
        {
            string temp = match.str(0);
            if (temp.find("0x") != string::npos)
            {
                cout << "<< Hexadecimal Number ," << temp << "  >>" << endl;
            }
            else if (temp.find("0b") != string::npos)
            {
                cout << "<< Binary Number ," << temp << "  >>" << endl;
            }
            else if (temp.find("e") != string::npos)
            {
                cout << "<< Scientific Notation Number ," << temp << "  >>" << endl;
            }
            else if (temp.find(".") != string::npos)
            {
                cout << "<< Floating Point Number ," << temp << " >>" << endl;
            }
            else if (temp[0] == '0')
            {
                cout << "<< Octal Number ," << temp << "  >>" << endl;
            }
            else
            {
                cout << "<< Decimal Number ," << temp << "  >>" << endl;
            }
        }

        /*----------------String Literals-------------------*/
        //start = linesofcode[i].cbegin();
        if (regex_search(linesofcode[i], match, stringLiteralRegex))
        {
            cout << "<< String Literal , " << match.str(0) << "  >>" << endl;
            start = match[0].second;
        }
    }
}


