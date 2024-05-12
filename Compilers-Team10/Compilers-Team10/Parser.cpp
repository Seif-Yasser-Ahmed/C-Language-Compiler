// #include <iostream>
// #include <vector>
// #include <string>
// #include "Token.h"
// using namespace std;

struct Token
{
    string lexeme; // the string
    string type;
    int num;
};

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

class Parser
{
public:
    Parser(const vector<Token> &tokens) : tokens(tokens), currentTokenIndex(0) {}

    bool parseProgram()
    {
        return parseDeclarationList(); // we check with this if parsing successful
    }

private:
    const vector<Token> &tokens; // vector of token
    size_t currentTokenIndex;    // 3ashan netabe3 el tokens index
    bool ifCond = false;

    Token getCurrentToken()
    {
        return tokens[currentTokenIndex];
    }

    void consumeToken()
    { // go to next token
        currentTokenIndex++;
    }

    void reportError(const string &message)
    { // to gracefully handle error
        cout << "Error: " << message << endl;
    }

    // / START OF PARSING FUNCTIONS /

    bool parseDeclarationList()
    { // just to loop on our vector and start the algorithm for recursive descent parsing
        while (currentTokenIndex < tokens.size())
        {
            if (!parseDeclaration())
            { // recursive descent technique, a lot of recursion and function calls will be made to check grammar
                cout << getCurrentToken().lexeme << endl;
                return false; // there is error
            }
        }
        return true; // no errors
    }

    bool parseDeclaration()
    { // matching tokens here in appropriate order
        if (getCurrentToken().lexeme == "}" && currentTokenIndex == tokens.size() - 1)
        {
            consumeToken();
            return true;
        }
        if (!parseTypeSpecifier() && getCurrentToken().type != "BLOCK")
        { // must find float, int,....
            reportError("Expected type specifier");
            return false; // error
        }

        if (getCurrentToken().type == "ID")
        { // must get identifier afte type specifier ex: x in int x
            consumeToken();
        }
        else if (getCurrentToken().type != "BLOCK")
        {
            reportError("Expected identifier");
            return false; // error
        }
        if (getCurrentToken().type == "BLOCK")
        {
            parseBlockStatement();
        }
        if (getCurrentToken().lexeme == "}" && currentTokenIndex == tokens.size() - 1)
        {
            consumeToken();
            return true;
        }
        if (getCurrentToken().lexeme == "=")
        { // this is optional, not having '=' wont cause errors
            consumeToken();
            if (!parseExpression())
            { // check expressions conform to grammar
                return false;
            }
        }

        if (getCurrentToken().lexeme == ";")
        {
            consumeToken(); // Consume ';'
            /*if (!parseExpression()) {
                return false;
            } */
        }
        else
        {
            if (getCurrentToken().lexeme == "(")
            {
                if (!parseExpression())
                    return false;
            }
            if (getCurrentToken().lexeme == ";")
            {                   // this is not optional
                consumeToken(); // Consume ';'
                if (currentTokenIndex < tokens.size())
                {
                    if (!parseExpression())
                        return false;
                }
            }
            else
            {
                // cout << "We're here" << endl;
                // if (scErrorCall()) then say expected semicolon
                reportError("Expected semicolon");
                return false;
            }
        }
        return true; // No errors encountered
    }

    bool parseTypeSpecifier()
    { // zay int,float,....
        if (getCurrentToken().type == "TYPE_SPECIFIER")
        {
            consumeToken(); // go to next token
            return true;
        }
        else
        {
            return false;
        }
    }

    bool parseExpression()
    { // parsing expressions, like and, or, addition, shifting,....
        if (getCurrentToken().type == "BLOCK")
        {
            // cout << parseBlockStatement();
            parseBlockStatement();
        }
        return parseConditionalExpression();
    }

    bool parseConditionalExpression()
    {
        if (!parseLogicalOrExpression())
        {                 // go to next function
            return false; // something wrong with syntax (go to parseCastExpression() and parseUnaryExpression() functions about line 280 to understand why)
        }

        if (getCurrentToken().lexeme == "?")
        {
            consumeToken();
            if (!parseExpression())
            {
                return false;
            }
            if (getCurrentToken().lexeme != ":")
            {
                reportError("Expected ':'");
                return false;
            }
            consumeToken();
            return parseConditionalExpression();
        }

        return true;
    }

    bool parseLogicalOrExpression()
    {
        if (!parseLogicalAndExpression())
        {                 // go to next function....
            return false; // error in syntax again, go next function. we keep going to next function till last two (parseCastExpression() and parseUnaryExpression())
        }

        while (getCurrentToken().lexeme == "||")
        {
            consumeToken();
            if (!parseLogicalAndExpression())
            { // still need to check syntax of following expression
                return false;
            }
        }

        return true;
    }

    bool parseLogicalAndExpression()
    { // same comments 5alas
        if (!parseInclusiveOrExpression())
        {
            return false;
        }

        while (getCurrentToken().lexeme == "&&")
        {
            consumeToken();
            if (!parseInclusiveOrExpression())
            {
                return false;
            }
        }

        return true;
    }

    bool parseInclusiveOrExpression()
    {
        if (!parseExclusiveOrExpression())
        {
            return false;
        }

        while (getCurrentToken().lexeme == "|")
        {
            consumeToken();
            if (!parseExclusiveOrExpression())
            {
                return false;
            }
        }

        return true;
    }

    bool parseExclusiveOrExpression()
    {
        if (!parseAndExpression())
        {
            return false;
        }

        while (getCurrentToken().lexeme == "^")
        {
            consumeToken();
            if (!parseAndExpression())
            {
                return false;
            }
        }

        return true;
    }

    bool parseAndExpression()
    {
        if (!parseEqualityExpression())
        {
            return false;
        }

        while (getCurrentToken().lexeme == "&")
        {
            consumeToken();
            if (!parseEqualityExpression())
            {
                return false;
            }
        }

        return true;
    }

    bool parseEqualityExpression()
    {
        if (!parseRelationalExpression())
        {
            return false;
        }

        while (getCurrentToken().lexeme == "==" || getCurrentToken().lexeme == "!=")
        {
            consumeToken();
            if (!parseRelationalExpression())
            {
                return false;
            }
        }

        return true;
    }

    bool parseRelationalExpression()
    {
        if (!parseShiftExpression())
        {
            return false;
        }

        while (getCurrentToken().lexeme == "<" || getCurrentToken().lexeme == ">" ||
               getCurrentToken().lexeme == "<=" || getCurrentToken().lexeme == ">=")
        {
            consumeToken();
            if (!parseShiftExpression())
            {
                return false;
            }
        }

        return true;
    }

    bool parseShiftExpression()
    {
        if (!parseAdditiveExpression())
        {
            return false;
        }

        while (getCurrentToken().lexeme == "<<" || getCurrentToken().lexeme == ">>")
        {
            consumeToken();
            if (!parseAdditiveExpression())
            {
                return false;
            }
        }

        return true;
    }

    bool parseAdditiveExpression()
    {
        if (!parseMultiplicativeExpression())
        {
            return false;
        }

        while (getCurrentToken().lexeme == "+" || getCurrentToken().lexeme == "-")
        {
            consumeToken();
            if (!parseMultiplicativeExpression())
            {
                return false;
            }
        }

        return true;
    }

    bool parseMultiplicativeExpression()
    {
        if (!parseCastExpression())
        {
            return false;
        }

        while (getCurrentToken().lexeme == "*" || getCurrentToken().lexeme == "/" ||
               getCurrentToken().lexeme == "%")
        {
            consumeToken();
            if (!parseCastExpression())
            {
                return false;
            }
        }

        return true;
    }

    bool parseCastExpression()
    { // when u cast the datatype ex: x = (int)y;
        if (getCurrentToken().lexeme == "(")
        {
            consumeToken();
            if (!parseTypeSpecifier() && !ifCond)
            {
                return parseFunctionCallExpression();
            }
            if (getCurrentToken().lexeme != ")")
            {
                // reportError("Expected ')'");
                if (!ifCond)
                    return parseFunctionDeclarationExpression();
            }
            consumeToken();
            return parseCastExpression();
        }
        else
        {
            return parseUnaryExpression(); // 3ashan el galna mesh cast expression
        }
    }

    bool parseUnaryExpression()
    {
        if (getCurrentToken().type == "ID" || getCurrentToken().type == "CONSTANT" ||
            getCurrentToken().type == "STRING_LITERAL")
        {
            consumeToken();
            return true;
        }
        else if (getCurrentToken().lexeme == "(")
        {
            consumeToken();
            if (!parseExpression())
            {
                return false;
            }
            if (getCurrentToken().lexeme != ")")
            {
                reportError("Expected ')'");
                return false;
            }
            consumeToken();
            return true;
        }
        else if (getCurrentToken().type == "BLOCK")
        {
            // cout << "Block, lexeme is " << getCurrentToken().lexeme << endl;
            return parseBlockStatement();
        }
        else
        {
            // reportError("Invalid unary expression");
            // cout << "func declaration, lexeme is " << getCurrentToken().lexeme << endl;
            cout << getCurrentToken().lexeme << endl;
            if (!ifCond)
                return parseFunctionDeclarationExpression();
            // else parseIf();
        }
    }

    bool parseFunctionCallExpression()
    {
        bool flag = false;
        if (getCurrentToken().lexeme == ")")
        {
            flag = true;
            consumeToken();
        }
        else
        {
            if (getCurrentToken().type == "ID")
            {
                consumeToken();
                while (getCurrentToken().type == "COMMA")
                {
                    consumeToken();
                    if (getCurrentToken().type == "ID")
                    {
                        consumeToken();
                        flag = true;
                    }
                }
                if (getCurrentToken().lexeme != ")")
                    flag = false;
                else
                    consumeToken();
            }
        }
        if (flag == false)
        {
            reportError("Error at function call");
        }
        return flag;
    }

    bool parseFunctionDeclarationExpression()
    {
        bool flag = false;
        if (getCurrentToken().type == "ID")
        {
            consumeToken();
            while (getCurrentToken().type == "COMMA")
            {
                consumeToken();
                if (getCurrentToken().type == "TYPE_SPECIFIER")
                {
                    consumeToken();
                    if (getCurrentToken().type == "ID")
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
            reportError("Error at function declaration");
            return flag;
        }
        /*if (getCurrentToken().lexeme == "{") {
            flag = parseFnBlock();
        }*/
        return flag;
    }

    bool parseBlockStatement()
    {
        if (getCurrentToken().type == "BLOCK")
        {
            if (getCurrentToken().lexeme == "if")
            {
                ifCond = true;
                // cout << "TRUE" << " "<<ifCond << endl;
                return parseIf();
            } // for if, else if and else
            if (getCurrentToken().lexeme == "{")
                return true;
            if (getCurrentToken().lexeme == "}")
                return true;

            /*else if (getCurrentToken().lexeme == "for") if (!parseFor())return false;
            else if (getCurrentToken().lexeme == "while") if (!parseWhile())return false;
            else if (getCurrentToken().lexeme == "do") if (!parseDo())return false;*/
        }
        else
        {
            consumeToken();
            return true;
        }
    }

    bool parseIf()
    {
        consumeToken();
        if (getCurrentToken().lexeme == "(")
        {
            consumeToken();
            if (!parseExpression())
                return false;
            // if (getCurrentToken().lexeme == "(") return parseIf();
            if (getCurrentToken().lexeme != ")")
            {
                return false;
            }
            else
                consumeToken();
            if (getCurrentToken().lexeme == "{")
            {
                consumeToken();

                // cout << getCurrentToken().lexeme << getCurrentToken().type << endl;
                if (!parseDeclaration())
                    return false;
                if (getCurrentToken().lexeme == "}")
                {
                    // / consumeToken();
                    // /
                    ifCond = false; // t2reeban 8alat
                    return true;
                }
            }
            return true;
        }
        else
        {
            reportError("invalid if condition syntax");
            return false;
        }
    }

    /* bool parseFor() {

     }
     bool parseWhile() {

     }

     bool parseDo() {

     }*/
};

int main()
{
    // replace with actual tokens from our scanner, this vector is made to store the tokens
    vector<Token> tokens = {
        // Test1*// if condition (WORKING!!!!!!!!)
        /*{"int", "TYPE_SPECIFIER"},
         {"y", "ID"},
         {";", "SEMI"},*/
        {"if", "BLOCK"},
        {"(", "BRACKET"},
        {"y", "ID"},
        {"==", "ASSIGNMENT"},
        {"5", "CONSTANT"},
        {")", "BRACKET"},
        {"{", "BLOCK"},
        // {";", "SEMI"},
        {"if", "BLOCK"},
        {"(", "BRACKET"},
        {"y", "ID"},
        {"==", "ASSIGNMENT"},
        {"5", "CONSTANT"},
        {")", "BRACKET"},
        {"{", "BLOCK"},
        {"int", "TYPE_SPECIFIER"},
        {"y", "ID"},
        {";", "SEMI"},
        {"}", "BLOCK"},

        {"}", "BLOCK"}
        // Test2// Basic test, assignments (WORKING)
        /* {"int", "TYPE_SPECIFIER"},
         {"x", "ID"},
         {";", "SEMI"},
         {"float", "TYPE_SPECIFIER"},
         {"y", "ID"},
         {"=", "ASSIGNMENT"},
         {"10", "CONSTANT"},
         {";", "SEMI"}*/
        //*Test3// function declaration, calls, empty parameters list (WORKING)
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
    };

    /*{"int", "TYPE_SPECIFIER"},
    {"x", "ID"},
    {"(", "BRACKET"},
    {"float", "TYPE_SPECIFIER"},
    {"y", "ID"},
    {",", "COMMA"},
    {"int", "TYPE_SPECIFIER"},
    {"z", "ID"},
    {")", "BRACKET"},
    {";", "SEMI"},*/
    /*{"=", "ASSIGNMENT"},
    {"10", "CONSTANT"},
    {";", "SEMI"}*/
    //};
    int a = 0;

    Parser parser(tokens);
    if (parser.parseProgram())
    {
        cout << "Parsing successful!" << endl;
    }
    else
    {
        cout << "Parsing failed!" << endl;
    }
}
