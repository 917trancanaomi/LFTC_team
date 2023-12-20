//
// Created by Oana on 12/10/2023.
//

#include <algorithm>
#include <stack>
#include <cstring>
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
                    if (!input.isPointAtEnd() &&
                        std::find(elements.begin(), elements.end(), input.getPointValue()) == elements.end())
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
    std::vector<std::pair<std::string, Production>> numberedProductions = grammar.getNumberedProductions();
    for (const auto &currentNonterminal: state) {
        //parsing all items
        for (const auto &currentProduction: currentNonterminal.second) {
            if (currentProduction.isPointAtEnd()) {
                if (currentNonterminal.first == grammar.startingSymbol) {
                    value = ACCEPT;
                } else if (value.empty()) {
                    value = REDUCE;

                    int count = 0;
                    for (int prod = 0; prod < numberedProductions.size(); prod++) {
                        if (currentNonterminal.first == numberedProductions[prod].first &&
                            currentProduction.getTerms() == numberedProductions[prod].second.getTerms()) {
                            count = prod + 1;
                            break;
                        }
                    }

                    value += " " + std::to_string(count);
                } else if (value == SHIFT) {
                    std::cerr << "SHIFT REDUCE CONFLICT! State" << i << "- symbol:" << currentNonterminal.first
                              << std::endl;
                    value = "ERROR";
                } else {
                    std::cerr << "REDUCE REDUCE CONFLICT! State" << i << "- symbol:" << currentNonterminal.first
                              << std::endl;
                    value = "ERROR";
                }
            } else if (value == REDUCE) {
                std::cerr << "SHIFT REDUCE CONFLICT! State" << i << "- symbol:" << currentNonterminal.first
                          << std::endl;
                value = "ERROR";
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

bool LR0::completeParsingTable(Grammar grammar) {
    Grammar expandedGrammar = grammar.createExpandedGrammar(grammar.startingSymbol + " PRIME");

    CanonicalCollection expandedGrammarCanonicalCollection(canonicalCollection(expandedGrammar));

    for (int i = 0; i < expandedGrammarCanonicalCollection.states.size(); i++) {
        auto state = expandedGrammarCanonicalCollection.states[i];
        std::string currentAction = action(state, expandedGrammar, i);
        if (currentAction == "ERROR")
            return false;

        this->parsingTable[i].first = currentAction;
        if (currentAction == SHIFT) {
            ///get elements that have to be checked for goto
            std::vector<std::string> elements;
            elements.clear();
            for (const auto &currentProduction: state) {
                for (const auto &input: currentProduction.second) {
                    if (!input.isPointAtEnd() && input != EPSILON)
                        elements.push_back(input.getPointValue());
                }
            }

            for (const auto &element: elements) {
                int value = goToNextState(expandedGrammarCanonicalCollection, state, grammar, element);
                this->parsingTable[i].second.emplace_back(element, value);
            }

        }

    }
    return true;
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

std::vector<int>
LR0::parseSequence(std::vector<std::string> inputStack, Grammar grammar, CanonicalCollection collection) {
    std::stack<std::string> workStack;
    std::stack<int> outputStack;

    //add initial state to work stack
    workStack.emplace("0");
    int posInput = 0;
    bool end = false;
    std::vector<std::pair<std::string, Production>> numberedProductions = grammar.getNumberedProductions();
    while (!end) {
        int state = std::stoi(workStack.top());
        std::string action = parsingTable[state].first;
        if (action == ACCEPT) {
            end = true;
            std::cout << "SEQUENCE ACCEPTED" << std::endl;
            break;
        } else {
            if (action == SHIFT) {
                std::string headInputStack = inputStack[posInput];
                bool checked = false;
                for (const auto &goTO: parsingTable[state].second) {
                    if (goTO.first == headInputStack) {
                        checked = true;
                        workStack.push(headInputStack);
                        workStack.push(std::to_string(goTO.second));
                        break;
                    }
                }

                if (!checked) {
                    std::cerr << "ERROR!! Input stack: ";
                    for (int j = posInput; j < inputStack.size(); j++) {
                        std::cerr << inputStack[j] << " ";
                    }
                    std::cerr << std::endl;
                    break;
                }

                posInput++;
            } else {
                //in the reduce case
                //get the production number;
                int productionNr = atoi(strchr(action.c_str(), ' ')+1);

                outputStack.push(productionNr);

                //popping stuff from the workstack



            }
        }
    }

    //change from stack to vector
    return std::vector<int>();
}
