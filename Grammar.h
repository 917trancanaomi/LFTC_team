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

class Grammar {
public:
    Grammar();

    void readFromFile(const std::string& filename);
    void printNonterminals() const;
    void printTerminals() const;
    void printProductions() const;
    void productionsForSpecificNonterminal(const std::string& nonterminal) const;
    bool checkIfCFG() const;

    template <typename T>
    void printSet(const std::set<T>& s) const;

private:
    std::set<std::string> nonterminals;
    std::set<std::string> terminals;
    std::map<std::string, std::set<std::string>> productions;
    std::string startingSymbol;

    static const std::string EPSILON;

    void processNonterminals(std::ifstream& reader);
    void processTerminals(std::ifstream& reader);
    void processProductions(std::ifstream& reader);
    void processInitialState(std::ifstream& reader);

    static std::vector<std::string> splitString(const std::string& str, char delimiter);
    static std::set<std::string> splitStringToSet(const std::string& str, char delimiter);
    static std::string trim(const std::string& str);
    static std::string vectorToString(const std::set<std::string>& vec);

};

#endif //LFTC_TEAM_GRAMMAR_H
