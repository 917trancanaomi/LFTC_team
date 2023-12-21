// main.cpp
#include <limits>
#include "Grammar.h"
#include "LR0.h"
#include "ParseOutput.h"

void printCanonicalCollection(const CanonicalCollection &canonicalCollection) {
    const auto &states = canonicalCollection.getStates();
    for (size_t i = 0; i < states.size(); ++i) {
        std::cout << "State " << i << ":\n";
        const auto &state = states[i];
        for (const auto &item: state) {
            const std::string &nonterminal = item.first;
            const auto &productions = item.second;

            for (const auto &production: productions) {
                std::cout << nonterminal << " -> ";
                std::cout << production;
                std::cout << "\n";
            }
        }
        std::cout << "\n";
    }
}

int main() {
    Grammar grammar;
    grammar.readFromFile("C:\\Users\\Naomi\\Desktop\\University Year 3\\lftc\\LFTC_team\\g3.txt");

    int opt = -1;
    while (opt != 0) {
        std::cout << "Choose one of the following options" << std::endl;
        std::cout << "0. Exit" << std::endl;
        std::cout << "1: List the set of nonterminals" << std::endl;
        std::cout << "2: List the set of terminals:" << std::endl;
        std::cout << "3: List the productions" << std::endl;
        std::cout << "4: List productions for a given nonterminal" << std::endl;
        std::cout << "5: Check if CFG" << std::endl;
        std::cout << "6: Canonical collection" << std::endl;
        std::cout << "7: Create Parsing table" << std::endl;
        std::cout << "8: Test ParseOutput with 133" << std::endl;
        std::cout << "10: Read Grammar and Sequence from File and User Input" << std::endl;
        std::cout << "Enter option: ";

        try {
            std::cin >> opt;
            LR0 lr0;
            switch (opt) {
                case 1:
                    grammar.printNonterminals();
                    break;
                case 2:
                    grammar.printTerminals();
                    break;
                case 3:
                    grammar.printProductions();
                    break;
                case 4: {
                    std::cout << "Enter the given nonterminal: ";
                    std::string nonterminal;
                    std::cin >> nonterminal;
                    grammar.productionsForSpecificNonterminal(nonterminal);
                    break;
                }
                case 5:
                    std::cout << "Check if CFG: " << std::boolalpha << grammar.checkIfCFG() << std::endl;
                    break;
                case 6: {
                    Grammar expandedGrammar = grammar.createExpandedGrammar(grammar.startingSymbol + "PRIME");
                    CanonicalCollection collection = lr0.canonicalCollection(expandedGrammar);
                    printCanonicalCollection(collection);
                    break;
                }
                case 7: {
//                    if (lr0.completeParsingTable(grammar))
//                        lr0.printParsingTable();
                    lr0.completeParsingTable(grammar);
//                    lr0.printParsingTable();
                    break;
                }
                case 8: {
                    std::vector<std::string> inputSequence = {"a", "b", "b", "c"};
                    //Parse the input sequence
                    std::vector<int> parseResult = lr0.parseSequence(grammar, inputSequence);

                    // Print the result of parsing
                    std::cout << "Parsing result: ";
                    for (int result: parseResult) {
                        if (result == -1) {
                            std::cout << "Error";
                        } else {
                            std::cout << "Production " << result << " ";
                        }
                    }
                    std::cout << std::endl;
                    // Generate parse table using ParseOutput
                    ParseOutput parseOutput;
                    parseOutput.populateTableFromProductionString(parseResult, grammar);
                    std::cout << parseOutput << std::endl;
                }
                case 9: {
                    std::vector<std::string> inputSequence = {"a", "b", "b", "c"};

                    lr0.completeParsingTable(grammar);
                    // Parse the input sequence
                    std::vector<int> parseResult = lr0.parseSequence(grammar, inputSequence);

                    // Print the result of parsing
                    std::cout << "Parsing result: ";
                    for (int result: parseResult) {
                        if (result == -1) {
                            std::cout << "Error";
                        } else {
                            std::cout << "Production " << result << " ";
                        }
                    }
                    std::cout << std::endl;
                    break;
                }
                case 0:
                    std::cout << "Exiting..." << std::endl;
                    break;
                default:
                    std::cout << "Invalid option" << std::endl;
                    break;
            }

        } catch (const std::exception &e) {
            std::cerr << "Exception: " << e.what() << std::endl;
        }
    }

    return 0;
}
