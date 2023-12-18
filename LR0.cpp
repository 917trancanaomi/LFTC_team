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
                        if (newOutput[nonTerminal].empty() ||
                            std::find(newOutput[nonTerminal].begin(), newOutput[nonTerminal].end(), smolprod) ==
                            newOutput[nonTerminal].end()) {
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
            if (!prod.isPointAtEnd() && prod.getPointValue() == X) {
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
                    if (!input.isPointAtEnd() && std::find(elements.begin(), elements.end(), input.getPointValue()) == elements.end())
                        elements.push_back(input.getPointValue());
                }
            }
            for (const auto &element: elements) {
                std::map<std::string, std::vector<Production>> newStateItems = goTo(
                        item, grammar, element
                );

                if (!newStateItems.empty() && !newCanonicalCollection.stateExists(newStateItems)) {
                    newCanonicalCollection.addState(newStateItems);
                    changed = true;
                }

            }

        }
        oldCanonicalCollection = newCanonicalCollection;
    } while (changed);

    return oldCanonicalCollection;
}

std::string
LR0::action(std::map<std::string, std::vector<Production>> state, Grammar grammar, int i) {
    std::string value = "";
    for (const auto &currentNonterminal: state) {
        //parsing all items
        for (const auto &currentProduction: currentNonterminal.second) {
            if (currentProduction.isPointAtEnd()) {
                if (currentNonterminal.first == grammar.startingSymbol) {
                    value = ACCEPT;
                } else if (value.empty()) {
                    value = REDUCE;

                    int count = 0;
                    bool terminationFlag = false;
                    for (const auto &item: grammar.productions) {
                        for (const auto &production: item.second) {
                            count++;
                            if (currentNonterminal.first == item.first &&
                                currentProduction.getTerms() == production.getTerms()) {
                                terminationFlag = true;
                                break;
                            }
                        }
                        if (terminationFlag)
                            break;

                    }
                    value += " " + std::to_string(count);
                } else if (value == SHIFT) {
                    std::cerr << "SHIFT REDUCE CONFLICT! State" << i << " " << std::endl;
                } else {
                    std::cerr << "REDUCE REDUCE CONFLICT! State" << i << " " << std::endl;
                }
            } else if (value == REDUCE) {
                std::cerr << "SHIFT REDUCE CONFLICT! State" << i << " " << std::endl;
            } else {
                value = SHIFT;
            }
        }
    }
    return value;
}

int LR0::goToNextState(CanonicalCollection canonicalCollection, std::map<std::string, std::vector<Production>> state,
                       Grammar grammar, std::string element) {
    int value = -1;
    auto valueGoTo = goTo(state, grammar, element);

    for (int i = 0; i < canonicalCollection.states.size(); i++) {
        if (valueGoTo == canonicalCollection.states[i]) {
            value = i;
            break;
        }
    }

    return value;
}

void LR0::completeParsingTable(Grammar grammar) {
    Grammar expandedGrammar = grammar.createExpandedGrammar(grammar.startingSymbol + " PRIME");

    CanonicalCollection expandedGrammarCanonicalCollection(canonicalCollection(expandedGrammar));

    for (int i = 0; i < expandedGrammarCanonicalCollection.states.size(); i++) {
        auto state = expandedGrammarCanonicalCollection.states[i];
        std::string currentAction = action(state, expandedGrammar, i);

        this->parsingTable[i].first = currentAction;
        if (currentAction == SHIFT) {
            ///get elements that have to be checked for goto
            std::vector<std::string> elements;
            elements.clear();
            for (const auto &currentProduction: state) {
                for (const auto &input: currentProduction.second) {
                    if (!input.isPointAtEnd())
                        elements.push_back(input.getPointValue());
                }
            }

            for (const auto &element: elements) {
                int value = goToNextState(expandedGrammarCanonicalCollection, state, grammar, element);
                this->parsingTable[i].second.emplace_back(element, value);
            }

        }

    }

}

void LR0::printParsingTable() {
    std::cout << "~~~~PARSING TABLE~~~~" << std::endl;
    for (const auto &states: this->parsingTable) {
        std::cout << "state " << states.first << " -  ACTION " << states.second.first << std::endl;
        for (const auto &item: states.second.second) {
            std::cout << "GOTO(" << item.first << ") = state " << item.second << std::endl;
        }
        std::cout << std::endl;
    }

}

std::vector<int> LR0::parseSequence(Grammar grammar) {
    return std::vector<int>();
}

