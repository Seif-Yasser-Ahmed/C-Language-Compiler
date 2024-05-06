#include <iostream>
#include <vector>
#include <string>

using namespace std;

struct Token {
    string lexeme; // the string
    string type;
    int num;
};


class Parser {
public:
    Parser(const vector<Token>& tokens) : tokens(tokens), currentTokenIndex(0) {}

    bool parseProgram() {
        return parseDeclarationList(); // we check with this if parsing successful 
    }

private:
    const vector<Token>& tokens; // vector of token 
    size_t currentTokenIndex; // 3ashan netabe3 el tokens index

    
    Token getCurrentToken() {
        return tokens[currentTokenIndex];
    }

    
    void consumeToken() { // go to next token
        currentTokenIndex++;
    }

    
    void reportError(const string& message) { //to gracefully handle error
        cout << "Error: " << message << endl;
    }

        /*****************************************************START OF PARSING FUNCTIONS*****************************************************/

    bool parseDeclarationList() { //just to loop on our vector and start the algorithm for recursive descent parsing
        while (currentTokenIndex < tokens.size()) {
            if (!parseDeclaration()) { // recursive descent technique, a lot of recursion and function calls will be made to check grammar 
                return false; // there is error 
            }
        }
        return true; // no errors 
    }

    bool parseDeclaration() { //matching tokens here in appropriate order
        if (!parseTypeSpecifier()) { //must find float, int,....
            reportError("Expected type specifier");
            return false; //error 
        }

        if (getCurrentToken().type == "ID") { //must get identifier afte type specifier ex: x in int x
            consumeToken(); 
        }
        else {
            reportError("Expected identifier");
            return false; //error 
        }

        if (getCurrentToken().lexeme == "=") { //this is optional, not having '=' wont cause errors 
            consumeToken(); 
            if (!parseExpression()) { //check expressions conform to grammar 
                return false; 
            }
        }

        if (getCurrentToken().lexeme == ";") { 
            consumeToken(); // Consume ';'
        }
        else {
            if (getCurrentToken().lexeme == "(") {
                if(!parseExpression()) return false;
            }
            if (getCurrentToken().lexeme == ";") { //this is not optional
                consumeToken(); // Consume ';'
            }
            else{
                //cout << "We're here" << endl;
                //if (scErrorCall()) then say expected semicolon
                reportError("Expected semicolon");
                return false;
            }
        }

        return true; // No errors encountered
    }

    bool parseTypeSpecifier() {//zay int,float,....
        if (getCurrentToken().type == "TYPE_SPECIFIER") {
            consumeToken(); // go to next token
            return true; 
        }
        else {
            return false; 
        }
    }

    bool parseExpression() { //parsing expressions, like and, or, addition, shifting,.... 
        return parseConditionalExpression();
    }

    bool parseConditionalExpression() {
        if (!parseLogicalOrExpression()) { // go to next function
            return false; //something wrong with syntax (go to parseCastExpression() and parseUnaryExpression() functions about line 280 to understand why)
        }

        if (getCurrentToken().lexeme == "?") {
            consumeToken(); 
            if (!parseExpression()) {
                return false; 
            }
            if (getCurrentToken().lexeme != ":") {
                reportError("Expected ':'");
                return false;
            }
            consumeToken();
            return parseConditionalExpression();
        }

        return true; 
    }

    bool parseLogicalOrExpression() {
        if (!parseLogicalAndExpression()) { // go to next function....
            return false; //error in syntax again, go next function. we keep going to next function till last two (parseCastExpression() and parseUnaryExpression())
        }

        while (getCurrentToken().lexeme == "||") {
            consumeToken(); 
            if (!parseLogicalAndExpression()) {  //still need to check syntax of following expression
                return false; 
            }
        }

        return true; 
    }

    bool parseLogicalAndExpression() { // same comments 5alas
        if (!parseInclusiveOrExpression()) {
            return false;
        }

        while (getCurrentToken().lexeme == "&&") {
            consumeToken(); 
            if (!parseInclusiveOrExpression()) {
                return false; 
            }
        }

        return true; 
    }

    bool parseInclusiveOrExpression() {
        if (!parseExclusiveOrExpression()) {
            return false;
        }

        while (getCurrentToken().lexeme == "|") {
            consumeToken(); 
            if (!parseExclusiveOrExpression()) {
                return false;
            }
        }

        return true;
    }

    bool parseExclusiveOrExpression() {
        if (!parseAndExpression()) {
            return false;
        }

        while (getCurrentToken().lexeme == "^") {
            consumeToken(); 
            if (!parseAndExpression()) {
                return false; 
            }
        }

        return true; 
    }

    bool parseAndExpression() {
        if (!parseEqualityExpression()) {
            return false;
        }

        while (getCurrentToken().lexeme == "&") {
            consumeToken(); 
            if (!parseEqualityExpression()) {
                return false;
            }
        }

        return true; 
    }

    bool parseEqualityExpression() {
        if (!parseRelationalExpression()) {
            return false;
        }

        while (getCurrentToken().lexeme == "==" || getCurrentToken().lexeme == "!=") {
            consumeToken(); 
            if (!parseRelationalExpression()) {
                return false; 
            }
        }

        return true; 
    }

    bool parseRelationalExpression() {
        if (!parseShiftExpression()) {
            return false;
        }

        while (getCurrentToken().lexeme == "<" || getCurrentToken().lexeme == ">" ||
            getCurrentToken().lexeme == "<=" || getCurrentToken().lexeme == ">=") {
            consumeToken();
            if (!parseShiftExpression()) {
                return false; 
            }
        }

        return true; 
    }

    bool parseShiftExpression() {
        if (!parseAdditiveExpression()) {
            return false;
        }

        while (getCurrentToken().lexeme == "<<" || getCurrentToken().lexeme == ">>") {
            consumeToken(); 
            if (!parseAdditiveExpression()) {
                return false;
            }
        }

        return true; 
    }

    bool parseAdditiveExpression() {
        if (!parseMultiplicativeExpression()) {
            return false;
        }

        while (getCurrentToken().lexeme == "+" || getCurrentToken().lexeme == "-") {
            consumeToken(); 
            if (!parseMultiplicativeExpression()) {
                return false;
            }
        }

        return true; 
    }

    bool parseMultiplicativeExpression() {
        if (!parseCastExpression()) {
            return false;
        }

        while (getCurrentToken().lexeme == "*" || getCurrentToken().lexeme == "/" ||
            getCurrentToken().lexeme == "%") {
            consumeToken(); 
            if (!parseCastExpression()) {
                return false; 
            }
        }

        return true; 
    }

    bool parseCastExpression() { // when u cast the datatype ex: x = (int)y;
        if (getCurrentToken().lexeme == "(") {
            consumeToken(); 
            if (!parseTypeSpecifier()) {
                return parseFunctionCallExpression();
            }
            if (getCurrentToken().lexeme != ")") {
                //reportError("Expected ')'");
                return parseFunctionDeclarationExpression();
            }
            consumeToken(); 
            return parseCastExpression();
        }
        else {
            return parseUnaryExpression(); // 3ashan el galna mesh cast expression
        }
    }

    bool parseUnaryExpression() {
        if (getCurrentToken().type == "ID" || getCurrentToken().type == "CONSTANT" ||
            getCurrentToken().type == "STRING_LITERAL") {
            consumeToken(); 
            return true; 
        }
        else if (getCurrentToken().lexeme == "(") {
            consumeToken(); 
            if (!parseExpression()) { 
                return false; 
            }
            if (getCurrentToken().lexeme != ")") {
                reportError("Expected ')'");
                return false;
            }
            consumeToken();
            return true; 
        }
        else {
            //reportError("Invalid unary expression");
            return parseFunctionDeclarationExpression();
        }
    }

    bool parseFunctionCallExpression() {
        bool flag = false;
        if (getCurrentToken().lexeme == ")") {
            flag = true;
            consumeToken();
        }
        else {
            if (getCurrentToken().type == "ID") {
                consumeToken();
                while (getCurrentToken().type == "COMMA") {
                    consumeToken();
                    if (getCurrentToken().type == "ID") {
                        consumeToken();
                        flag = true;
                    }
                }
                if (getCurrentToken().lexeme != ")") flag = false;
                else consumeToken();
            }
        }
        if (flag == false) {
            reportError("Error at function call");
        }
        return flag;
    }

    bool parseFunctionDeclarationExpression() { //also used for declaring functions with no parameters 
        bool flag = false;
        if (getCurrentToken().type == "ID") {
            consumeToken();
            while (getCurrentToken().type == "COMMA"){
                consumeToken();
                if (getCurrentToken().type == "TYPE_SPECIFIER") {
                    consumeToken();
                    if (getCurrentToken().type == "ID") {
                        consumeToken();
                        flag = true;
                    }
                    else flag = false;
                }
                else flag = false;
            } 
            if (getCurrentToken().lexeme != ")") flag = false;
            else consumeToken();
        }
        //cout << "DONE!" << endl;
        if (flag == false) {
            reportError("Error at function declaration");
        }
        return flag;
    }

};

int main() {
    // replace with actual tokens from our scanner, this vector is made to store the tokens 
    vector<Token> tokens = {
        {"int", "TYPE_SPECIFIER"},
        {"x", "ID"},
        {"(", "BRACKET"},
        //{"float", "TYPE_SPECIFIER"},
        {"y", "ID"},
        {",", "COMMA"},
        {"int", "TYPE_SPECIFIER"},
        {"z", "ID"},
        {")", "BRACKET"},
        {";", "SEMI"},
        /*{"=", "ASSIGNMENT"},
        {"10", "CONSTANT"},
        {";", "SEMI"}*/
    };

    Parser parser(tokens);
    if (parser.parseProgram()) {
        cout << "Parsing successful!" << endl;
    }
    else {
        cout << "Parsing failed!" << endl;
    }
}
