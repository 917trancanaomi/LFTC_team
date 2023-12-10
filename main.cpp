// main.cpp
#include <limits>
#include "Grammar.h"
#include "LR0.h"

int main() {
    Grammar grammar;
    grammar.readFromFile("D:\\UniversityWork\\LFTC_team\\g.txt");

//    int opt = -1;
//    while (opt != 0) {
//        std::cout << "Choose one of the following options" << std::endl;
//        std::cout << "0. Exit" << std::endl;
//        std::cout << "1: List the set of nonterminals" << std::endl;
//        std::cout << "2: List the set of terminals:" << std::endl;
//        std::cout << "3: List the productions" << std::endl;
//        std::cout << "4: List productions for a given nonterminal" << std::endl;
//        std::cout << "5: Check if CFG" << std::endl;
//        std::cout << "Enter option: ";
//
//        try {
//            std::cin >> opt;
//            switch (opt) {
//                case 1:
//                    grammar.printNonterminals();
//                    break;
//                case 2:
//                    grammar.printTerminals();
//                    break;
//                case 3:
//                    grammar.printProductions();
//                    break;
//                case 4: {
//                    std::cout << "Enter the given nonterminal: ";
//                    std::string nonterminal;
//                    std::cin >> nonterminal;
//                    grammar.productionsForSpecificNonterminal(nonterminal);
//                    break;
//                }
//                case 5:
//                    std::cout << "Check if CFG: " << std::boolalpha << grammar.checkIfCFG() << std::endl;
//                    break;
//                case 0:
//                    std::cout << "Exiting..." << std::endl;
//                    break;
//                default:
//                    std::cout << "Invalid option" << std::endl;
//                    break;
//            }
//        } catch (const std::exception& e) {
//            std::cerr << "Exception: " << e.what() << std::endl;
//        }
//    }
    LR0 lr0;
    std::map<std::string, std::vector<Production>> input, output;
    input["S"] = std::vector<Production>();
    input["S"].push_back(Production("A 2"));
    input["S"].push_back(Production("1"));
    input["S"].push_back(Production("3"));

    output = lr0.goTo(input, grammar, "A");

    return 0;
}
