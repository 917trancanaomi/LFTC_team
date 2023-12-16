//
// Created by Naomi on 12/15/2023.
//

#include <iostream>
#include <map>

class ParsingTable {
public:

    char action;  // 's' for shift, 'r' for reduce, 'a' for accept
    int stateOrProduction;  // State number for shift, production number for reduce

    // Example print method
    void print() const {
        for (const auto& entry : table) {
            std::cout << "State " << entry.first << ":\n";
            for (const auto& action : entry.second) {
                std::cout << "  Symbol " << action.first << ": " << action.second << "\n";
            }
        }
    }

private:
    std::map<std::string, std::map<std::string, std::string>> table;


};
