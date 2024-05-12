//============================================================================================
//============================================================================================
//============================================================================================
//============================================================================================
//============================ Last Version 12/5 2:06 AM  ====================================
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

class Parser2
{
public:
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
    bool enumflag = false;

    //--------------------------------------------------------------------------------

    //--------------------------------------------------------------------------------
    // Main Function to parse the code and check the grammar
    //--------------------------------------------------------------------------------
    bool isDataType(string lexeme)
    {
        temp2 = getCurrentToken().lexeme;
        return (lexeme == "float" || lexeme == "int" || lexeme == "char" || lexeme == "char*" || lexeme == "double" || lexeme == "void" || lexeme == "long" || lexeme == "unsigned" || lexeme == "short" || lexeme == "union" || lexeme == "enum" || lexeme == "struct");
    }

    //--------------------------------------------------------------------------------
    // Main Function to parse the code and check the grammar
    //--------------------------------------------------------------------------------
    Token getCurrentToken()
    {
        return tokens[currentTokenIndex];
    }

    //--------------------------------------------------------------------------------
    // Main Function to parse the code and check the grammar
    //--------------------------------------------------------------------------------
    void consumeToken()
    {
        currentTokenIndex++;
    }

    //--------------------------------------------------------------------------------
    // Main Function to parse the code and check the grammar
    //--------------------------------------------------------------------------------
    void backToken()
    {
        currentTokenIndex--;
    }

    //--------------------------------------------------------------------------------
    // Main Function to parse the code and check the grammar
    //--------------------------------------------------------------------------------
    bool isInSymbolTable(string lexeme1)
    {
        for (int i = 0; i < SymbolTable.size(); i++)
        {
            if (SymbolTable[i].first == lexeme1)
            {
                return true;
            }
        }
        return false;
    }

    //--------------------------------------------------------------------------------
    // Main Function to parse the code and check the grammar
    //--------------------------------------------------------------------------------
    bool parseDeclarationList()
    { // just to loop on our vector and start the algorithm for recursive descent parsing
        while (currentTokenIndex < tokens.size() && currentTokenIndex != tokens.size() - 1)
        {
            if (!parseDeclaration())
            {                 // recursive descent technique, a lot of recursion and function calls will be made to check grammar
                return false; // there is error
            }
        }
        return true; // no errors
    }

    //--------------------------------------------------------------------------------
    // Main Function to parse the code and check the grammar
    //--------------------------------------------------------------------------------
    bool parseDeclaration()
    {
        // This is the magical cout any error occurs just see in the terminal which lexeme is followed by 34 and you will solve the error :)
        cout << getCurrentToken().lexeme << 34 << endl;
        if (isDataType(getCurrentToken().lexeme))
        {
            if (getCurrentToken().lexeme == "enum")
            {
                return parseEnum();
            }
            temp = getCurrentToken().lexeme;
            consumeToken();
            if (isInSymbolTable(getCurrentToken().lexeme))
            {
                cout << "Variable '" << getCurrentToken().lexeme << "' already declared" << endl;
                return false;
            }
            if (parseVariableDeclaration())
            {
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
                cout << "Variable  '" << getCurrentToken().lexeme << "'  hasn't been declared" << endl;
                return false;
            }
            else
            {
                return parseVariableDeclaration();
            }
        }

        else if (getCurrentToken().lexeme == "if" || getCurrentToken().lexeme == "while")
        {
            if (parseIfWhileStatements())
            {
                consumeToken();
                return true;
            }
            else
            {
                return false;
            }
        }

        else if (getCurrentToken().lexeme == "for")
        {
            return parseForExpression();
        }
        else
        {
            return false;
        }
    }

    //--------------------------------------------------------------------------------
    // Main Function to parse the code and check the grammar
    //--------------------------------------------------------------------------------
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

    //--------------------------------------------------------------------------------
    // Main Function to parse the code and check the grammar
    //--------------------------------------------------------------------------------
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
        if (flag == false)
        {
            // reportError("Error at function declaration");
            return flag;
        }
        return flag;
    }

    //--------------------------------------------------------------------------------
    // Main Function to parse the code and check the grammar
    //--------------------------------------------------------------------------------
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

    //--------------------------------------------------------------------------------
    // Main Function to parse the code and check the grammar
    //--------------------------------------------------------------------------------
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

    //--------------------------------------------------------------------------------
    // Main Function to parse the code and check the grammar
    //--------------------------------------------------------------------------------
    bool parseBlock()
    {
        bool isIf = false;
        noOfCalls++;
        if (getCurrentToken().lexeme == "{")
        {

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
                    if (getCurrentToken().lexeme == ";" && currentTokenIndex < tokens.size() - 1)
                    {
                        consumeToken();
                    }
                    else
                    {
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
                    return parseBlock();
                }
                else if (getCurrentToken().lexeme == "if")
                {
                    return parseIfWhileStatements();
                }
                else
                {
                    return false;
                }
            }
            return true;
        }
        else
        {
            return false;
        }
    }

    //--------------------------------------------------------------------------------
    // Main Function to parse the code and check the grammar
    //--------------------------------------------------------------------------------
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
                if (parseSumExpression())
                {
                    return true;
                }
                return false;
            }
            else if (getCurrentToken().lexeme == "(")
            {
                consumeToken();
                return parseFunctionCallExpression();
            }
            else if (getCurrentToken().lexeme == "[")
            {
                return parseMuttable();
            }
            else if (getCurrentToken().lexeme == "{")
            {
                noOfBlocks++;
                return parseBlock();
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

    //--------------------------------------------------------------------------------
    // Main Function to parse the code and check the grammar
    //--------------------------------------------------------------------------------
    bool parseSumOperation()
    {
        if (getCurrentToken().lexeme == "+" || getCurrentToken().lexeme == "-")
        {
            // consumeToken();
            return true;
        }
        else
        {
            return false;
        }
    }

    //--------------------------------------------------------------------------------
    // Main Function to parse the code and check the grammar
    //--------------------------------------------------------------------------------
    bool parseMulExpression()
    {

        if (getCurrentToken().type == "Identifier" || getCurrentToken().type == "Decimal Number")
        {
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
                    return false;
                }
            }
            else if (getCurrentToken().lexeme == ";")
            {
                return true;
            }
            else
            {
                return false;
            }
        }

        if (getCurrentToken().lexeme == ";")
        {
            return true;
        }
    }

    //--------------------------------------------------------------------------------
    // Main Function to parse the code and check the grammar
    //--------------------------------------------------------------------------------

    bool parseMuttable()
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
                if (getCurrentToken().lexeme == ";")
                {
                    if (currentTokenIndex < tokens.size() - 1)
                    {
                        consumeToken();
                    }
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
                return false;
            }
        }
        else
        {
            return false;
        }
    }

    //--------------------------------------------------------------------------------
    // Main Function to parse the code and check the grammar
    //--------------------------------------------------------------------------------
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
        else if (parseFunctionCall())
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
            return false;
        }
    }

    //--------------------------------------------------------------------------------
    // Main Function to parse the code and check the grammar
    //--------------------------------------------------------------------------------
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

    //--------------------------------------------------------------------------------
    // Main Function to parse the code and check the grammar
    //--------------------------------------------------------------------------------
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

    //--------------------------------------------------------------------------------
    // Main Function to parse the code and check the grammar
    //--------------------------------------------------------------------------------
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

    //--------------------------------------------------------------------------------
    // Main Function to parse the code and check the grammar
    //--------------------------------------------------------------------------------
    bool parseUnaryExpression()
    {
        if (!parseFactor())
        {
            if (parseUnaryOperation())
            {
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
                return true;
            }
            else
            {
                return false;
            }
        }
        else
        {
            return true;
        }
    }

    //--------------------------------------------------------------------------------
    // Main Function to parse the code and check the grammar
    //--------------------------------------------------------------------------------
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

    //--------------------------------------------------------------------------------
    // Main Function to parse the code and check the grammar
    //--------------------------------------------------------------------------------
    bool parseExpression()
    {
        if (isDataType(getCurrentToken().lexeme))
        {
            temp = getCurrentToken().lexeme;
            consumeToken();
            if (isInSymbolTable(getCurrentToken().lexeme))
            {
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

            if (!isInSymbolTable(getCurrentToken().lexeme))
            {
                // cout << 2 << endl;
                cout << "Variable " << getCurrentToken().lexeme << " hasn't been declared" << endl;
                return false;
            }

            consumeToken();
            // cout << getCurrentToken().lexeme << 5 << endl;

            if (getCurrentToken().lexeme == "=" || getCurrentToken().lexeme == "+=" || getCurrentToken().lexeme == "-=" || getCurrentToken().lexeme == "*=" || getCurrentToken().lexeme == "/=")
            {
                consumeToken();
                if (parseExpression())
                {
                    return true;
                }
                else if (parseConstant())
                {
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
            else if (getCurrentToken().lexeme == "+" || getCurrentToken().lexeme == "-" || parseMulOperation())
            {
                consumeToken();
                // cout << getCurrentToken().type << 6 << endl;
                if (getCurrentToken().type == "Identifier" || getCurrentToken().type == "Decimal Number" || getCurrentToken().type == "Floating Point Number" || getCurrentToken().type == "Octal Number" || getCurrentToken().type == "Hexadecimal Number" || getCurrentToken().type == "Binary Number")
                {
                    // cout << getCurrentToken().lexeme << 6 << endl;
                    consumeToken();
                    return true;
                }
                else
                {
                    return false;
                }
            }
            else if (parseMulOperation())
            {

                consumeToken();
                return parseExpression();
            }
            else if (getCurrentToken().lexeme == ";")
            {
                return true;
            }
            else if (getCurrentToken().lexeme == "(")
            {
                consumeToken();
                return parseFunctionCallExpression();
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

    //--------------------------------------------------------------------------------
    // Main Function to parse the code and check the grammar
    //--------------------------------------------------------------------------------
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

    //--------------------------------------------------------------------------------
    // Main Function to parse the code and check the grammar
    //--------------------------------------------------------------------------------
    bool parseSumExpression()
    {
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

            if (parseSumOperation())
            {
                consumeToken();
                if (getCurrentToken().type == "Identifier" || getCurrentToken().type == "Decimal Number" || getCurrentToken().type == "Floating Point Number" || getCurrentToken().type == "Octal Number" || getCurrentToken().type == "Hexadecimal Number" || getCurrentToken().type == "Binary Number")
                {
                    return true;
                }
                else
                {
                    return false;
                }
            }
            else if (getCurrentToken().lexeme == ";")
            {
                consumeToken();
                return true;
            }
            else if (parseMulOperation())
            {
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

    //--------------------------------------------------------------------------------
    // Main Function to parse the code and check the grammar
    //--------------------------------------------------------------------------------
    bool parseUnaryOperation()
    {
        if (getCurrentToken().lexeme == "++" || getCurrentToken().lexeme == "--" || getCurrentToken().lexeme == "!" || getCurrentToken().lexeme == "~" || getCurrentToken().lexeme == "-")
        {
            consumeToken();
            return true;
        }
        else
        {
            return false;
        }
    }

    //--------------------------------------------------------------------------------
    // Main Function to parse the code and check the grammar
    //--------------------------------------------------------------------------------
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

    //--------------------------------------------------------------------------------
    // Main Function to parse the code and check the grammar
    //--------------------------------------------------------------------------------
    bool parseRelExpression()
    {

        if (getCurrentToken().type == "Identifier")
        {
            if (!isInSymbolTable(getCurrentToken().lexeme))
            {
                cout << "Variable " << getCurrentToken().lexeme << " hasn't been declared " << endl;
                return false;
            }
            consumeToken();
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

    //--------------------------------------------------------------------------------
    // Main Function to parse the code and check the grammar
    //--------------------------------------------------------------------------------
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

    //--------------------------------------------------------------------------------
    // Main Function to parse the code and check the grammar
    //--------------------------------------------------------------------------------
    bool parseFunctionCall()
    {
        if (getCurrentToken().type == "Identifier")
        {

            // cout << getCurrentToken().lexeme << 1 << endl;
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
            if (getCurrentToken().lexeme == ")")
            {
                consumeToken();
                if (getCurrentToken().lexeme == ";")
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
    }

    //--------------------------------------------------------------------------------
    // Main Function to parse the code and check the grammar
    //--------------------------------------------------------------------------------
    bool parseFunctionCallExpression()
    {
        bool flag = false;
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
                flag = false;
            }
        }
        else
        {
            // cout << getCurrentToken().lexeme << "seif" << endl;
            if (getCurrentToken().type == "Identifier")
            {
                // cout << getCurrentToken().lexeme << 1 << endl;

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
                }
            }
        }
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