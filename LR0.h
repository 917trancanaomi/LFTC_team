//
// Created by Oana on 12/10/2023.
//

#ifndef LFTC_TEAM_LR0_H
#define LFTC_TEAM_LR0_H


#include <stack>
#include "Production.h"
#include "Grammar.h"
#include "CanonicalCollection.h"

#define ACCEPT "accept"
#define SHIFT "shift"
#define REDUCE "reduce"

class LR0 {
private:
    //structure of parsing table
    //map with key = state number (0,1,2,3 etc.)
    // value = pair<action, goto>
    // action = shift | reduce | accept
    // goto = vector<pair<element, state_number>>
   std::map<int, std::pair<std::string, std::vector<std::pair<std::string, int>>>> parsingTable;

public:
    std::map<std::string, std::vector<Production>>
    closure(const std::map<std::string, std::vector<Production>> &I, Grammar grammar);

    std::map<std::string, std::vector<Production>>
    goTo(const std::map<std::string, std::vector<Production>> &I, Grammar grammar, std::string X);

    CanonicalCollection canonicalCollection(Grammar grammar);

    std::string
    action(std::map<std::string, std::vector<Production>> state, Grammar grammar, int i);

    int goToNextState(CanonicalCollection canonicalCollection, std::map<std::string, std::vector<Production>> state,
                      Grammar grammar, std::string element);

    bool completeParsingTable(Grammar grammar);

    void printParsingTable();

    /*
     * deci aici se va face parsarea unei secvente
     * ma gandesc ca o secventa trebuie citita cumva dar mno ca la gramatici doar cu litere e chill
     * dar cand va fi cu PIF o sa fie tare urat, desi ma gandesc ca putem sa il intrebam pe prof exact
     * cum.
     * Aici daca se incearca accesarea unui lucru care nu este in map trebuie sa spui ca nu e o secventa
     * acceptata => poti returna vectorul cu un singur element (-1)  ++++ trebuie afisat locul/unde crapa
     * ori simbolul/productia ori ceva de acolo
     * basically trebuie implementat exact ce am facut la seminar si are si profa explicatii
     */
    std::vector<int> parseSequence(Grammar& grammar, const std::vector<std::string>& inputSequence);
};


#endif //LFTC_TEAM_LR0_H