//
// Created by Oana on 12/10/2023.
//

#include <algorithm>
#include "LR0.h"
#include "State.h"

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
                    if (output.find(nonTerminal) == output.end() ||
                        std::find(output[nonTerminal].begin(), output[nonTerminal].end(), smolprod) ==
                        output[nonTerminal].end()) {
                        changed = true;
                        output[nonTerminal].push_back(smolprod);
                    }

                }
            }
        }


    } while (changed);

    return output;
}

std::map<std::string, std::vector<Production>>
LR0::goTo(const std::map<std::string, std::vector<Production>> &I, Grammar grammar, std::string X) {
    std::map<std::string, std::vector<Production>> output;
    if (I.empty())
        return output;
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
    CanonicalCollection canonicalCollection;
    std::cout << "Entering canonicalCollection function..." << std::endl;

    // Construct the initial state
    std::map<std::string, std::vector<Production>> initialItems;
    initialItems[grammar.startingSymbol] = grammar.getProductionsForNonterminal(grammar.startingSymbol);

    // Use the existing closure function
    std::map<std::string, std::vector<Production>> initialClosure = closure(initialItems, grammar);
    canonicalCollection.addState(initialClosure);

    std::vector<std::string> elements;
    for (const auto &item: grammar.terminals)
        elements.emplace_back(item);

    for (const auto &item: grammar.nonterminals)
        elements.emplace_back(item);

    bool changed;
    do {
        changed = false;
        for (int i = 0; i < canonicalCollection.states.size(); i++) {
            auto item = canonicalCollection.states[i];
            if (!item.empty()) {
                elements.clear();
                for (const auto &newitem: item) {
                    for (const auto &shhhhh: newitem.second) {
                        if (!shhhhh.isPointAtEnd())
                            elements.push_back(shhhhh.getPointValue());
                    }
                }
                for (int j = 0; j < elements.size(); j++) {
                    std::map<std::string, std::vector<Production>> newStateItems = goTo(
                            item, grammar, elements[j]
                    );

                    if (!newStateItems.empty() && !canonicalCollection.stateExists(newStateItems)) {
                        canonicalCollection.addState(newStateItems);
                        changed = true;
                    }

                }
            }
        }
    } while (changed);

    return canonicalCollection;
}


//
//CanonicalCollection LR0::canonicalCollection(const Grammar& grammar) {
//    CanonicalCollection canonicalCollection;
//    std::cout << "Entering canonicalCollection function..." << std::endl;
//
//    // Construct the initial state
//    State initialItems = closure(Item(grammar.startingSymbol, {grammar.startingSymbol}, 0), grammar);
//    canonicalCollection.addState(State(initialItems));
//
//    size_t index = 0;
//    while (index < canonicalCollection.getStates().size()) {
//        for (const std::string& symbol : canonicalCollection.getStates()[index].getSymbolsAfterTheDot()) {
//            State newState = goTo(canonicalCollection.getStates()[index], symbol, grammar);
//            if (!newState.items.empty()) {
//                auto it = std::find(canonicalCollection.states.begin(), canonicalCollection.states.end(), newState);
//                if (it == canonicalCollection.states.end()) {
//                    canonicalCollection.addState(newState);
//                }
//            }
//        }
//        ++index;
//    }
//
//    return canonicalCollection;
//}