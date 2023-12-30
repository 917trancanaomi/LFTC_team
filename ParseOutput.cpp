//
// Created by Oana on 12/16/2023.
//

#include <queue>
#include <stack>
#include <iomanip>
#include "ParseOutput.h"

void ParseOutput::populateTableFromProductionString(std::vector<int> productionString, Grammar grammar) {
    //put the starting symbol in the table
    Element aux;
    aux.info = grammar.startingSymbol;
    aux.parent = -1;
    aux.rightSibling = -1;
    table.push_back(aux);
    //parse all the productions
    std::vector<std::pair<std::string, Production>> productionsNumbered = grammar.getNumberedProductions();
    std::deque<int> nonterminalIndexDeque;

    int currentPosition = 0;

    nonterminalIndexDeque.push_back(currentPosition);


    for (int i = 0; i < productionString.size(); i++) {
        Production currentProduction = productionsNumbered[productionString[i] - 1].second;
        auto terms = currentProduction.getTerms();
        int parent = nonterminalIndexDeque.back();
        std::vector<int> aux;
        for (int j = 0; j < terms.size(); j++) {
            currentPosition++;

            Element newterm;
            newterm.info = terms[j];
            newterm.parent = parent;
            if (j == 0)
                newterm.rightSibling = -1;
            else
                newterm.rightSibling = currentPosition - 1;

            table.push_back(newterm);

            //check for nonterminal to add to queue
            if (grammar.nonterminals.find(terms[j]) != grammar.nonterminals.end())
                aux.push_back(currentPosition);
        }
        nonterminalIndexDeque.pop_back();
        for (const auto &item: aux)
            nonterminalIndexDeque.push_back(item);
    }
}


std::ostream &operator<<(std::ostream &os, const ParseOutput &output) {
    os << "Parent-sibling table: \n";
    os << std::left << std::setw(7) << "INDEX" << " | " << std::setw(40) << "INFO" << " | " << std::setw(7) << "PARENT" << " | " << "RIGHT SIBLING\n";
    for (int i = 0; i < output.table.size(); i++) {
        Element el = output.table[i];
        os << std::left << std::setw(7) << i << " | " << std::setw(40) << el.info << " | " << std::setw(7) << el.parent << " | " << el.rightSibling << "\n";
    }
    return os;
}