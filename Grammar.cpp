//
// Created by Naomi on 12/7/2023.
//

#include "Grammar.h"

const std::string Grammar::EPSILON = "epsilon";

Grammar::Grammar() = default;

void Grammar::readFromFile(const std::string& filename) {
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
    printSet(nonterminals);
}

void Grammar::printTerminals() const {
    std::cout << "Terminals: ";
    printSet(terminals);
}

void Grammar::printProductions() const {
    std::cout << "Productions:" << std::endl;
    for (const auto& entry : productions) {
        std::cout << entry.first << " -> " << vectorToString(entry.second) << std::endl;
    }
}

void Grammar::productionsForSpecificNonterminal(const std::string& nonterminal) const {
    std::cout << "Productions for " << nonterminal << ": ";
    auto it = productions.find(nonterminal);
    if (it != productions.end()) {
        std::cout << vectorToString(it->second);
    } else {
        std::cout << "{}";
    }
    std::cout << std::endl;
}

bool Grammar::checkIfCFG() const {
    if (nonterminals.find(initialState) == nonterminals.end()) {
        std::cerr << "Invalid initial state: " << initialState << std::endl;
        return false;
    }

    for (const auto& entry : productions) {
        const std::string& leftHandSide = entry.first;
        const auto& productionSet = entry.second;
        std::cout<<leftHandSide<<"\n";
        std::vector<std::string> nonterminalsOnLeft = splitString(leftHandSide, ' ');

        if (nonterminalsOnLeft.size() != 1) {
            std::cerr << "Invalid number of nonterminals on left-hand side: " << leftHandSide << std::endl;
            return false;
        }

        const std::string& nonterminal = nonterminalsOnLeft[0];

        if (nonterminals.find(nonterminal) == nonterminals.end()) {
            std::cerr << "Invalid nonterminal in left-hand side: " << nonterminal << std::endl;
            return false;
        }

        for (const std::string& production : productionSet) {
            std::vector<std::string> symbols = splitString(production, ' ');

            for (const std::string& symbol : symbols) {
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

void Grammar::processNonterminals(std::ifstream& reader) {
    std::string nonterminalsLine;
    std::getline(reader, nonterminalsLine);
    nonterminals = splitStringToSet(nonterminalsLine, ' ');
}

void Grammar::processTerminals(std::ifstream& reader) {
    std::string terminalsLine;
    std::getline(reader, terminalsLine);
    terminals = splitStringToSet(terminalsLine, ' ');
}

void Grammar::processProductions(std::ifstream& reader) {
    std::string productionLine;

    while (std::getline(reader, productionLine)) {
        std::istringstream iss(productionLine);
        std::string nonterminal;
//        iss >> nonterminal;
//
//        if (nonterminal.empty()) {
//            continue;
//        }

        std::getline(iss, nonterminal, '>');
        nonterminal = nonterminal.substr(0, nonterminal.find('-'));
//
//        std::string separator;
//        iss >> separator; // "->"

        std::vector<std::string> productionSymbols;
        std::string productionsStr;
        std::getline(iss, productionsStr);

        std::istringstream productionsStream(productionsStr);
        std::string production;
        while (std::getline(productionsStream, production, '|')) {
            production = trim(production);
            productionSymbols.push_back(production);
        }

        if (!productionSymbols.empty()) {
            productions[nonterminal] = std::set<std::string>(productionSymbols.begin(), productionSymbols.end());
            nonterminals.insert(nonterminal);

            // Set initial state if not set
            if (initialState.empty()) {
                initialState = nonterminal;
            }
        }
    }
}

void Grammar::processInitialState(std::ifstream& reader) {
    std::getline(reader, initialState);
    initialState = trim(initialState);
}

std::vector<std::string> Grammar::splitString(const std::string& str, char delimiter) {
    std::vector<std::string> tokens;
    std::istringstream iss(str);
    std::string token;
    while (std::getline(iss, token, delimiter)) {
        tokens.push_back(token);
    }
    return tokens;
}

std::set<std::string> Grammar::splitStringToSet(const std::string& str, char delimiter) {
    std::vector<std::string> tokens = splitString(str, delimiter);
    return std::set<std::string>(tokens.begin(), tokens.end());
}

std::string Grammar::trim(const std::string& str) {
    size_t first = str.find_first_not_of(" \t\n");
    if (first == std::string::npos) {
        return "";
    }
    size_t last = str.find_last_not_of(" \t\n");
    return str.substr(first, last - first + 1);
}

std::string Grammar::vectorToString(const std::set<std::string>& vec) {
    std::ostringstream oss;
    std::vector<std::string> vecList(vec.begin(), vec.end());

    for (size_t i = 0; i < vecList.size(); ++i) {
        oss << vecList[i];
        if (i < vecList.size() - 1) {
            oss << " | ";
        }
    }

    return oss.str();
}


template <typename T>
void Grammar::printSet(const std::set<T>& s) const {
    std::cout << "{";
    for (const auto& item : s) {
        std::cout << item << ", ";
    }
    std::cout << "}" << std::endl;
}
