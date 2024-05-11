//============================================================================================
//============================================================================================
//============================================================================================
//============================================================================================
//=================================== Last Version 10/5  =====================================
//============================================================================================
//============================================================================================
//============================================================================================
//============================================================================================

#include <iostream>
#include <vector>
#include <string>
#include "Token.h"
// #include "Token.cpp"
using namespace std;
// struct Token
// {
//     string lexeme; // the string
//     string type;
//     int num;
// };

class Parser2
{
public:
    // Token token = new Token();
    Parser2(const vector<Token> &tokens) : tokens(tokens), currentTokenIndex(0) {}

    bool parseProgram()
    {
        return parseDeclarationList(); // we check with this if parsing successful
    }

    vector<pair<string, string>> SymbolTable; // make the symbol table
private:
    //--------------------------------------------------------------------------------
    bool returned = false;
    const vector<Token> &tokens; // vector of token
    size_t currentTokenIndex;    // 3ashan netabe3 el tokens index
    bool ifCond = false;
    int noOfBlocks = 0;
    int noOfCalls = 0;
    string temp;
    string temp2;
    //--------------------------------------------------------------------------------

    bool isDataType(string lexeme)
    {
        // cout << lexeme << 11111111 << endl;
        temp2 = getCurrentToken().lexeme;
        // if()

        return (lexeme == "float" || lexeme == "int" || lexeme == "char" || lexeme == "char*" || lexeme == "double" || lexeme == "void" || lexeme == "long" || lexeme == "unsigned" || lexeme == "short" || lexeme == "union" || lexeme == "enum" || lexeme == "struct");
    }

    Token getCurrentToken()
    {
        return tokens[currentTokenIndex];
    }
    // go to next token
    void consumeToken()
    {
        currentTokenIndex++;
    }
    void backToken()
    {
        currentTokenIndex--;
    }

    bool parseDeclarationList()
    { // just to loop on our vector and start the algorithm for recursive descent parsing
        while (currentTokenIndex < tokens.size() && currentTokenIndex != tokens.size() - 1)
        {
            // isInSymbolTable(getCurrentToken().lexeme);
            if (!parseDeclaration())
            { // recursive descent technique, a lot of recursion and function calls will be made to check grammar
                // cout << getCurrentToken().lexeme << endl;
                return false; // there is error
            }
            // if (noOfBlocks != noOfCalls)
            // {
            //     cout << "Error in the number of blocks and calls" << endl;
            //     return false;
            // }
            // cout << getCurrentToken().lexeme << endl;
        }
        return true; // no errors
    }
    bool enumflag = false;
    bool parseDeclaration()
    {
        cout << getCurrentToken().lexeme << 34 << endl;
        if (isDataType(getCurrentToken().lexeme))
        {
            if (getCurrentToken().lexeme == "enum")
            {

                return parseEnum();
            }
            temp = getCurrentToken().lexeme;
            // cout << temp << 44 << endl;
            consumeToken();
            if (isInSymbolTable(getCurrentToken().lexeme))
            {
                cout << "Variable already declared" << endl;
                return false;
            }
            if (parseVariableDeclaration())
            {
                // cout << getCurrentToken().lexeme << 45 << endl;
                // consumeToken();
                return true;
            }
            else
            {
                cout << "Declaration is wrong" << endl;
                return false;
            }
        }
        else if (getCurrentToken().type == "Identifier")
        {
            if (!isInSymbolTable(getCurrentToken().lexeme))
            {
                // cout << 1 << endl;
                cout << "Variable  '" << getCurrentToken().lexeme << "'  hasn't been declared" << endl;
                return false;
            }
            else
            {
                return parseVariableDeclaration();
            }
        }
        // else if ()
        // {
        // }
        else if (getCurrentToken().lexeme == "if" || getCurrentToken().lexeme == "while")
        {
            if (parseIfWhileStatements())
            {
                // cout << getCurrentToken().lexeme << 1234532343 << endl;
                consumeToken();
                return true;
            }
            else
            {
                cout << "parseDeclaration is wrong" << endl;
                return false;
            }
        }

        else if (getCurrentToken().lexeme == "for")
        {
            return parseForExpression();
        }
        // else if (parseReturnStatement())
        // {
        //     return true;
        // }
        // else if (parseFunctionDeclaration())
        // {
        //     return true;
        // }
        else
        {
            cout << "parseDeclaration is wrong" << endl;
            return false;
        }
    }
    bool parseForExpression()
    {
        consumeToken();

        if (getCurrentToken().lexeme == "(")
        {
            consumeToken();
            if (parseExpression())
            {
                consumeToken();
                if (parseRelExpression())
                {

                    consumeToken();
                    consumeToken();

                    if (parseExpression())
                    {
                        // consumeToken();
                        if (getCurrentToken().lexeme == ")")
                        {
                            consumeToken();
                            noOfBlocks++;

                            if (parseBlock())
                            {
                                // cout << getCurrentToken().lexeme << 789 << endl;
                                return true;
                            }
                            else
                            {
                                cout << "parseForExpression is wrong" << endl;
                                return false;
                            }
                        }
                        else
                        {
                            cout << "parseForExpression is wrong" << endl;

                            return false;
                        }
                    }
                    else
                    {
                        cout << "parseForExpression is wrong" << endl;

                        return false;
                    }
                }
                else
                {
                    cout << "parseForExpression is wrong" << endl;

                    return false;
                }
            }
            else
            {
                cout << "parseForExpression is wrong" << endl;

                return false;
            }
        }
        else
        {
            cout << "parseForExpression is wrong" << endl;

            return false;
        }
    }
    bool parseFunctionDeclaration()
    {
        bool flag = false;
        if (getCurrentToken().lexeme == ")")
        {
            flag = true;
            if (currentTokenIndex < tokens.size() - 1)
            {
                consumeToken();
            }
            // consumeToken();
        }
        if (getCurrentToken().type == "Identifier")
        {
            consumeToken();
            while (getCurrentToken().type == "Delimiter")
            {
                consumeToken();
                if (getCurrentToken().type == "Keyword")
                {
                    consumeToken();
                    if (getCurrentToken().type == "Keyword")
                    {
                        consumeToken();
                        flag = true;
                    }
                    else
                        flag = false;
                }
                else
                    flag = false;
            }
            if (getCurrentToken().lexeme != ")")
                flag = false;
            else
                consumeToken();
        }
        // cout << "DONE!" << endl;
        if (flag == false)
        {
            // cout << getCurrentToken().lexeme << endl;
            // reportError("Error at function declaration");
            return flag;
        }
        /*if (getCurrentToken().lexeme == "{") {
            flag = parseFnBlock();
        }*/
        return flag;
    }
    bool parseReturn()
    {
        consumeToken();
        if (getCurrentToken().type == "Identifier" || getCurrentToken().type == "Decimal Number" || getCurrentToken().type == "Floating Point Number" || getCurrentToken().type == "Octal Number" || getCurrentToken().type == "Hexadecimal Number" || getCurrentToken().type == "Binary Number")
        {
            consumeToken();
            if (getCurrentToken().lexeme == ";")
            {
                return true;
            }
            else
            {
                cout << "Error in return statement" << endl;
                return false;
            }
        }
        else if (parseExpression())
        {
            return true;
        }
        else
        {
            if (getCurrentToken().lexeme == ";")
            {
                return true;
            }
        }
    }

    bool parseEnum()
    {
        consumeToken();
        if (getCurrentToken().type == "Identifier")
        {
            consumeToken();
            if (getCurrentToken().lexeme == "{")
            {
                consumeToken();
                if (getCurrentToken().type == "Identifier")
                {
                    consumeToken();
                    while (getCurrentToken().lexeme == ",")
                    {
                        consumeToken();
                        if (getCurrentToken().type == "Identifier")
                        {
                            consumeToken();
                        }
                        else
                        {
                            return false;
                        }
                    }

                    if (getCurrentToken().lexeme == "}")
                    {
                        consumeToken();

                        if (getCurrentToken().lexeme == ";")
                        {
                            consumeToken();
                            return true;
                        }
                    }
                }
            }
        }
    }
    bool parseBlock()
    {
        // consumeToken();
        bool isIf = false;
        noOfCalls++;
        if (getCurrentToken().lexeme == "{")
        {

            // noOfBlocks++;
            consumeToken();
            while (getCurrentToken().lexeme != "}" && currentTokenIndex < tokens.size())
            {

                if (!parseExpression() && getCurrentToken().lexeme != "if" && getCurrentToken().lexeme != "while" && getCurrentToken().lexeme != "for")
                {
                    cout << "Error in block" << endl;
                    return false;
                }
                else if (getCurrentToken().lexeme == "if" || getCurrentToken().lexeme == "while")
                {
                    if (getCurrentToken().lexeme == "if")
                    {
                        isIf = true;
                    }
                    return parseIfWhileStatements();
                }
                else if (getCurrentToken().lexeme == "for")
                {

                    return parseForExpression();
                }
                else if (enumflag)
                {
                    return parseEnum();
                }
                else
                {

                    // cout << getCurrentToken().lexeme << 4 << endl;

                    if (getCurrentToken().lexeme == ";" && currentTokenIndex < tokens.size() - 1)
                    {

                        consumeToken();
                        // consumeToken();
                    }
                    else
                    {
                        cout << "Error in block" << endl;
                        return false;
                    }
                }
                if (getCurrentToken().lexeme == "return")
                {
                    return parseReturn();
                }
                if (getCurrentToken().lexeme == "break" || getCurrentToken().lexeme == "continue")
                {
                    consumeToken();
                    if (getCurrentToken().lexeme == ";")
                    {
                        consumeToken();
                    }
                    else
                    {
                        cout << "Error in block" << endl;
                        return false;
                    }
                }
                // if (currentTokenIndex == tokens.size() && getCurrentToken().lexeme != "}")
                // {
                //     return false;
                // }
                // consumeToken();
            }

            if (currentTokenIndex < tokens.size() - 1)
            {
                consumeToken();
            }
            if (getCurrentToken().lexeme == "else")
            {
                consumeToken();
                if (getCurrentToken().lexeme == "{")
                {
                    // consumeToken();
                    return parseBlock();
                }
                else if (getCurrentToken().lexeme == "if")
                {
                    return parseIfWhileStatements();
                }
                else
                {
                    cout << "Error in block" << endl;
                    return false;
                }
            }
            cout << getCurrentToken().lexeme << 12 << endl;

            // cout << getCurrentToken().lexeme << 1 << endl;
            return true;
        }
        else
        {
            cout << "Error in block" << endl;
            return false;
        }
    }

    bool isInSymbolTable(string lexeme1)
    {
        for (int i = 0; i < SymbolTable.size(); i++)
        {
            // cout << SymbolTable[i].first << endl;
            // cout << SymbolTable[i].second << endl;
            if (SymbolTable[i].first == lexeme1)
            {
                return true;
            }
        }
        cout << "Error in symbol table" << endl;
        return false;
    }

    bool parseVariableDeclaration()
    {

        if (getCurrentToken().type == "Identifier")
        {

            if (!isInSymbolTable(getCurrentToken().lexeme))
            {
                SymbolTable.push_back({getCurrentToken().lexeme, temp});
            }

            if (currentTokenIndex != tokens.size() - 1)
            {
                consumeToken();
            }

            if (getCurrentToken().lexeme == ";")
            {
                if (currentTokenIndex == tokens.size() - 1)
                {
                    return true;
                }
                consumeToken();
                return true;
            }
            else if (getCurrentToken().lexeme == "=" || getCurrentToken().lexeme == "+=" || getCurrentToken().lexeme == "-=" || getCurrentToken().lexeme == "*=" || getCurrentToken().lexeme == "/=")
            {
                consumeToken();
                // cout << getCurrentToken().lexeme << 123 << endl;
                if (parseSumExpression())
                {
                    return true;
                }
                // backToken();
                // backToken();
                // if (parseMulExpression())
                // {
                //     return true;
                // }
                cout << "Error in variable declaration" << endl;
                return false;

                // if (getCurrentToken().type == "Decimal Number")
                // {
                //     if (currentTokenIndex != tokens.size() - 1)
                //     {
                //         consumeToken();
                //     }
                //     if (getCurrentToken().lexeme == ";")
                //     {
                //         if (currentTokenIndex < tokens.size())
                //         {
                //             consumeToken();
                //         }
                //         return true;
                //     }
                //     else
                //     {
                //         return false;
                //     }
                // }
                // else if (getCurrentToken().type == "Identifier")
                // {
                //     consumeToken();
                //     if (getCurrentToken().lexeme == ";")
                //     {
                //         consumeToken();
                //         return true;
                //     }
                //     else
                //     {
                //         return false;
                //     }
                // }
                // else
                // {
                //     return false;
                // }
            }
            else if (getCurrentToken().lexeme == "(")
            {

                consumeToken();
                // cout << getCurrentToken().lexeme << 123456 << endl;
                return parseFunctionCallExpression();
            }
            else if (getCurrentToken().lexeme == "[")
            {
                consumeToken();
                if (getCurrentToken().type == "Decimal Number")
                {
                    if (currentTokenIndex < tokens.size() - 1)
                    {
                        consumeToken();
                    }
                    if (getCurrentToken().lexeme == "]")
                    {
                        if (currentTokenIndex < tokens.size() - 1)
                        {
                            consumeToken();
                        }
                        // cout << "Seif" << endl;
                        if (getCurrentToken().lexeme == ";")
                        {
                            if (currentTokenIndex < tokens.size() - 1)
                            {
                                consumeToken();
                            }
                            // consumeToken();
                            return true;
                        }
                        else
                        {
                            cout << "Error in variable declaration" << endl;
                            return false;
                        }
                    }
                }
                else if (getCurrentToken().lexeme == "]")
                {
                    if (currentTokenIndex < tokens.size() - 1)
                    {
                        consumeToken();
                    }
                    if (getCurrentToken().lexeme == ";")
                    {
                        return true;
                    }
                    else
                    {
                        cout << "Error in variable declaration" << endl;

                        return false;
                    }
                }
                else
                {
                    cout << "Error in variable declaration" << endl;

                    return false;
                }
            }
            else if (getCurrentToken().lexeme == "{")
            {
                noOfBlocks++;
                return parseBlock();
            }
            else
            {
                cout << "Error in variable declaration" << endl;

                return false;
            }
        }
        else
        {
            cout << "Error in variable declaration" << endl;

            return false;
        }
    }
    bool parseSumOperation()
    {
        if (getCurrentToken().lexeme == "+" || getCurrentToken().lexeme == "-")
        {
            consumeToken();
            return true;
        }
        else
        {
            cout << "Error in sum operation" << endl;
            return false;
        }
    }
    bool parseMulExpression()
    {

        if (getCurrentToken().type == "Identifier" || getCurrentToken().type == "Decimal Number")
        {
            // cout << getCurrentToken().lexeme << 8 << endl;
            consumeToken();
            if (parseMulOperation())
            {
                cout << getCurrentToken().lexeme << 1 << endl;
                consumeToken();
                if (parseMulExpression())
                {
                    return true;
                }
                else if (parseSumExpression())
                {
                    return true;
                }
                else
                {
                    cout << "Error in mul expression" << endl;
                    return false;
                }
            }
            else if (getCurrentToken().lexeme == ";")
            {
                return true;
            }
            else
            {
                cout << "Error in mul expression" << endl;

                return false;
            }
        }

        if (getCurrentToken().lexeme == ";")
        {
            return true;
        }
    }
    bool parseMuttable()
    {
        if (getCurrentToken().type == "Identifier")
        {
            consumeToken();
            if (getCurrentToken().lexeme == "[")
            {
                consumeToken();
                if (getCurrentToken().type == "Decimal Number")
                {
                    if (getCurrentToken().lexeme == "]")
                    {
                        consumeToken();
                        return true;
                    }
                    else
                    {
                        cout << "Error in muttable" << endl;
                        return false;
                    }
                }
                else
                {
                    cout << "Error in muttable" << endl;

                    return false;
                }
            }
            else
            {
                return true;
            }
        }
        else
        {
            cout << "Error in muttable" << endl;

            return false;
        }
    }
    bool parseImmutable()
    {
        if (getCurrentToken().lexeme == "(")
        {
            consumeToken();
            if (parseExpression())
            {
                if (getCurrentToken().lexeme == ")")
                {
                    consumeToken();
                    return true;
                }
            }
        }
        else if (parseCall())
        {
            consumeToken();
            return true;
        }
        else if (parseConstant())
        {

            consumeToken();
            return true;
        }
        else
        {
            cout << "Error in immutable" << endl;
            return false;
        }
    }
    bool parseCall()
    {
        if (getCurrentToken().type == "Identifier")
        {
            consumeToken();
            if (getCurrentToken().lexeme == "(")
            {
                consumeToken();
                if (parseArguments())
                {
                    consumeToken();
                    if (getCurrentToken().lexeme == ")")
                    {
                        return true;
                    }
                    else
                    {
                        cout << "Error in call" << endl;
                        return false;
                    }
                }
                else
                {
                    cout << "Error in call" << endl;

                    return false;
                }
            }
            else
            {
                cout << "Error in call" << endl;

                return false;
            }
        }
        else
        {
            cout << "Error in call" << endl;

            return false;
        }
    }
    bool parseArguments()
    {
        if (parseArgumentsList())
        {
            return true;
        }
        else
        {
            return true;
        }
    }
    bool parseArgumentsList()
    {
        if (parseExpression())
        {
            consumeToken();
            return true;
        }
        else if (parseArgumentsList())
        {
            consumeToken();
            if (getCurrentToken().lexeme == ",")
            {
                consumeToken();
                if (parseExpression())
                {
                    return true;
                }
                else
                {
                    return false;
                }
            }
            else
            {
                return false;
            }
        }
        else
        {
            return false;
        }
    }
    bool parseIfWhileStatements()
    {
        consumeToken();

        if (getCurrentToken().lexeme == "(")
        {
            consumeToken();
            if (!parseRelExpression())
            {
                return false;
            }
            consumeToken();
            // cout << getCurrentToken().lexeme << endl;
            if (getCurrentToken().lexeme == ")")
            {
                consumeToken();
                noOfBlocks++;
                if (parseBlock())
                {
                    return true;
                }
                else
                {
                    return false;
                }
                // return true;
                // cout << "seif" << 1 << endl;
            }
            else
            {
                return false;
            }
        }
        else
        {
            return false;
        }
    }

    bool parseUnaryExpression()
    {
        if (!parseFactor())
        {
            // //cout << getCurrentToken().lexeme << 1 << endl;
            if (parseUnaryOperation())
            {
                // //cout << getCurrentToken().lexeme << 2 << endl;
                consumeToken();
                if (parseUnaryExpression())
                {
                    return true;
                }
                else
                {
                    return false;
                }
            }
            else if (parseFactor())
            {
                // //cout << getCurrentToken().lexeme << 2 << endl;
                return true;
            }
            else
            {
                // //cout << 1 << endl;
                return false;
            }
        }
        else
        {
            return true;
        }
    }
    bool parseMulOperation()
    {
        if (getCurrentToken().lexeme == "*" || getCurrentToken().lexeme == "/" || getCurrentToken().lexeme == "%")
        {
            consumeToken();
            return true;
        }
        else
        {
            return false;
        }
    }
    bool parseExpression()
    {
        // cout << getCurrentToken().lexeme << 8 << endl;

        if (isDataType(getCurrentToken().lexeme))
        {
            consumeToken();
            if (isInSymbolTable(getCurrentToken().lexeme))
            {
                // cout << getCurrentToken().lexeme << 2345 << endl;
                cout << "Variable " << getCurrentToken().lexeme << " already declared" << endl;
                return false;
            }
            else
            {
                SymbolTable.push_back({getCurrentToken().lexeme, temp});
            }
        }
        if (getCurrentToken().type == "Identifier")
        {

            if (!isInSymbolTable(getCurrentToken().lexeme) && getCurrentToken().lexeme != "printf")
            {
                cout << 2 << endl;
                cout << "Variable " << getCurrentToken().lexeme << "hasn't been declared" << endl;
                return false;
            }

            consumeToken();
            // cout << getCurrentToken().lexeme << 5 << endl;

            if (getCurrentToken().lexeme == "=" || getCurrentToken().lexeme == "+=" || getCurrentToken().lexeme == "-=" || getCurrentToken().lexeme == "*=" || getCurrentToken().lexeme == "/=")
            {
                // if (getCurrentToken().lexeme == "+=" || getCurrentToken().lexeme == "-=" || getCurrentToken().lexeme == "*=" || getCurrentToken().lexeme == "/=")
                // {
                //     return false;
                // }
                consumeToken();
                // cout << getCurrentToken().lexeme << endl;
                if (parseExpression())
                {
                    return true;
                }
                else if (parseConstant())
                {
                    // consumeToken();

                    return true;
                }
                else
                {
                    return false;
                }
            }
            else if (getCurrentToken().lexeme == "++" || getCurrentToken().lexeme == "--")
            {

                consumeToken();
                return true;
            }
            else if (getCurrentToken().lexeme == "+" || getCurrentToken().lexeme == "-" || getCurrentToken().lexeme == "*" || getCurrentToken().lexeme == "/" || getCurrentToken().lexeme == "%")
            {
                consumeToken();
                cout << getCurrentToken().type << 6 << endl;
                if (getCurrentToken().type == "Identifier" || getCurrentToken().type == "Decimal Number" || getCurrentToken().type == "Floating Point Number" || getCurrentToken().type == "Octal Number" || getCurrentToken().type == "Hexadecimal Number" || getCurrentToken().type == "Binary Number")
                {
                    cout << getCurrentToken().lexeme << 6 << endl;
                    consumeToken();
                    return true;
                }
                else
                {
                    return false;
                }
                // return parseExpression();
            }
            else if (parseMulOperation())
            {

                consumeToken();
                return parseExpression();
            }
            else if (getCurrentToken().lexeme == ";")
            {
                // cout << getCurrentToken().lexeme << endl;

                return true;
            }
            else if (getCurrentToken().lexeme == "(")
            {

                return parseFunctionCallExpression();
            }
            else
            {
                // cout << getCurrentToken().lexeme << 4 << endl;
                return false;
            }
        }
        else
        {
            // cout << getCurrentToken().lexeme << 5 << endl;
            return false;
        }
    }
    bool parseConstant()
    {
        if (getCurrentToken().type == "Identifier" || getCurrentToken().type == "Decimal Number" || getCurrentToken().type == "Floating Point Number" || getCurrentToken().type == "Octal Number" || getCurrentToken().type == "Hexadecimal Number" || getCurrentToken().type == "Binary Number")
        {
            consumeToken();
            return true;
        }
        else if (getCurrentToken().lexeme == "true" || getCurrentToken().lexeme == "false")
        {
            consumeToken();
            return true;
        }
        else if (getCurrentToken().type == "String Literal")
        {
            consumeToken();
            return true;
        }
        else
        {
            return false;
        }
    }
    bool parseSumExpression()
    {
        // count++;
        cout << getCurrentToken().lexeme << 1313 << endl;

        // //cout << getCurrentToken().lexeme << endl;
        if (getCurrentToken().lexeme == ";")
        {
            return true;
        }
        else if (getCurrentToken().type == "Identifier" || getCurrentToken().type == "Decimal Number" || getCurrentToken().type == "Floating Point Number" || getCurrentToken().type == "Octal Number" || getCurrentToken().type == "Hexadecimal Number" || getCurrentToken().type == "Binary Number")
        {
            if (!isInSymbolTable(getCurrentToken().lexeme) && getCurrentToken().type == "Identifier")
            {
                cout << 3 << endl;
                cout << "Variable " << getCurrentToken().lexeme << " hasn't been declared" << endl;
                return false;
            }
            consumeToken();

            if (getCurrentToken().lexeme == "+" || getCurrentToken().lexeme == "-")
            {
                // cout << getCurrentToken().lexeme << 1 << endl;
                // cout << getCurrentToken().lexeme << 1 << endl;
                // consumeToken();
                // if (parseMulExpression())
                // {

                //     return true;
                // }
                // else
                consumeToken();
                if (getCurrentToken().type == "Identifier" || getCurrentToken().type == "Decimal Number" || getCurrentToken().type == "Floating Point Number" || getCurrentToken().type == "Octal Number" || getCurrentToken().type == "Hexadecimal Number" || getCurrentToken().type == "Binary Number")
                {
                    return true;
                }
                else
                {
                    return false;
                }
                // if (parseSumExpression())
                // {
                //     return true;
                // }
                // else
                // {
                //     return false;
                // }
            }
            else if (getCurrentToken().lexeme == ";")
            {
                consumeToken();
                return true;
            }
            else if (getCurrentToken().lexeme == "*" || getCurrentToken().lexeme == "/" || getCurrentToken().lexeme == "%")
            {
                // cout << getCurrentToken().lexeme << 432 << endl;
                consumeToken();

                return parseMulExpression();
            }
            else
            {
                return false;
            }
        }
        else if (parseMulExpression())
        {
            return true;
        }
        else
        {
            // cout << getCurrentToken().lexeme << endl;
        }
    }
    bool parseUnaryOperation()
    {
        if (getCurrentToken().lexeme == "++" || getCurrentToken().lexeme == "--" || getCurrentToken().lexeme == "!" || getCurrentToken().lexeme == "~" || getCurrentToken().lexeme == "-")
        {
            consumeToken();
            return true;
        }
        else
        {
            // cout << "seif" << endl;
            return false;
        }
    }
    bool parseFactor()
    {
        if (parseImmutable())
        {
            return true;
        }
        else if (parseMuttable())
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    bool parseRelExpression()
    {
        // //cout << getCurrentToken().lexeme << endl;

        if (getCurrentToken().type == "Identifier")
        {
            if (!isInSymbolTable(getCurrentToken().lexeme))
            {
                // cout << 4 << endl;
                cout << "Variable " << getCurrentToken().lexeme << " hasn't been declared " << endl;
                return false;
            }
            consumeToken();
            if (parseRelOperation())
            {
                // cout << getCurrentToken().lexeme << endl;
                if (getCurrentToken().type == "Identifier" || getCurrentToken().type == "Decimal Number" || getCurrentToken().type == "Floating Point Number" || getCurrentToken().type == "Octal Number" || getCurrentToken().type == "Hexadecimal Number" || getCurrentToken().type == "Binary Number")
                {
                    return true;
                }
                else
                {
                    return false;
                }
            }
        }
        else if (getCurrentToken().type == "Decimal Number" || getCurrentToken().type == "Floating Point Number" || getCurrentToken().type == "Octal Number" || getCurrentToken().type == "Hexadecimal Number" || getCurrentToken().type == "Binary Number")
        {
            if (parseRelOperation())
            {
                if (getCurrentToken().type == "Identifier" || getCurrentToken().type == "Decimal Number" || getCurrentToken().type == "Floating Point Number" || getCurrentToken().type == "Octal Number" || getCurrentToken().type == "Hexadecimal Number" || getCurrentToken().type == "Binary Number")
                {
                    return true;
                }
                else
                {
                    return false;
                }
            }
        }
        else
        {
            return false;
        }
    }
    bool parseRelOperation()
    {

        if (getCurrentToken().lexeme == "<" || getCurrentToken().lexeme == ">" || getCurrentToken().lexeme == "<=" || getCurrentToken().lexeme == ">=" || getCurrentToken().lexeme == "==" || getCurrentToken().lexeme == "!=")
        {

            consumeToken();
            return true;
        }
        else
        {
            return false;
        }
    }

    bool parseFunctionCall()
    {
        if (getCurrentToken().type == "Identifier")
        {
            consumeToken();
            if (getCurrentToken().lexeme == "(")
            {
                consumeToken();
                if (parseArguments())
                {
                    consumeToken();
                    if (getCurrentToken().lexeme == ")")
                    {
                        return true;
                    }
                    else
                    {
                        return false;
                    }
                }
                else
                {
                    return false;
                }
            }
            else
            {
                return false;
            }
        }
    }

    bool parseFunctionCallExpression()
    {
        bool flag = false;
        // cout << getCurrentToken().lexeme << 1 << endl;

        if (getCurrentToken().lexeme == ")")
        {
            flag = true;
            if (currentTokenIndex < tokens.size() - 1)
            {
                consumeToken();
            }

            if (getCurrentToken().lexeme == "{")
            {
                noOfBlocks++;
                return parseBlock();
            }
            else if (getCurrentToken().lexeme == ";")
            {
                return true;
            }
            else
            {
                // if(getCurrentToken().lexeme != ";")
                // {
                flag = false;
                // }
            }
            // consumeToken();
        }
        else
        {
            cout << getCurrentToken().lexeme << "seif" << endl;
            // consumeToken();
            if (getCurrentToken().type == "Identifier")
            {
                cout << getCurrentToken().lexeme << 1 << endl;

                return parseFunctionCall();
            }
            else if (isDataType(getCurrentToken().lexeme))
            {
                consumeToken();
                if (getCurrentToken().type == "Identifier")
                {
                    consumeToken();
                    while (getCurrentToken().lexeme == ",")
                    {
                        consumeToken();
                        if (isDataType(getCurrentToken().lexeme))
                        {
                            consumeToken();
                            if (getCurrentToken().type == "Identifier")
                            {
                                consumeToken();
                                flag = true;
                            }
                        }
                        else if (getCurrentToken().type == "Identifier")
                        {
                            consumeToken();
                            flag = true;
                        }
                        else
                        {
                            flag = false;
                        }
                    }
                    if (getCurrentToken().lexeme == ")")
                    {
                        flag = true;
                        consumeToken();
                        if (getCurrentToken().lexeme == ";")
                        {
                            flag = true;
                        }
                        else
                        {
                            flag = false;
                        }
                    }
                    else
                    {
                        flag = false;
                    }
                    // flag = true;
                }
            }
        }
        cout << getCurrentToken().lexeme << 3 << endl;
        consumeToken();
        return flag;
    }
};
// int main()
// {

// struct Token
// {
//     char lexeme;
//     char type;
// } int main()
// {
//     int jou;
//     int x;
//     int seif = 0;
//     int salah;
//     while (seif < 5)
//     {
//         jou += 20;
//     }

//     if (jou == 5)
//     {
//         for (int parser = 0; parser <= seif; parser++)
//         {
//             int x = 5;
//         }
//     }
// }
// //
// int main()
// {
//     Token token1;
//     Token token2;
//     Token token3;
//     Token token4;
//     Token token5;
//     token1.setToken("int", "keyword");
//     token2.setToken("main", "Identifier");
//     token3.setToken("=", "Assignment Operator");
//     token4.setToken("5", "Decimal Number");
//     token5.setToken(";", "Delimiter");
//     vector<Token> tokens;
//     tokens.push_back(token1);
//     tokens.push_back(token2);
//     tokens.push_back(token3);
//     tokens.push_back(token4);
//     tokens.push_back(token5);
//     Parser2 parser(tokens);

//     if (parser.parseProgram())
//     {
//         cout << "Parsing successful!" << endl;
//     }
//     else
//     {
//         cout << "Parsing failed!" << endl;
//     }
// }

// replace with actual tokens from our scanner, this vector is made to store the tokens
// vector<Token> tokens = {
// {"struct", "TYPE_SPECIFIER"},
// {"Token", "Identifier"},
// {"{", "BLOCK"},
// {"char", "TYPE_SPECIFIER"},
// {"lexeme", "Identifier"},
// {";", "Delimiter"},
// {"char", "TYPE_SPECIFIER"},
// {"type", "Identifier"},
// {";", "Delimiter"},
// {"}", "BLOCK"},
// //-------------------
// {"int", "TYPE_SPECIFIER"},
// {"main", "Identifier"},
// {"(", "BRACKET"},
// {")", "BRACKET"},
// {"{", "BLOCK"},
// {"int", "TYPE_SPECIFIER"},
// {"jou", "Identifier"},
// {";", "Delimiter"},
// {"int", "TYPE_SPECIFIER"},
// {"x", "Identifier"},
// {";", "Delimiter"},
// {"int", "TYPE_SPECIFIER"},
// {"seif", "Identifier"},
// {"=", "ASSIGNMENT"},
// {"0", "Decimal Number"},
// {";", "Delimiter"},
// {"int", "TYPE_SPECIFIER"},
// {"salah", "Identifier"},
// {";", "Delimiter"},
// {"while", "BLOCK"},
// {"(", "BRACKET"},
// {"seif", "Identifier"},
// {"<", "ASSIGNMENT"},
// {"5", "Decimal Number"},
// {")", "BRACKET"},
// {"{", "BLOCK"},
// {"jou", "Identifier"},
// {"+=", "Unary"},
// {"20", "Decimal Number"},
// {";", "Delimiter"},

// {"}", "BLOCK"},
// //-------------------
// {"if", "BLOCK"},
// {"(", "BRACKET"},
// {"jou", "Identifier"},
// {"==", "ASSIGNMENT"},
// {"5", "Decimal Number"},
// {")", "BRACKET"},
// {"{", "BLOCK"},
// {"for", "BLOCK"},
// {"(", "BRACKET"},
// {"int", "TYPE_SPECIFIER"},
// {"parser", "Identifier"},
// {"=", "ASSIGNMENT"},
// {"0", "Decimal Number"},
// {";", "Delimiter"},
// {"parser", "Identifier"},
// {"<=", "ASSIGNMENT"},
// {"seif", "Identifier"},
// {";", "Delimiter"},
// {"parser", "Identifier"},
// {"++", "ASSIGNMENT"},
// {")", "BRACKET"},
// {"{", "BLOCK"},
// // {"int", "TYPE_SPECIFIER"},
// {"x", "Identifier"},
// {"=", "ASSIGNMENT"},
// {"5", "Decimal Number"},
// {";", "Delimiter"},

// {"}", "BLOCK"},
// {"}", "BLOCK"},
// {"}", "BLOCK"},
//-----------------------------------------------------------
// {"int", "TYPE_SPECIFIER"},
//     {"y", "Identifier"},
//     {";", "Delimiter"},
//     {"int", "TYPE_SPECIFIER"},
//     {"z", "Identifier"},
//     {";", "Delimiter"},
//     {"int", "TYPE_SPECIFIER"},
//     {"main", "Identifier"},
//     {"=", "ASSIGNMENT"},
//     {"y", "Identifier"},
//     {"+", "ASSIGNMENT"},
//     {"z", "Identifier"},
//     {";", "Delimiter"},

// {";", "Delimiter"},

// {";", "Delimiter"},
// {"while", "BLOCK"},
// {"(", "BRACKET"},
// {"seif", "Identifier"},
// {"==", "ASSIGNMENT"},
// {"5", "Decimal Number"},
// {")", "BRACKET"},
// {"{", "BLOCK"},
// {"if", "BLOCK"},
// {"(", "BRACKET"},
// {"jou", "Identifier"},
// {"==", "ASSIGNMENT"},
// {"5", "Decimal Number"},
// {")", "BRACKET"},
// {"{", "BLOCK"},
// // {"int", "TYPE_SPECIFIER"},
// {"x", "Identifier"},
// {";", "Delimiter"},

// {"for", "BLOCK"},
// {"(", "BRACKET"},
// {"int", "TYPE_SPECIFIER"},
// {"lexeme", "Identifier"},
// {"=", "ASSIGNMENT"},
// {"0", "Decimal Number"},
// {";", "Delimiter"},
// {"lexeme", "Identifier"},
// {"<=", "ASSIGNMENT"},
// {"b", "Identifier"},
// {";", "Delimiter"},
// {"lexeme", "Identifier"},
// {"++", "ASSIGNMENT"},
// {")", "BRACKET"},
// {"{", "BLOCK"},
// // {"int", "TYPE_SPECIFIER"},
// {"lexeme", "Identifier"},
// {";", "Delimiter"},
// {"int", "TYPE_SPECIFIER"},
// {"type", "Identifier"},
// {";", "Delimiter"},
// {"}", "BLOCK"},
// {"}", "BLOCK"},
// {"}", "BLOCK"},
// {"for", "BLOCK"},
// {"(", "BRACKET"},
// {"int", "TYPE_SPECIFIER"},
// {"lexeme", "Identifier"},
// {"=", "ASSIGNMENT"},
// {"0", "Decimal Number"},
// {";", "Delimiter"},
// {"lexeme", "Identifier"},
// {"<=", "ASSIGNMENT"},
// {"b", "Identifier"},
// {";", "Delimiter"},
// {"lexeme", "Identifier"},
// {"++", "ASSIGNMENT"},
// {")", "BRACKET"},
// {"{", "BLOCK"},
// {"int", "TYPE_SPECIFIER"},
// {"lexeme", "Identifier"},
// {";", "Delimiter"},
// {"int", "TYPE_SPECIFIER"},
// {"type", "Identifier"},
// {";", "Delimiter"},
// {"}", "BLOCK"},
// {"struct", "TYPE_SPECIFIER"},
// {"Token", "Identifier"},
// {"{", "BLOCK"},
// {"int", "TYPE_SPECIFIER"},
// {"lexeme", "Identifier"},
// {";", "Delimiter"},
// {"int", "TYPE_SPECIFIER"},
// {"type", "Identifier"},
// {";", "Delimiter"},
// {"}", "BLOCK"},
// {";", "Delimiter"},
// {"int", "TYPE_SPECIFIER"},
// {"y", "Identifier"},
// {"(", "BRACKET"},
// {")", "BRACKET"},
// {";", "Delimiter"},
// {"int", "TYPE_SPECIFIER"},
// {"x", "Identifier"},
// {";", "Delimiter"},
// {"int", "TYPE_SPECIFIER"},
// {"main", "Identifier"},
// {"(", "BRACKET"},
// {"float", "TYPE_SPECIFIER"},
// {"q", "Identifier"},
// {",", "COMMA"},
// {"int", "TYPE_SPECIFIER"},
// {"z", "Identifier"},
// {",", "COMMA"},
// {"int", "TYPE_SPECIFIER"},
// {"v", "Identifier"},
// {",", "COMMA"},
// {"int", "TYPE_SPECIFIER"},
// {"c", "Identifier"},
// {",", "COMMA"},
// {"int", "TYPE_SPECIFIER"},
// {"b", "Identifier"},
// {",", "COMMA"},
// {"int", "TYPE_SPECIFIER"},
// {"n", "Identifier"},
// {")", "BRACKET"},
// {";", "Delimiter"},
// {"int", "TYPE_SPECIFIER"},
// {"b", "Identifier"},
// {";", "Delimiter"},
// // {"int", "TYPE_SPECIFIER"},
// {"x", "Identifier"},
// {"[", "BRACKET"},
// {"10", "Decimal Number"},
// {"]", "BRACKET"},
// {";", "Delimiter"},
// {"while", "BLOCK"},
// {"(", "BRACKET"},
// {"seif", "Identifier"},
// {"==", "ASSIGNMENT"},
// {"5", "Decimal Number"},
// {")", "BRACKET"},
// {"{", "BLOCK"},
// {"if", "BLOCK"},
// {"(", "BRACKET"},
// {"jou", "Identifier"},
// {"==", "ASSIGNMENT"},
// {"5", "Decimal Number"},
// {")", "BRACKET"},
// {"{", "BLOCK"},
// {"int", "TYPE_SPECIFIER"},
// {"x", "Identifier"},
// {";", "Delimiter"},
// {"}", "BLOCK"},
// {"}", "BLOCK"},
// {";", "Delimiter"},
// {"if", "BLOCK"},
// {"(", "BRACKET"},
// {"jou", "Identifier"},
// {"==", "ASSIGNMENT"},
// {"5", "Decimal Number"},
// {")", "BRACKET"},
// {"{", "BLOCK"},
// {"int", "TYPE_SPECIFIER"},
// {"l", "Identifier"},
// {";", "Delimiter"},
// {"}", "BLOCK"},
// {";", "Delimiter"},
// {"=", "ASSIGNMENT"},
// {"5", "Decimal Number"},
// {";", "Delimiter"},
// {"if", "BLOCK"},
// {"(", "BRACKET"},
// {"y", "Identifier"},
// {"==", "ASSIGNMENT"},
// {"5", "Decimal Number"},
// {")", "BRACKET"},
// {"{", "BLOCK"},
// {"int", "TYPE_SPECIFIER"},
// {"x", "Identifier"},
// {";", "Delimiter"},
// // {"int", "TYPE_SPECIFIER"},
// {"x", "Identifier"},
// {"=", "ASSIGNMENT"},
// {"10", "Decimal Number"},
// {";", "Delimiter"},
// {"seif", "Identifier"},
// {"=", "ASSIGNMENT"},
// {"10", "Decimal Number"},
// {";", "Delimiter"},
// {"seif1", "Identifier"},
// {"=", "ASSIGNMENT"},
// {"10", "Decimal Number"},
// {";", "Delimiter"},
// // {";", "Delimiter"},
// {"}", "BLOCK"},
// // {";", "Delimiter"},
// // Test2// Basic test, assignments (WORKING)
// {"int", "TYPE_SPECIFIER"},
// {"p", "Identifier"},
// {";", "Delimiter"},
// {"float", "TYPE_SPECIFIER"},
// {"m", "Identifier"},
// {"=", "ASSIGNMENT"},
// {"10", "Decimal Number"},
// {";", "Delimiter"},
// //*Test3// function declaration, calls, empty parameters list (WORKING)
// {"int", "TYPE_SPECIFIER"},
// {"o", "Identifier"},
// {"+=", "Unary"},
// {"10", "Decimal Number"},
// {";", "Delimiter"},
// {"int", "TYPE_SPECIFIER"},
// {"v", "Identifier"},
// // {"(", "BRACKET"},
// // {")", "BRACKET"},
// // {"{", "BLOCK"},
// // {"int", "TYPE_SPECIFIER"},
// // {"x", "Identifier"},
// // {"=", "ASSIGNMENT"},
// // {"10", "Decimal Number"},
// {";", "Delimiter"},
// {"while", "BLOCK"},
// {"(", "BRACKET"},
// {"o", "Identifier"},
// {"==", "ASSIGNMENT"},
// {"5", "Decimal Number"},
// {")", "BRACKET"},
// {"{", "BLOCK"},
// {"int", "TYPE_SPECIFIER"},
// {"p", "Identifier"},
// {";", "Delimiter"},
// {"}", "BLOCK"},
// //===========================================================
// //===========================================================
// // {"int", "TYPE_SPECIFIER"},
// // {"x", "Identifier"},
// // {"(", "BRACKET"},
// // {"float", "TYPE_SPECIFIER"},
// // {"y", "Identifier"},
// // {",", "COMMA"},
// // {"int", "TYPE_SPECIFIER"},
// // {"z", "Identifier"},
// // {")", "BRACKET"},
// // {";", "Delimiter"},
// {"int", "TYPE_SPECIFIER"},
// {"q", "Identifier"},
// {";", "Delimiter"},
// // {"(", "BRACKET"},
// // {"float", "TYPE_SPECIFIER"},
// // {"y", "Identifier"},
// // {",", "COMMA"},
// // {"int", "TYPE_SPECIFIER"},
// // {"z", "Identifier"},
// // {")", "BRACKET"},
// // {";", "Delimiter"},
// // {"int", "TYPE_SPECIFIER"},
// {"x", "Identifier"},
// {"(", "BRACKET"},
// {")", "BRACKET"},
// {"{", "BLOCK"},
// {"}", "BLOCK"},
// {"int", "TYPE_SPECIFIER"},
// {"x", "Identifier"},
// {",", "COMMA"},
// {"y", "Identifier"},
// {"(", "BRACKET"},
// {")", "BRACKET"},
// {";", "Delimiter"},
// {"int", "TYPE_SPECIFIER"},
// {"x", "Identifier"},
// {"(", "BRACKET"},
// {"float", "TYPE_SPECIFIER"},
// {"y", "Identifier"},
// {",", "COMMA"},
// {"int", "TYPE_SPECIFIER"},
// {"z", "Identifier"},
// {")", "BRACKET"},
// {";", "Delimiter"},
// {"=", "ASSIGNMENT"},
// {"10", "Decimal Number"},
// {";", "Delimiter"},
// {"int", "TYPE_SPECIFIER"},
// {"x", "Identifier"},
// {"(", "BRACKET"},
// {"float", "TYPE_SPECIFIER"},
// {"y", "Identifier"},
// {",", "COMMA"},
// {"int", "TYPE_SPECIFIER"},
// {"z", "Identifier"},
// {")", "BRACKET"},
// {";", "Delimiter"},
// {"=", "ASSIGNMENT"},
// {"10", "Decimal Number"},
// {";", "Delimiter"},
// {"{", "BLOCK"},
// {"int", "TYPE_SPECIFIER"},
// {"y", "Identifier"},
// {";", "Delimiter"},
// {"}", "BLOCK"},
// {"}", "BLOCK"},
// Test1*// if condition (WORKING!!!!!!!!)
// {"int", "TYPE_SPECIFIER"},
// {"y", "Identifier"},
// // {"=", "ASSIGNMENT"},
// // {"5", "Decimal Number"},
// {";", "Delimiter"},
// // Errorr===================
// {"float", "TYPE_SPECIFIER"},
// {"x", "Identifier"},
// {"=", "ASSIGNMENT"},
// {"5", "Decimal Number"},
// {";", "Delimiter"},
// {"int", "TYPE_SPECIFIER"},
// // {"main", "Identifier"},
// // {";", "Delimiter"},
// {"main", "Identifier"},
// {"(", "BRACKET"},
// {")", "BRACKET"},
// {"{", "BLOCK"},
// {"}", "BLOCK"},

// {";", "Delimiter"},
//=====================================
// {"if", "BLOCK"},
// {"(", "BRACKET"},
// {"y", "Identifier"},
// {"==", "ASSIGNMENT"},
// {"5", "Decimal Number"},
// {")", "BRACKET"},
// {"{", "BLOCK"},
// {"int", "TYPE_SPECIFIER"},
// {"x", "Identifier"},
// {";", "Delimiter"},
// // {"int", "TYPE_SPECIFIER"},
// {"x", "Identifier"},
// {"=", "ASSIGNMENT"},
// {"10", "Decimal Number"},
// {";", "Delimiter"},
// {"seif", "Identifier"},
// {"=", "ASSIGNMENT"},
// {"10", "Decimal Number"},
// {";", "Delimiter"},
// {"seif1", "Identifier"},
// {"=", "ASSIGNMENT"},
// {"10", "Decimal Number"},
// {";", "Delimiter"},
// // {";", "Delimiter"},
// {"}", "BLOCK"},
// // {";", "Delimiter"},
// // Test2// Basic test, assignments (WORKING)
// {"int", "TYPE_SPECIFIER"},
// {"x", "Identifier"},
// {";", "Delimiter"},
// {"float", "TYPE_SPECIFIER"},
// {"y", "Identifier"},
// {"=", "ASSIGNMENT"},
// {"10", "Decimal Number"},
// {";", "Delimiter"},
// //*Test3// function declaration, calls, empty parameters list (WORKING)
// {"int", "TYPE_SPECIFIER"},
// {"x", "Identifier"},
// {"+=", "Unary"},
// {"10", "Decimal Number"},
// {";", "Delimiter"},
// {"int", "TYPE_SPECIFIER"},
// {"main", "Identifier"},
// {"(", "BRACKET"},
// {")", "BRACKET"},
// {";", "Delimiter"},
// // {"{", "BLOCK"},
// // {"int", "TYPE_SPECIFIER"},
// // {"x", "Identifier"},
// // {"=", "ASSIGNMENT"},
// // {"10", "Decimal Number"},
// {";", "Delimiter"},
// {"while", "BLOCK"},
// {"(", "BRACKET"},
// {"o", "Identifier"},
// {"==", "ASSIGNMENT"},
// {"5", "Decimal Number"},
// {")", "BRACKET"},
// {"{", "BLOCK"},
// {"int", "TYPE_SPECIFIER"},
// {"p", "Identifier"},
// {";", "Delimiter"},
// {"}", "BLOCK"},
//===========================================================
//===========================================================

// {"int", "TYPE_SPECIFIER"},
// {"x", "Identifier"},
// {"(", "BRACKET"},
// {"float", "TYPE_SPECIFIER"},
// {"y", "Identifier"},
// {",", "COMMA"},
// {"int", "TYPE_SPECIFIER"},
// {"z", "Identifier"},
// {")", "BRACKET"},
// {";", "Delimiter"},

// {"z", "Identifier"},
// {"=", "ASSIGNMENT"},
// {"5", "Decimal Number"},
// {";", "Delimiter"},
// {"(", "BRACKET"},
// {"float", "TYPE_SPECIFIER"},
// {"y", "Identifier"},
// {",", "COMMA"},
// {"int", "TYPE_SPECIFIER"},
// {"z", "Identifier"},
// {")", "BRACKET"},
// {";", "Delimiter"},
// {"int", "TYPE_SPECIFIER"},
// {"x", "Identifier"},
// {"(", "BRACKET"},
// {")", "BRACKET"},
// {"{", "BLOCK"},
// {"}", "BLOCK"},
// {"int", "TYPE_SPECIFIER"},
// {"x", "Identifier"},
// {",", "COMMA"},
// {"y", "Identifier"},
// {"(", "BRACKET"},
// {")", "BRACKET"},
// {";", "Delimiter"},
// {"int", "TYPE_SPECIFIER"},
// {"x", "Identifier"},
// {"(", "BRACKET"},
// {"float", "TYPE_SPECIFIER"},
// {"y", "Identifier"},
// {",", "COMMA"},
// {"int", "TYPE_SPECIFIER"},
// {"z", "Identifier"},
// {")", "BRACKET"},
// {";", "Delimiter"},
// {"=", "ASSIGNMENT"},
// {"10", "Decimal Number"},
// {";", "Delimiter"},
// {"int", "TYPE_SPECIFIER"},
// {"x", "Identifier"},
// {"(", "BRACKET"},
// {"float", "TYPE_SPECIFIER"},
// {"y", "Identifier"},
// {",", "COMMA"},
// {"int", "TYPE_SPECIFIER"},
// {"z", "Identifier"},
// {")", "BRACKET"},
// {";", "Delimiter"},
// {"=", "ASSIGNMENT"},
// {"10", "Decimal Number"},
// {";", "Delimiter"},
// write a hard test case for the parser

// };

//     Parser2 parser(tokens);

//     if (parser.parseProgram())
//     {
//         cout << "Parsing successful!" << endl;
//     }
//     else
//     {
//         cout << "Parsing failed!" << endl;
//     }
// }