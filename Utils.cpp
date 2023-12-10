//
// Created by Oana on 12/10/2023.
//
#include "Utils.h"
//
// Created by Oana on 12/10/2023.
//

std::set<std::string> Utils::splitStringToSet(const std::string &str, char delimiter) {
    std::vector<std::string> tokens = splitString(str, delimiter);
    return {tokens.begin(), tokens.end()};
}

std::string Utils::trim(const std::string &str) {
    size_t first = str.find_first_not_of(" \t\n");
    if (first == std::string::npos) {
        return "";
    }
    size_t last = str.find_last_not_of(" \t\n");
    return str.substr(first, last - first + 1);
}


void Utils::printSet(const std::set<std::string> &s) {
    std::cout << "{";

    for (const auto &item: s) {
        std::cout << item << ", ";
    }
    std::cout << "}" << std::endl;
}


std::vector<std::string> Utils::splitString(const std::string &str, char delimiter) {
    std::vector<std::string> tokens;
    std::istringstream iss(str);
    std::string token;
    while (std::getline(iss, token, delimiter)) {
        tokens.push_back(token);
    }
    return tokens;
}
