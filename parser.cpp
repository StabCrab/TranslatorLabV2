//
// Created by trykr on 24.01.2023.
//

#include "parser.h"
#include <exception>

Parser::Parser(std::string filename)
{
    file.open(filename);
    if (!file.is_open())
    {
        throw std::invalid_argument("filename is not valid");
    }
}
Parser::~Parser()
{

}


bool Parser::parse()
{
    while(!file.eof())
    {
        std::getline(file, currentLine);
        token = scan();
        Efunc();
    }
    return true;
}

Token Parser::scan()
{
    if (currentLine.empty())
    {
        return Token ::Empty;
    }
    while (currentLine[0] == ' ')
    {
        currentLine.erase(0,1);
    }
    if (currentLine[0] == '+')
    {
        if (currentLine[1] == '+')
        {
            currentLine.erase(0,2);
            return Token::PlusPlus;
        }
        else
        {
            std::__throw_invalid_argument("Unsupported token");
        }
    }
    if (currentLine[0] == '=')
    {
        currentLine.erase(0,1);
        return Token::Equals;
    }
    if (isalpha(currentLine[0]))
    {
        int i = 0;
        buf.clear();
        while (isalpha(currentLine[i]) || isdigit(currentLine[i]))
        {
            buf.push_back(currentLine[i]);
            ++i;
        }
        currentLine.erase(0,i);
        if (S.find(buf) == S.end())
        {
            S.insert(std::make_pair(buf, 0));
        }
        return Token::S;
    }
    if (isdigit(currentLine[0]))
    {
        int i = 0;
        buf.clear();
        while (isdigit(currentLine[i]))
        {
            buf.push_back(currentLine[i]);
            ++i;
        }
        currentLine.erase(0,i);
        return Token::I;
    }
    std::__throw_invalid_argument("Unsupported token");
}


void Parser::printVars()
{
    for (std::pair<const std::basic_string<char>, int> i : S)
    {
        std::cout << i.first << '=' << i.second << '\n';
    }
}

int Parser::Efunc()
{
    if (token == Token::PlusPlus)
    {
        token = scan();
        if (token == Token::S)
        {
            token = scan();
            return E1func();
        }
        else
            std::__throw_invalid_argument("Error");
    }
    else if (token == Token::S)
    {
        token = scan();
        return E2func();
    }
    else if (token == Token::I)
    {
        token = scan();
        if (token != Token::Empty)
            std::__throw_invalid_argument("Error");
        return std::stoi(buf);
    }
    std::__throw_invalid_argument("Error");
}

int Parser::E1func()
{
    if (token == Token::Equals)
    {
        std::string a = buf;
        token = scan();
        S.at(a) = Efunc();
        return S.at(a);
    }
    else if (token == Token::Empty)
    {
        return S.at(buf);
    }
    std::__throw_invalid_argument("Error");
}

int Parser::E2func()
{
    if (token == Token::Equals)
    {
        std::string a = buf;
        token = scan();
        S.at(a) = Efunc();
        return S.at(a);
    }
    else if (token == Token::Empty)
    {
        return S.at(buf);
    }
    else if (token == Token::PlusPlus)
    {
        S.at(buf)++;
        token = scan();
        if (token != Token::Empty)
            std::__throw_invalid_argument("Error");
        return S.at(buf);
    }
}


