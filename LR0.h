//
// Created by Oana on 12/10/2023.
//

#ifndef LFTC_TEAM_LR0_H
#define LFTC_TEAM_LR0_H


#include "Production.h"
#include "Grammar.h"

class LR0 {

public:
    std::map<std::string, std::vector<Production>>
    closure(const std::map<std::string, std::vector<Production>>& I, Grammar grammar);

    std::vector<Production> goTo(std::vector<Production>);

};


#endif //LFTC_TEAM_LR0_H
