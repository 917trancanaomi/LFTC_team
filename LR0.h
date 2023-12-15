//
// Created by Oana on 12/10/2023.
//

#ifndef LFTC_TEAM_LR0_H
#define LFTC_TEAM_LR0_H


#include "Production.h"
#include "Grammar.h"
#include "CanonicalCollection.h"

class LR0 {

public:
    std::map<std::string, std::vector<Production>>
    closure(const std::map<std::string, std::vector<Production>>& I, Grammar grammar);

    std::map<std::string, std::vector<Production>> goTo(const std::map<std::string, std::vector<Production>>& I, Grammar grammar, std::string X);
    CanonicalCollection canonicalCollection(Grammar grammar);

    //ParsingTable getParsingTable(const CanonicalCollection& canonicalCollection, const Grammar& grammar);


};


#endif //LFTC_TEAM_LR0_H
