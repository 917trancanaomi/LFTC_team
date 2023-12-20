//
// Created by Oana on 12/16/2023.
//

#ifndef LFTC_TEAM_PARSEOUTPUT_H
#define LFTC_TEAM_PARSEOUTPUT_H

#include <string>
#include <vector>
#include <ostream>
#include "Grammar.h"

struct Element {
    std::string info;
    int parent;
    int rightSibling;
};

class ParseOutput {
public:
    friend std::ostream &operator<<(std::ostream &os, const ParseOutput &output);

    std::vector<Element> table;

    void populateTableFromProductionString(std::vector<int> productionString, Grammar grammar) ;


};


#endif //LFTC_TEAM_PARSEOUTPUT_H
