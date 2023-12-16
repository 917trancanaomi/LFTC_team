//
// Created by Oana on 12/10/2023.
//

#include <algorithm>
#include "LR0.h"

std::map<std::string, std::vector<Production>>
LR0::closure(const std::map<std::string, std::vector<Production>> &I, Grammar grammar) {
    std::map<std::string, std::vector<Production>> oldOutput;

    //initialize with I
    for (const auto &item: I)
        oldOutput.insert(item);

    bool changed;
    do {
        changed = false;
        std::map<std::string, std::vector<Production>> newOutput;
        for (const auto &item: oldOutput) {
            newOutput[item.first] = item.second;
        }

        for (const auto item: oldOutput) {
            for (const auto &prod: item.second) {
                if (!prod.isPointAtEnd()) {
                    std::string nonTerminal = prod.getPointValue();
                    std::vector<Production> currentProductions = grammar.getProductionsForNonterminal(nonTerminal);

                    for (const auto &smolprod: currentProductions) {
                        if (oldOutput.find(nonTerminal) == oldOutput.end() ||
                            std::find(oldOutput[nonTerminal].begin(), oldOutput[nonTerminal].end(), smolprod) ==
                            oldOutput[nonTerminal].end()) {
                            changed = true;
                            newOutput[nonTerminal].push_back(smolprod);
                        }

                    }
                }
            }
        }
        oldOutput.clear();
        for (const auto &item: newOutput) {
            oldOutput[item.first] = item.second;
        }

    } while (changed);

    return oldOutput;
}

std::map<std::string, std::vector<Production>>
LR0::goTo(const std::map<std::string, std::vector<Production>> &I, Grammar grammar, std::string X) {
    std::map<std::string, std::vector<Production>> output;
    for (const auto &item: I) {
        for (Production prod: item.second) {
            if (prod.getPointValue() == X) {
                Production aux(prod);
                aux.incrementPoint();
                output[item.first].push_back(aux);
            }
        }
    }
    return closure(output, grammar);
}

CanonicalCollection LR0::canonicalCollection(Grammar grammar) {
    CanonicalCollection oldCanonicalCollection;

    // Construct the initial state
    std::map<std::string, std::vector<Production>> initialItems;
    initialItems[grammar.startingSymbol] = grammar.getProductionsForNonterminal(grammar.startingSymbol);

    // Use the existing closure function
    std::map<std::string, std::vector<Production>> initialClosure = closure(initialItems, grammar);
    oldCanonicalCollection.addState(initialClosure);

    bool changed;
    do {
        changed = false;
        CanonicalCollection newCanonicalCollection(oldCanonicalCollection);
        for (int i = 0; i < oldCanonicalCollection.states.size(); i++) {
            auto item = oldCanonicalCollection.states[i];
            std::vector<std::string> elements;
            elements.clear();
            for (const auto &currentProduction: item) {
                for (const auto &input: currentProduction.second) {
                    if (!input.isPointAtEnd())
                        elements.push_back(input.getPointValue());
                }
            }
            for (const auto &element: elements) {
                std::map<std::string, std::vector<Production>> newStateItems = goTo(
                        item, grammar, element
                );

                if (!newStateItems.empty() && !oldCanonicalCollection.stateExists(newStateItems)) {
                    newCanonicalCollection.addState(newStateItems);
                    changed = true;
                }

            }

        }
        oldCanonicalCollection = newCanonicalCollection;
    } while (changed);

    return oldCanonicalCollection;
}

