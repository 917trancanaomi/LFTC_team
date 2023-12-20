//
// Created by Naomi on 12/7/2023.
//

#include "Grammar.h"
#include "Utils.h"


Grammar::Grammar() = default;

void Grammar::readFromFile(const std::string &filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return;
    }

    processNonterminals(file);
    processTerminals(file);
    processInitialState(file);
    processProductions(file);

    file.close();
}

void Grammar::printNonterminals() const {
    std::cout << "Nonterminals: ";
    Utils::printSet(nonterminals);
}

void Grammar::printTerminals() const {
    std::cout << "Terminals: ";
    Utils::printSet(terminals);
}

void Grammar::printProductions() const {
    std::cout << "Productions:" << std::endl;
    for (const auto &entry: productions) {
        std::string val = "";
        for (int i = 0; i < entry.second.size(); i++) {
            val += entry.second[i].toString() + " ";
            if (i < entry.second.size() - 1)
                val += "| ";
        }
        std::cout << entry.first << " -> " << val << std::endl;

    }
}

void Grammar::productionsForSpecificNonterminal(const std::string &nonterminal) const {
    std::cout << "Productions for " << nonterminal << ": ";
    auto it = productions.find(nonterminal);
    if (it != productions.end()) {
        std::string val = "";
        for (int i = 0; i < it->second.size(); i++) {
            val += it->second[i].toString();
            if (i < it->second.size() - 1)
                val += "| ";
        }
        std::cout << val << std::endl;
    } else {
        std::cout << "{}";
    }
    std::cout << std::endl;
}

bool Grammar::checkIfCFG() const {
    if (nonterminals.find(startingSymbol) == nonterminals.end()) {
        std::cerr << "Invalid starting symbol: " << startingSymbol << std::endl;
        return false;
    }

    for (const auto &entry: productions) {
        const std::string &leftHandSide = entry.first;
        const auto &productionSet = entry.second;
//        std::cout << leftHandSide << "\n";
        std::vector<std::string> nonterminalsOnLeft = Utils::splitString(leftHandSide, ' ');

        if (nonterminalsOnLeft.size() != 1) {
            std::cerr << "Invalid number of nonterminals on left-hand side: " << leftHandSide << std::endl;
            return false;
        }

        const std::string &nonterminal = nonterminalsOnLeft[0];

        if (nonterminals.find(nonterminal) == nonterminals.end()) {
            std::cerr << "Invalid nonterminal in left-hand side: " << nonterminal << std::endl;
            return false;
        }

        for (const Production &production: productionSet) {
            for (const std::string &symbol: production.getTerms()) {
                if (nonterminals.find(symbol) == nonterminals.end() &&
                    terminals.find(symbol) == terminals.end() &&
                    symbol != EPSILON) {
                    std::cerr << "Invalid symbol in production: " << symbol << std::endl;
                    return false;
                }
            }
        }
    }

    return true;
}

void Grammar::processNonterminals(std::ifstream &reader) {
    std::string nonterminalsLine;
    std::getline(reader, nonterminalsLine);
    nonterminals = Utils::splitStringToSet(nonterminalsLine, ' ');
}

void Grammar::processTerminals(std::ifstream &reader) {
    std::string terminalsLine;
    std::getline(reader, terminalsLine);
    terminals = Utils::splitStringToSet(terminalsLine, ' ');
}

void Grammar::processProductions(std::ifstream &reader) {
    std::string productionLine;

    while (std::getline(reader, productionLine)) {
        std::istringstream iss(productionLine);
        std::string nonterminal;


        std::getline(iss, nonterminal, '>');
        nonterminal = nonterminal.substr(0, nonterminal.find('-') - 1);

        std::vector<Production> productionSymbols;
        std::string productionsStr;
        std::getline(iss, productionsStr);

        std::istringstream productionsStream(productionsStr);
        std::string production;
        while (std::getline(productionsStream, production, '|')) {
            std::cout<<production<<std::endl;
            production = Utils::trim(production);
            Production aux(production);
            productionSymbols.push_back(aux);
        }

        if (!productionSymbols.empty()) {
            productions[nonterminal] = productionSymbols;

        }
    }
}

void Grammar::processInitialState(std::ifstream &reader) {
    std::string startingSymbolLine;
    std::getline(reader, startingSymbolLine);
    startingSymbol = Utils::trim(startingSymbolLine);
}

std::vector<Production> Grammar::getProductionsForNonterminal(std::string nonterminal) {
    auto it = productions.find(nonterminal);
    if (it != productions.end())
        return it->second;
    else return std::vector<Production>();
}

Grammar::Grammar(const Grammar &grammar) {
    this->startingSymbol = grammar.startingSymbol;
    this->nonterminals = grammar.nonterminals;
    this->terminals = grammar.terminals;
    this->productions = grammar.productions;
}

Grammar Grammar::createExpandedGrammar(std::string initialSymbol) {
    Grammar newGrammar(*this);
    Production aux(this->startingSymbol);
    newGrammar.productions[initialSymbol].push_back(aux);
    newGrammar.startingSymbol = initialSymbol;
    return newGrammar;
}

std::vector<std::pair<std::string, Production>> Grammar::getNumberedProductions() {
    std::vector<std::pair<std::string, Production>> prods;
    for (const auto &item: this->productions){
        for (const auto &prod: item.second){
            prods.emplace_back(item.first, prod);
        }
    }
    return prods;
}


