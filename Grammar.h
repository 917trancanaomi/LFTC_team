//
// Created by Naomi on 12/7/2023.
//

#ifndef LFTC_TEAM_GRAMMAR_H
#define LFTC_TEAM_GRAMMAR_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <set>
#include <map>
#include <vector>
#include "Production.h"

class Grammar {
public:
    Grammar();

    void readFromFile(const std::string& filename);
    void printNonterminals() const;
    void printTerminals() const;
    void printProductions() const;
    void productionsForSpecificNonterminal(const std::string& nonterminal) const;
    bool checkIfCFG() const;

    std::vector<Production> getProductionsForNonterminal(std::string nonterminal);


private:
    std::set<std::string> nonterminals;
    std::set<std::string> terminals;
    std::map<std::string, std::vector<Production>> productions;
    std::string startingSymbol;

    static const std::string EPSILON;

    void processNonterminals(std::ifstream& reader);
    void processTerminals(std::ifstream& reader);
    void processProductions(std::ifstream& reader);
    void processInitialState(std::ifstream& reader);

};

#endif //LFTC_TEAM_GRAMMAR_H
