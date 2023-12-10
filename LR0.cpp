//
// Created by Oana on 12/10/2023.
//

#include <algorithm>
#include "LR0.h"

std::map<std::string, std::vector<Production>>
LR0::closure(const std::map<std::string, std::vector<Production>> &I, Grammar grammar) {
    std::map<std::string, std::vector<Production>> output;

    //initialize with I
    for (const auto &item: I)
        output.insert(item);


    bool changed;
    do {
        changed = false;
        for (const auto item: output) {
            for (const auto &prod: item.second) {
                std::string nonTerminal = prod.getPointValue();
                std::vector<Production> currentProductions = grammar.getProductionsForNonterminal(nonTerminal);

                for (const auto &smolprod: currentProductions) {
                    if(std::find(output[nonTerminal].begin(), output[nonTerminal].end(), smolprod) == output[nonTerminal].end()){
                        changed = true;
                        output[nonTerminal].push_back(smolprod);
                    }
                }
            }
        }


    } while (changed);

    return output;
}
