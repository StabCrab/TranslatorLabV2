//
// Created by trykr on 24.01.2023.
//

#ifndef TR6_PARSER_H
#define TR6_PARSER_H
#include <iostream>
#include <fstream>
#include <vector>
#include <map>


//E ::= ++S E1 | S E2 | I
//E1 ::= ε | = E
//E2 ::= ε | = E | ++


enum class Token
{
    PlusPlus, // ++
    S,
    Equals, // =
    I,
    Empty,
};

class Parser
{
private:
    std::string currentLine;
    Token token;
    std::ifstream file;
    std::map<std::string, int> S;
    std::string buf;
    Token scan();
    int Efunc();
    int E1func();
    int E2func();

public:
    Parser(std::string filename);
    ~Parser();

    bool parse();
    void printVars();


};


#endif //TR6_PARSER_H
