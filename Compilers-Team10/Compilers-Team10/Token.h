#include <string.h>
#include <string>
#ifndef TOKEN_H
#define TOKEN_H

#pragma once
using namespace std;
class Token
{
public:
    Token();
    ~Token();
    void setToken(string lexeme, string type);
    string lexeme; // the string
    string type;

private:
};

#endif