//
// Created by Oana on 12/10/2023.
//

#ifndef LFTC_TEAM_LR0_H
#define LFTC_TEAM_LR0_H


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
    action(std::map<std::string, std::vector<Production>> state, Grammar grammar);

    int goToNextState(CanonicalCollection canonicalCollection, std::map<std::string, std::vector<Production>> state,
                      Grammar grammar, std::string element);

    void completeParsingTable(Grammar grammar);

    void printParsingTable();

};


#endif //LFTC_TEAM_LR0_H
