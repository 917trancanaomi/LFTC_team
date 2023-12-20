//
// Created by Oana on 12/16/2023.
//

#include <queue>
#include "ParseOutput.h"

void ParseOutput::populateTableFromProductionString(std::vector<int> productionString, Grammar grammar) {
    if (productionString[0] == -1) {
        std::cout << "Parsing incorrect | bad production string" << std::endl;
        return;
    }


    //put the starting symbol in the table
    Element aux;
    aux.info = grammar.startingSymbol;
    aux.parent = -1;
    aux.rightSibling = -1;
    table.push_back(aux);
    //parse all the productions
    std::vector<std::pair<std::string, Production>> productionsNumbered = grammar.getNumberedProductions();
    std::queue<int> nonterminalIndexQueue;
    int currentPosition = 0;

    nonterminalIndexQueue.push(currentPosition);

    for (int i = 0; i < productionString.size(); i++) {
        Production currentProduction = productionsNumbered[productionString[i] - 1].second;
        auto terms = currentProduction.getTerms();
        for (int j = 0; j < terms.size(); j++) {
            currentPosition++;

            Element newterm;
            newterm.info = terms[j];
            newterm.parent = nonterminalIndexQueue.front();
            if (j == 0)
                newterm.rightSibling = -1;
            else
                newterm.rightSibling = currentPosition - 1;

            table.push_back(newterm);

            //check for nonterminal to add to queue
            if (grammar.nonterminals.find(terms[j]) != grammar.nonterminals.end())
                nonterminalIndexQueue.push(currentPosition);

        }
        nonterminalIndexQueue.pop();
    }
}


std::ostream &operator<<(std::ostream &os, const ParseOutput &output) {
    os << "Parent-sibling table: \n";
    os << " INDEX  " << " | " << "  INFO  " << " | " << " PARENT " << " | " << "RIGHT SIBLING\n";
    for (int i = 0; i < output.table.size(); i++) {
        Element el = output.table[i];
        os << i << "         | " << el.info << "         | " << el.parent << "         | " << el.rightSibling << "\n";
    }
    return os;
}
