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

using namespace std;
struct Token
{
    string lexeme; // the string
    string type;
    int num;
};

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
    //--------------------------------------------------------------------------------

    bool isDataType(string lexeme)
    {
        // cout << lexeme << 11111111 << endl;
        temp2 = getCurrentToken().lexeme;
        // if()

        return (lexeme == "float" || lexeme == "int" || lexeme == "char" || lexeme == "double" || lexeme == "void" || lexeme == "long" || lexeme == "unsigned" || lexeme == "short" || lexeme == "union" || lexeme == "enum" || lexeme == "struct");
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
            // cout << getCurrentToken().lexeme << endl;
        }
        return true; // no errors
    }
    string temp;
    string temp2;
    bool parseDeclaration()
    {
        cout << getCurrentToken().lexeme << 34 << endl;
        if (isDataType(getCurrentToken().lexeme))
        {
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

                // cout << getCurrentToken().lexeme << 222222 << endl;
                return true;
            }
            else
            {
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
        // else if ()
        // {
        // }
        else if (getCurrentToken().lexeme == "if" || getCurrentToken().lexeme == "while")
        {
            if (parseIfWhileStatements())
            {
                cout << getCurrentToken().lexeme << 1234532343 << endl;
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
                            if (parseBlock())
                            {
                                cout << getCurrentToken().lexeme << 789 << endl;
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
            while (getCurrentToken().type == "COMMA")
            {
                consumeToken();
                if (getCurrentToken().type == "TYPE_SPECIFIER")
                {
                    consumeToken();
                    if (getCurrentToken().type == "Identifier")
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
            cout << getCurrentToken().lexeme << endl;
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
        if (getCurrentToken().type == "CONSTANT")
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
    bool parseBlock()
    {
        // consumeToken();
        if (getCurrentToken().lexeme == "{")
        {

            consumeToken();
            while (getCurrentToken().lexeme != "}" && currentTokenIndex < tokens.size())
            {
                if (getCurrentToken().lexeme == "return")
                {
                    return parseReturn();
                }

                if (!parseExpression() && getCurrentToken().lexeme != "if" && getCurrentToken().lexeme != "while" && getCurrentToken().lexeme != "for")
                {
                    return false;
                }
                else if (getCurrentToken().lexeme == "if" || getCurrentToken().lexeme == "while")
                {

                    return parseIfWhileStatements();
                }
                else if (getCurrentToken().lexeme == "for")
                {

                    return parseForExpression();
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

                // if (currentTokenIndex == tokens.size() && getCurrentToken().lexeme != "}")
                // {
                //     return false;
                // }
            }
            if (currentTokenIndex < tokens.size() - 1)
            {
                consumeToken();
            }
            // cout << getCurrentToken().lexeme << 1 << endl;
            return true;
        }
        else
        {
            return false;
        }
    }

    bool isInSymbolTable(string lexeme1)
    {
        for (int i = 0; i < SymbolTable.size(); i++)
        {
            cout << SymbolTable[i].first << endl;
            cout << SymbolTable[i].second << endl;
            if (SymbolTable[i].first == lexeme1)
            {
                return true;
            }
        }
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
                if (getCurrentToken().type == "CONSTANT")
                {
                    if (currentTokenIndex != tokens.size() - 1)
                    {
                        consumeToken();
                    }
                    if (getCurrentToken().lexeme == ";")
                    {
                        if (currentTokenIndex < tokens.size())
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
                else if (getCurrentToken().type == "Identifier")
                {
                    consumeToken();
                    if (getCurrentToken().lexeme == ";")
                    {
                        consumeToken();
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
            else if (getCurrentToken().lexeme == "(")
            {
                consumeToken();
                return parseFunctionCallExpression();
            }
            else if (getCurrentToken().lexeme == "[")
            {
                consumeToken();
                if (getCurrentToken().type == "CONSTANT")
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
                        return false;
                    }
                }
                else
                {
                    return false;
                }
            }
            else if (getCurrentToken().lexeme == "{")
            {
                consumeToken();
                while (getCurrentToken().lexeme != "}" && currentTokenIndex < tokens.size())
                {
                    if (!parseExpression())
                    {
                        // cout << getCurrentToken().lexeme << 1 << endl;
                        return false;
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
                }

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
        else
        {
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
            return false;
        }
    }
    bool parseMulExpression()
    {
        if (parseUnaryExpression())
        {
            if (parseMulExpression())
            {
                consumeToken();
                if (parseMulOperation())
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
            }
        }
        else
        {
            return false;
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
                if (getCurrentToken().type == "CONSTANT")
                {
                    if (getCurrentToken().lexeme == "]")
                    {
                        consumeToken();
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
                return true;
            }
        }
        else
        {
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
            return true;
        }
        else
        {
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
            cout << getCurrentToken().lexeme << endl;
            if (getCurrentToken().lexeme == ")")
            {
                consumeToken();
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

        if (isDataType(getCurrentToken().lexeme))
        {
            cout << getCurrentToken().lexeme << 9 << endl;
            consumeToken();
            if (isInSymbolTable(getCurrentToken().lexeme))
            {
                cout << getCurrentToken().lexeme << 2345 << endl;
                cout << "Variable already declared" << endl;
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
                cout << "Variable hasn't been declared" << endl;
                return false;
            }
            consumeToken();

            if (getCurrentToken().lexeme == "=" || getCurrentToken().lexeme == "+=" || getCurrentToken().lexeme == "-=" || getCurrentToken().lexeme == "*=" || getCurrentToken().lexeme == "/=")
            {
                if (getCurrentToken().lexeme == "+=" || getCurrentToken().lexeme == "-=" || getCurrentToken().lexeme == "*=" || getCurrentToken().lexeme == "/=")
                {
                    return false;
                }
                consumeToken();
                // cout << getCurrentToken().lexeme << endl;
                if (parseExpression())
                {
                    return true;
                }
                else if (parseConstant())
                {
                    // consumeToken();
                    // if (getCurrentToken().lexeme == ";")
                    // {
                    // cout << getCurrentToken().lexeme << 2 << endl;
                    return true;
                    // }
                    // else
                    // {
                    //     return false;
                    // }
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
            else if (getCurrentToken().lexeme == ";")
            {
                // cout << getCurrentToken().lexeme << endl;
                return true;
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
        if (getCurrentToken().type == "CONSTANT")
        {
            consumeToken();
            return true;
        }
        else if (getCurrentToken().lexeme == "true" || getCurrentToken().lexeme == "false")
        {
            consumeToken();
            return true;
        }
        else if (getCurrentToken().type == "STRING_LITERAL")
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
        // //cout << getCurrentToken().lexeme << endl;
        if (parseMulExpression())
        {
            return true;
        }
        else
        {
            // cout << getCurrentToken().lexeme << endl;
            if (getCurrentToken().type == "Identifier")
            {
                consumeToken();
                // cout << getCurrentToken().lexeme << "after id y" << endl;

                if (parseSumOperation())
                {
                    consumeToken();
                    if (parseMulExpression())
                    {
                        return true;
                    }
                    else
                    {
                        return false;
                    }
                }
            }
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
                cout << "Variable hasn't been declared " << endl;
                return false;
            }
            consumeToken();
            if (parseRelOperation())
            {
                // cout << getCurrentToken().lexeme << endl;
                if (getCurrentToken().type == "Identifier" || getCurrentToken().type == "CONSTANT")
                {
                    return true;
                }
                else
                {
                    return false;
                }
            }
        }
        else if (getCurrentToken().type == "CONSTANT")
        {
            if (parseRelOperation())
            {
                if (getCurrentToken().type == "Identifier" || getCurrentToken().type == "CONSTANT")
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

    bool parseFunctionCallExpression()
    {
        bool flag = false;
        cout << getCurrentToken().lexeme << 1 << endl;

        if (getCurrentToken().lexeme == ")")
        {
            flag = true;
            if (currentTokenIndex < tokens.size() - 1)
            {
                consumeToken();
            }
            if (getCurrentToken().lexeme != ";")
            {
                flag = false;
            }
            // consumeToken();
        }
        else
        {

            consumeToken();
            if (getCurrentToken().type == "Identifier")
            {
                consumeToken();
                while (getCurrentToken().type == "COMMA")
                {
                    consumeToken();
                    if ((isDataType(getCurrentToken().lexeme)))
                    {
                        consumeToken();
                        if (getCurrentToken().type == "Identifier")
                        {
                            consumeToken();
                            flag = true;
                        }
                    }
                }
                // cout << getCurrentToken().lexeme << 1 << endl;
                if (getCurrentToken().lexeme != ")")
                {
                    flag = false;
                }
                else
                {
                    if (currentTokenIndex < tokens.size() - 1)
                    {
                        // return true;
                        consumeToken();
                        if (getCurrentToken().lexeme != ";")
                        {
                            flag = false;
                        }
                    }
                    else
                    {
                        if (getCurrentToken().lexeme != ";")
                        {
                            flag = false;
                        }
                    }
                }
            }
        }
        if (flag == false)
        {
            // reportError("Error at function call");
        }
        consumeToken();
        return flag;
    }
};
int main()
{
    // replace with actual tokens from our scanner, this vector is made to store the tokens
    vector<Token> tokens = {
        {"int", "TYPE_SPECIFIER"},
        {"seif", "Identifier"},
        {";", "SEMI"},
        // {"int", "TYPE_SPECIFIER"},
        // {"jou", "Identifier"},
        // {";", "SEMI"},
        // {"int", "TYPE_SPECIFIER"},
        // {"x", "Identifier"},
        // {";", "SEMI"},
        // {"while", "BLOCK"},
        // {"(", "BRACKET"},
        // {"seif", "Identifier"},
        // {"==", "ASSIGNMENT"},
        // {"5", "CONSTANT"},
        // {")", "BRACKET"},
        // {"{", "BLOCK"},
        // {"if", "BLOCK"},
        // {"(", "BRACKET"},
        // {"jou", "Identifier"},
        // {"==", "ASSIGNMENT"},
        // {"5", "CONSTANT"},
        // {")", "BRACKET"},
        // {"{", "BLOCK"},
        // // {"int", "TYPE_SPECIFIER"},
        // {"x", "Identifier"},
        // {";", "SEMI"},

        // {"for", "BLOCK"},
        // {"(", "BRACKET"},
        // {"int", "TYPE_SPECIFIER"},
        // {"lexeme", "Identifier"},
        // {"=", "ASSIGNMENT"},
        // {"0", "CONSTANT"},
        // {";", "SEMI"},
        // {"lexeme", "Identifier"},
        // {"<=", "ASSIGNMENT"},
        // {"b", "Identifier"},
        // {";", "SEMI"},
        // {"lexeme", "Identifier"},
        // {"++", "ASSIGNMENT"},
        // {")", "BRACKET"},
        // {"{", "BLOCK"},
        // // {"int", "TYPE_SPECIFIER"},
        // {"lexeme", "Identifier"},
        // {";", "SEMI"},
        // {"int", "TYPE_SPECIFIER"},
        // {"type", "Identifier"},
        // {";", "SEMI"},
        // {"}", "BLOCK"},
        // {"}", "BLOCK"},
        // {"}", "BLOCK"},
        // {"for", "BLOCK"},
        // {"(", "BRACKET"},
        // {"int", "TYPE_SPECIFIER"},
        // {"lexeme", "Identifier"},
        // {"=", "ASSIGNMENT"},
        // {"0", "CONSTANT"},
        // {";", "SEMI"},
        // {"lexeme", "Identifier"},
        // {"<=", "ASSIGNMENT"},
        // {"b", "Identifier"},
        // {";", "SEMI"},
        // {"lexeme", "Identifier"},
        // {"++", "ASSIGNMENT"},
        // {")", "BRACKET"},
        // {"{", "BLOCK"},
        // {"int", "TYPE_SPECIFIER"},
        // {"lexeme", "Identifier"},
        // {";", "SEMI"},
        // {"int", "TYPE_SPECIFIER"},
        // {"type", "Identifier"},
        // {";", "SEMI"},
        // {"}", "BLOCK"},
        // {"struct", "TYPE_SPECIFIER"},
        // {"Token", "Identifier"},
        // {"{", "BLOCK"},
        // {"int", "TYPE_SPECIFIER"},
        // {"lexeme", "Identifier"},
        // {";", "SEMI"},
        // {"int", "TYPE_SPECIFIER"},
        // {"type", "Identifier"},
        // {";", "SEMI"},
        // {"}", "BLOCK"},
        // {";", "SEMI"},
        // {"int", "TYPE_SPECIFIER"},
        // {"y", "Identifier"},
        // {"(", "BRACKET"},
        // {")", "BRACKET"},
        // {";", "SEMI"},
        // {"int", "TYPE_SPECIFIER"},
        // {"x", "Identifier"},
        // {";", "SEMI"},
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
        // {";", "SEMI"},
        // {"int", "TYPE_SPECIFIER"},
        // {"b", "Identifier"},
        // {";", "SEMI"},
        // // {"int", "TYPE_SPECIFIER"},
        // {"x", "Identifier"},
        // {"[", "BRACKET"},
        // {"10", "CONSTANT"},
        // {"]", "BRACKET"},
        // {";", "SEMI"},
        // {"while", "BLOCK"},
        // {"(", "BRACKET"},
        // {"seif", "Identifier"},
        // {"==", "ASSIGNMENT"},
        // {"5", "CONSTANT"},
        // {")", "BRACKET"},
        // {"{", "BLOCK"},
        // {"if", "BLOCK"},
        // {"(", "BRACKET"},
        // {"jou", "Identifier"},
        // {"==", "ASSIGNMENT"},
        // {"5", "CONSTANT"},
        // {")", "BRACKET"},
        // {"{", "BLOCK"},
        // {"int", "TYPE_SPECIFIER"},
        // {"x", "Identifier"},
        // {";", "SEMI"},
        // {"}", "BLOCK"},
        // {"}", "BLOCK"},
        // {";", "SEMI"},
        // {"if", "BLOCK"},
        // {"(", "BRACKET"},
        // {"jou", "Identifier"},
        // {"==", "ASSIGNMENT"},
        // {"5", "CONSTANT"},
        // {")", "BRACKET"},
        // {"{", "BLOCK"},
        // {"int", "TYPE_SPECIFIER"},
        // {"l", "Identifier"},
        // {";", "SEMI"},
        // {"}", "BLOCK"},
        // {";", "SEMI"},
        // {"=", "ASSIGNMENT"},
        // {"5", "CONSTANT"},
        // {";", "SEMI"},
        // {"if", "BLOCK"},
        // {"(", "BRACKET"},
        // {"y", "Identifier"},
        // {"==", "ASSIGNMENT"},
        // {"5", "CONSTANT"},
        // {")", "BRACKET"},
        // {"{", "BLOCK"},
        // {"int", "TYPE_SPECIFIER"},
        // {"x", "Identifier"},
        // {";", "SEMI"},
        // // {"int", "TYPE_SPECIFIER"},
        // {"x", "Identifier"},
        // {"=", "ASSIGNMENT"},
        // {"10", "CONSTANT"},
        // {";", "SEMI"},
        // {"seif", "Identifier"},
        // {"=", "ASSIGNMENT"},
        // {"10", "CONSTANT"},
        // {";", "SEMI"},
        // {"seif1", "Identifier"},
        // {"=", "ASSIGNMENT"},
        // {"10", "CONSTANT"},
        // {";", "SEMI"},
        // // {";", "SEMI"},
        // {"}", "BLOCK"},
        // // {";", "SEMI"},
        // // Test2// Basic test, assignments (WORKING)
        // {"int", "TYPE_SPECIFIER"},
        // {"p", "Identifier"},
        // {";", "SEMI"},
        // {"float", "TYPE_SPECIFIER"},
        // {"m", "Identifier"},
        // {"=", "ASSIGNMENT"},
        // {"10", "CONSTANT"},
        // {";", "SEMI"},
        // //*Test3// function declaration, calls, empty parameters list (WORKING)
        // {"int", "TYPE_SPECIFIER"},
        // {"o", "Identifier"},
        // {"+=", "Unary"},
        // {"10", "CONSTANT"},
        // {";", "SEMI"},
        // {"int", "TYPE_SPECIFIER"},
        // {"v", "Identifier"},
        // // {"(", "BRACKET"},
        // // {")", "BRACKET"},
        // // {"{", "BLOCK"},
        // // {"int", "TYPE_SPECIFIER"},
        // // {"x", "Identifier"},
        // // {"=", "ASSIGNMENT"},
        // // {"10", "CONSTANT"},
        // {";", "SEMI"},
        // {"while", "BLOCK"},
        // {"(", "BRACKET"},
        // {"o", "Identifier"},
        // {"==", "ASSIGNMENT"},
        // {"5", "CONSTANT"},
        // {")", "BRACKET"},
        // {"{", "BLOCK"},
        // {"int", "TYPE_SPECIFIER"},
        // {"p", "Identifier"},
        // {";", "SEMI"},
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
        // // {";", "SEMI"},
        // {"int", "TYPE_SPECIFIER"},
        // {"q", "Identifier"},
        // {";", "SEMI"},
        // // {"(", "BRACKET"},
        // // {"float", "TYPE_SPECIFIER"},
        // // {"y", "Identifier"},
        // // {",", "COMMA"},
        // // {"int", "TYPE_SPECIFIER"},
        // // {"z", "Identifier"},
        // // {")", "BRACKET"},
        // // {";", "SEMI"},
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
        // {";", "SEMI"},
        // {"int", "TYPE_SPECIFIER"},
        // {"x", "Identifier"},
        // {"(", "BRACKET"},
        // {"float", "TYPE_SPECIFIER"},
        // {"y", "Identifier"},
        // {",", "COMMA"},
        // {"int", "TYPE_SPECIFIER"},
        // {"z", "Identifier"},
        // {")", "BRACKET"},
        // {";", "SEMI"},
        // {"=", "ASSIGNMENT"},
        // {"10", "CONSTANT"},
        // {";", "SEMI"},
        // {"int", "TYPE_SPECIFIER"},
        // {"x", "ID"},
        // {"(", "BRACKET"},
        // {"float", "TYPE_SPECIFIER"},
        // {"y", "ID"},
        // {",", "COMMA"},
        // {"int", "TYPE_SPECIFIER"},
        // {"z", "ID"},
        // {")", "BRACKET"},
        // {";", "SEMI"},
        // {"=", "ASSIGNMENT"},
        // {"10", "CONSTANT"},
        // {";", "SEMI"},
        // {"{", "BLOCK"},
        // {"int", "TYPE_SPECIFIER"},
        // {"y", "Identifier"},
        // {";", "SEMI"},
        // {"}", "BLOCK"},
        // {"}", "BLOCK"},
        // Test1*// if condition (WORKING!!!!!!!!)
        // {"int", "TYPE_SPECIFIER"},
        // {"y", "Identifier"},
        // // {"=", "ASSIGNMENT"},
        // // {"5", "CONSTANT"},
        // {";", "SEMI"},
        // // Errorr===================
        // {"float", "TYPE_SPECIFIER"},
        // {"x", "Identifier"},
        // {"=", "ASSIGNMENT"},
        // {"5", "CONSTANT"},
        // {";", "SEMI"},
        // {"int", "TYPE_SPECIFIER"},
        // // {"main", "Identifier"},
        // // {";", "SEMI"},
        // {"main", "Identifier"},
        // {"(", "BRACKET"},
        // {")", "BRACKET"},
        // {"{", "BLOCK"},
        // {"}", "BLOCK"},

        // {";", "SEMI"},
        //=====================================
        // {"if", "BLOCK"},
        // {"(", "BRACKET"},
        // {"y", "Identifier"},
        // {"==", "ASSIGNMENT"},
        // {"5", "CONSTANT"},
        // {")", "BRACKET"},
        // {"{", "BLOCK"},
        // {"int", "TYPE_SPECIFIER"},
        // {"x", "Identifier"},
        // {";", "SEMI"},
        // // {"int", "TYPE_SPECIFIER"},
        // {"x", "Identifier"},
        // {"=", "ASSIGNMENT"},
        // {"10", "CONSTANT"},
        // {";", "SEMI"},
        // {"seif", "Identifier"},
        // {"=", "ASSIGNMENT"},
        // {"10", "CONSTANT"},
        // {";", "SEMI"},
        // {"seif1", "Identifier"},
        // {"=", "ASSIGNMENT"},
        // {"10", "CONSTANT"},
        // {";", "SEMI"},
        // // {";", "SEMI"},
        // {"}", "BLOCK"},
        // // {";", "SEMI"},
        // // Test2// Basic test, assignments (WORKING)
        // {"int", "TYPE_SPECIFIER"},
        // {"x", "Identifier"},
        // {";", "SEMI"},
        // {"float", "TYPE_SPECIFIER"},
        // {"y", "Identifier"},
        // {"=", "ASSIGNMENT"},
        // {"10", "CONSTANT"},
        // {";", "SEMI"},
        // //*Test3// function declaration, calls, empty parameters list (WORKING)
        // {"int", "TYPE_SPECIFIER"},
        // {"x", "Identifier"},
        // {"+=", "Unary"},
        // {"10", "CONSTANT"},
        // {";", "SEMI"},
        // {"int", "TYPE_SPECIFIER"},
        // {"main", "Identifier"},
        // {"(", "BRACKET"},
        // {")", "BRACKET"},
        // {";", "SEMI"},
        // // {"{", "BLOCK"},
        // // {"int", "TYPE_SPECIFIER"},
        // // {"x", "Identifier"},
        // // {"=", "ASSIGNMENT"},
        // // {"10", "CONSTANT"},
        // {";", "SEMI"},
        // {"while", "BLOCK"},
        // {"(", "BRACKET"},
        // {"o", "Identifier"},
        // {"==", "ASSIGNMENT"},
        // {"5", "CONSTANT"},
        // {")", "BRACKET"},
        // {"{", "BLOCK"},
        // {"int", "TYPE_SPECIFIER"},
        // {"p", "Identifier"},
        // {";", "SEMI"},
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
        // {";", "SEMI"},

        // {"z", "Identifier"},
        // {"=", "ASSIGNMENT"},
        // {"5", "CONSTANT"},
        // {";", "SEMI"},
        // {"(", "BRACKET"},
        // {"float", "TYPE_SPECIFIER"},
        // {"y", "Identifier"},
        // {",", "COMMA"},
        // {"int", "TYPE_SPECIFIER"},
        // {"z", "Identifier"},
        // {")", "BRACKET"},
        // {";", "SEMI"},
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
        // {";", "SEMI"},
        // {"int", "TYPE_SPECIFIER"},
        // {"x", "Identifier"},
        // {"(", "BRACKET"},
        // {"float", "TYPE_SPECIFIER"},
        // {"y", "Identifier"},
        // {",", "COMMA"},
        // {"int", "TYPE_SPECIFIER"},
        // {"z", "Identifier"},
        // {")", "BRACKET"},
        // {";", "SEMI"},
        // {"=", "ASSIGNMENT"},
        // {"10", "CONSTANT"},
        // {";", "SEMI"},
        // {"int", "TYPE_SPECIFIER"},
        // {"x", "ID"},
        // {"(", "BRACKET"},
        // {"float", "TYPE_SPECIFIER"},
        // {"y", "ID"},
        // {",", "COMMA"},
        // {"int", "TYPE_SPECIFIER"},
        // {"z", "ID"},
        // {")", "BRACKET"},
        // {";", "SEMI"},
        // {"=", "ASSIGNMENT"},
        // {"10", "CONSTANT"},
        // {";", "SEMI"},
        // write a hard test case for the parser

    };
    // int x = 5;
    // float x = 6;
    // cout << x << endl;

    //

    Parser2 parser(tokens);

    // parser.SymbolTable
    if (parser.parseProgram())
    {
        cout << "Parsing successful!" << endl;
    }
    else
    {
        cout << "Parsing failed!" << endl;
    }
    // for (int i = 0; i < parser.SymbolTable.size(); i++)
    // {
    //     cout << parser.SymbolTable[i].first << " first" << endl;
    //     cout << parser.SymbolTable[i].second << " second" << endl;
    // }
}