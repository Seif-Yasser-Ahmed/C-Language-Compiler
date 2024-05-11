#include "Token.h"
using namespace std;
Token::Token()
{
}

Token::~Token()
{
}

void Token::setToken(string lexeme1, string type1)
{
    lexeme = lexeme1;
    type = type1;
}